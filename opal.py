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
        return find_by_label(self.driver, label, class_)


class LoginPage (OpalPage):
    def onPage(self):
        return self.onPageContents()

    def onPageContents(self):
        return self.elementExists(tag='label', contains_text='User Name') and \
            self.elementExists(tag='label', contains_text='Password') and \
            self.elementExists(tag='a', contains_text='Sign In')

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
        return self.elementExists(tag='h1', contains_text='Dashboard')

    def exploreData(self):
        self.driver.find_element(link_text='Explore Data').click()
        return Projects(self.driver).waitFor()
        

class Projects (OpalPage):
    url_location = 'projects'

    def onPageContents(self):
        return self.elementExists(tag='h1', contains_text='Projects') and self._projectlinks()

    def _projectlinks(self, contains=''):
        return self.driver.find_elements(css="tr div a[href^='#!project;name=']", contains_text=contains)

    def project(self, name):
        projects = self._projectlinks(name)
        assert projects
        projects[0].click()
        return Project(self.driver, name).waitFor()

    def createProject(self, name):
        assert not self.hasProject(name)
        self.driver.find_element(link_text='Add Project').click()
        self.waitForCondition(lambda: self.findByLabel('Name'))
        self.findByLabel('Name').send_keys(name)
        self.findByLabel('Title').send_keys(name)
        self.driver.find_element(link_text='Save').click()
        self.waitForCondition(lambda: not_find_by_label(self.driver, 'Name'))

    def hasProject(self, name):
        return bool(self._projectlinks(name))


class Project (OpalPage):
    def __init__(self, driver, name):
        super(Project, self).__init__(driver)
        self.name = name
        self.selector = "tr div a[href^='#!project;name=%s;tab=TABLES;path=']" % css_escape(name)

    def onPageContents(self):
        # global debug
        # debug = self.driver.find_elements(css=self.selector)
        # return debug
        # return C.element_present(css=self.selector)

        # FIXME: There is a strange race condition in which something matches the self.selector that 
        # shouldn't (The <a> that containing 'Dashboard' in the left top corner matches). Sleep as a workaround
        # time.sleep(0.1) 
        return self.elementExists(css='tr div span.gwt-InlineLabel', contains_text='No tables') or \
            self.elementExists(css=self.selector)

    def tables(self):
        return self.driver.find_elements(css=self.selector)

    def addTable(self, name):
        self.findElement(link_text='Add Table').click()
        self.waitForCondition(lambda: self.elementExists(link_text='Add table...'))
        self.findElement(link_text='Add table...').click()
        self.waitForCondition(lambda: self.findByLabel('Name'))
        self.findByLabel('Name').send_keys(name)
        self.findElement(link_text='Save').click()
        return Table(self.driver, self.name, name).waitFor()
        

class Table (OpalPage):
    def __init__(self, driver, projectname, tablename):
        super(Table, self).__init__(driver)
        self.projectname = projectname
        self.tablename = tablename

    def onPageContents(self):
        return self.elementExists(link_text='Add Variable') and \
            self.elementExists(css='h3', contains_text='Tables')
        
#    def 

    

def css_escape(string, quotes="'"):
    return string.replace(quotes, '\\'+quotes)

def xpath_string_escape(s):
    if "'" not in s: return "'%s'" % s
    if '"' not in s: return '"%s"' % s
    return "concat('%s')" % s.replace("'", "',\"'\",'")

def not_find_by_label(driver, label, class_='gwt-TextBox'):
    try:
        return not find_by_label(driver, label, class_)
    except NoSuchElementException:
        return True

def find_by_label(driver, label, class_='gwt-TextBox'):
    "Find an <input> element with a certain class that is preceded by a <label> containing the given text"
    # Unfortunately the only way powerful enough seems to be xpath
    return driver.find_element(xpath="//label[contains(text(), %s)]/following-sibling::input[contains(@class, %s)]" % (
        xpath_string_escape(label), xpath_string_escape(class_)))

