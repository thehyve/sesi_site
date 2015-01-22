#!/usr/bin/env python
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By

from pylenium import Pylenium
import pylenium.conditions as C


class Page (object):
    def __init__(self, driver=None):
        self._driver = driver
    
    @property
    def driver(self):
        """Allow using a global for now to prevent threading the driver through all objects. 
        This should really be a dynamic scoped variable."""
        #global driver
        return self._driver or driver

    @property
    def title(self):
        return self.driver.title

    def loggedIn(self):
        self.ensureScreenWidth()
        return C.element_present(link_text='User menu').test(driver)

    def ensureScreenWidth(self):
        size = self.driver.window_size
        if size[0] < 1050:
            self.driver.window_size = (1050, size[1])
        assert self.driver.window_size[0] >= 1050



class Autologout (Page):
    def onPage(self):
        return not self.loggedIn() and text_in_element(css='div.alert.alert-succes', text='You have been logged out').test(self.driver)


class HomePage (Page):
    def onPage(self):
        return C.text_in_element(css='h1', text='CMI - Center for Medical Innovation vzw').test(self.driver)

    def ensureLoggedIn(self):
        if not self.loggedIn():
            self.logIn()
        assert self.loggedIn()

    def logIn(self):
        usernamefield = self.driver.find_element(id='edit-name')
        usernamefield.send_keys(username)
        passwordfield = self.driver.find_element(id='edit-pass')
        passwordfield.send_keys(password)
        passwordfield.submit()
        self.driver.wait_until(C.any(C.element_visible(link_text='User menu'), 
                                        C.element_visible(css='div.alert.alert-error')))
        


