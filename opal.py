#!/usr/bin/env python
from urlparse import urlparse
import time
from selenium.common.exceptions import TimeoutException, NoSuchElementException
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By

from pylenium import Pylenium
import pylenium.conditions as C

from browser import Page

class OpalPage (Page):
    @property
    def location(self):
        return urlparse(self.driver.current_url).fragment.lstrip('!')

    def onPage(self):
        return self.loggedIn() and type(self).url_location == self.location

    def waitFor(self, **kwargs):
        self.waitForCondition(self.onPageContents, **kwargs)
        return self

    def waitForCondition(self, *conditions, **kwargs):
        return self.driver.wait_until(*(lambda _: c() for c in conditions), **kwargs)

    def loggedIn(self):
        if LoginPage(self.driver).onPage():
            return False
        if self.location == 'dashboard':
            self.driver.find_element(link_text='Projects').click()
        else:
            self.driver.find_element(link_text='Dashboard').click()
        self.driver.back()
        time.sleep(1)
        return not LoginPage(self.driver).onPage()

    # def ensureLoggedIn(self, username, password):
    #     if not self.loggedIn():
    #         loginpage = LoginPage(self.driver)
    #         assert loginpage.onPage()
    #         loginpage.logIn(username, password)
    #     assert self.loggedIn()

    def findCurrentPage(self):
        loc = self.location
        for cls in OpalPage.__subclasses__():
            try:
                if cls.url_location == loc: return cls(self.driver)
            except AttributeError:
                continue
        raise TestException('unable to identify current page: ' + self.driver.url)

    def ensureScreenWidth(self):
        size = self.driver.window_size
        if size[0] < 1050:
            self.driver.window_size = (1050, size[1])
        assert self.driver.window_size[0] >= 1050

    def logOut(self):
        if self.loggedIn():
            self.driver.find_element(link_text=self.browser.username).click()
            self.driver.find_element(link_text='Logout').click()
        return LoginPage(self.driver).waitFor()

    def findByLabel(self, label, class_='gwt-TextBox'):
        "Find an <input> element with a certain class that is preceded by a <label> containing the given text"
        # Unfortunately the only way powerful enough seems to be xpath
        return self.driver.find_element(xpath="//label[contains(text(), %s)]/following-sibling::input[contains(@class, %s)]" % (
            xpath_string_escape(label), xpath_string_escape(class_)))


class LoginPage (OpalPage):
    def onPage(self):
        return self.onPageContents()

    def onPageContents(self):
        try:
            self.driver.find_element(tag='label', contains_text='User Name')
            self.driver.find_element(tag='label', contains_text='Password')
            self.driver.find_element(tag='a', contains_text='Sign In')
            return True
        except NoSuchElementException:
            return False

    def logIn(self, username, password):
        username_field = self.findByLabel('User Name')
        password_field = self.findByLabel('Password', 'gwt-PasswordTextBox')
        username_field.send_keys(username)
        password_field.send_keys(password + '\n')
        self.driver.wait_until(C.element_present(link_text='Dashboard'))
        return self.findCurrentPage()


class Dashboard (OpalPage):
    url_location = 'dashboard'

    def onPageContents(self):
        return C.element_present(tag='h1', contains_text='Dashboard')

    def exploreData(self):
        self.driver.find_element(link_text='Explore Data').click()
        return Projects(self.driver).waitFor()
        

class Projects (OpalPage):
    url_location = 'projects'

    def onPageContents(self):
        return C.element_present(tag='h1', contains_text='Projects') and self._projectlinks()

    def _projectlinks(self, contains=''):
        return self.driver.find_elements(xpath="//tr//div/a[contains(@href, '#!project;name=')]", contains_text=contains)

    def project(self, name):
        projects = self._projectlinks(name)
        assert projects
        assert False

    def createProject(self, name):
        assert not self.hasProject(name)
        self.driver.find_element(link_text='Add Project').click()
        self.waitForCondition(lambda: self.findByLabel('Name'))
        self.findByLabel('Name').send_keys(name)
        self.findByLabel('Title').send_keys(name)
        self.driver.find_element(link_text='Save').click()
                    

    def hasProject(self, name):
        return bool(self._projectlinks(name))


class Project (OpalPage):
    pass
    
def xpath_string_escape(s):
    if "'" not in s: return "'%s'" % s
    if '"' not in s: return '"%s"' % s
    return "concat('%s')" % s.replace("'", "',\"'\",'")
