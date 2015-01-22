#!/usr/bin/env python
import atexit
from selenium import webdriver
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By

from pylenium import Pylenium
import conditions as cond

mica = 'http://localhost:7880/mica'
username = 'jan'
password = 'mica'

timeout = 3

def main():
    global pylenium, usernamefield, passwordfield
    # Create a new instance of the Firefox driver
    pylenium = Pylenium(webdriver.Firefox())
    # auto-kill the browser on exit
    atexit.register(pylenium.quit)
    

    pylenium.get(mica)
    print "page title:" + pylenium.title
    # The user menu is not visible on small screens
    size = pylenium.window_size
    if size[0] < 1050:
        pylenium.window_size = (1050, size[1])


    usernamefield = pylenium.find_element(id='edit-name')
    usernamefield.send_keys(username)
    passwordfield = pylenium.find_element(id='edit-pass')
    passwordfield.send_keys(password)
    passwordfield.submit()

    try:
        # we have to wait for the page to refresh, the last thing that seems to be updated is the title
        pylenium.wait_until(cond.any(cond.element_visible(link_text='User menu'), 
                                     cond.element_visible(css='div.alert.alert-error')))
        if not pylenium.find_elements(link_text='User menu'):
            raise Exception("Login failed")

    finally:
        pass
        #pylenium.quit()




class Page (object):
    def __init__(self, driver=None):
        self.driver = driver
    
    @property
    def driver(self):
        """Allow using a global for now to prevent threading the driver through all objects. 
        This should really be a dynamic scoped variable."""
        if self.driver:
            return self.driver
        return driver

    def loggedIn(self):
        self.ensureScreenWidth()
        return bool(self.driver.find_elements(link_name='User menu'))

    def ensureScreenWidth(self):
        size = pylenium.window_size
        if size[0] < 1050:
            pylenium.window_size = (1050, size[1])



class Autologout (Page):

    def onPage(self):
        return not self.loggedIn() and bool(
            [e for e in self.driver.find_elements(css='div.alert.alert-succes') if 
             'You have been logged out' in e.text])

class HomePage (Page):
    def onPage(self):
        return bool(self.driver.find_elements(css='h1', contains_text='CMI - Center for Medical Innovation vzw'))


if __name__ == '__main__':
    main()

