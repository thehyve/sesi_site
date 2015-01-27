#!/usr/bin/env python
from __future__ import unicode_literals, division, absolute_import, print_function

import atexit
from selenium import webdriver
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By

from pylenium import Pylenium
import pylenium.conditions as C

from browser import Browser
from mica import *
from opal import *

opal_url = 'http://localhost:8080'
opal_username = 'administrator'
opal_password = 'password'
opal_project = 'regression_test_project'

mica_url = 'http://localhost:7880/mica'
mica_username = 'jan'
mica_password = 'mica'



timeout = 3

def newdriver():
    global mica
    # Create a new instance of the Firefox driver
    driver = mica = Pylenium(webdriver.Firefox())
    # auto-kill the browser on exit
    atexit.register(driver.quit)
    return driver


def test_mica():
    global mica, opal
    pylenium = newdriver()

    pylenium.get(mica_url)
    size = pylenium.window_size
    if size[1] > 1000:
        pylenium.window_size = (size[0], 1000)
    page = HomePage(pylenium)
    print("page title:" + page.title)

    assert not page.loggedIn()
    page.logIn(mica_username, mica_password)
    assert HomePage.onPage(page)
    assert page.loggedIn()

def test_opal():
    global opal
    browser = opal = Browser(newdriver(), opal_url, LoginPage)
    assert browser.onPage()
    assert not browser.loggedIn()
    browser.logIn(opal_username, opal_password)
    assert browser.loggedIn()
    browser.exploreData()
    assert Projects.onPage(browser.page)
    import pdb; pdb.set_trace()
    if browser.hasProject(opal_project):
        print("project '{}' already exists, skipping project creation")
    else:
        browser.createProject(opal_project)
    assert browser.hasProject(opal_project)
    

if __name__ == '__main__':
    #test_mica()
    test_opal()

