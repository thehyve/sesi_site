#!/usr/bin/env python
from __future__ import unicode_literals, division, absolute_import, print_function

import os
import atexit
from selenium import webdriver
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By

import pylenium
import pylenium.conditions as C

from browser import Browser
from mica import *
from opal import *

class conf:
    class opal:
        url = 'http://localhost:8080'
        username = 'administrator'
        password = 'password'
        project = 'regression_test_project'
        tablename = 'diabetes_antwerp'
        viewname = 'MDS_Diabetes_Antwerp'
        tablefile = 'Diabetes_Antwerp_export.zip'
        viewfile = 'MDS_Diabetes_Antwerp.xml'
        mica_user = 'ssl_mica'

    class mica:
        url = 'http://localhost:7880/mica'
        username = 'mica'
        password = 'mica'
        dataset = 'regressiontest dataset'
        study = 'regressiontest study'
        study_summary = 'A dummy used in automated testing'



timeout = 3

def newdriver():
    # Create a new instance of the Firefox driver
    driver  = pylenium.Firefox()
    size = driver.window_size
    driver.window_size = (1100, min(1000, size[1]))
    driver.window_position = (0,0)
    # auto-kill the browser on exit
    atexit.register(driver.quit)
    return driver


def test_mica():
    global mica
    browser = mica = Browser(newdriver(), conf.mica.url, HomePage)

    print("page title:" + browser.title)

    assert not browser.loggedIn()
    print("logging in")
    browser.logIn(conf.mica.username, conf.mica.password)
    assert browser.onPage(HomePage)
    assert browser.loggedIn()

    browser.gotoStudies()
    print('looking for study '+conf.mica.study)
    if browser.hasStudy(conf.mica.study):
        print('deleting study '+conf.mica.study)
        browser.gotoStudy(conf.mica.study)
        browser.gotoEdit()
        browser.delete()
    print("creating new study "+conf.mica.study)
    create_study(browser, conf.mica.study, conf.mica.study_summary)

    datasetname = conf.mica.dataset+' v1'
    browser.gotoDatasets()
    print("looking for dataset "+datasetname)
    if browser.hasDataset(datasetname):
        print("deleting dataset "+datasetname)
        browser.gotoDataset(datasetname)
        browser.gotoEdit()
        browser.delete()
    print("creating new dataset "+conf.mica.dataset)
    create_dataset(browser, conf.mica.dataset)


def create_dataset(browser, name):
    assert browser.onPage(Datasets)
    browser.newDataset()
    browser.setName(name)
    browser.setTypeHarmonization()
    browser.setPublished()
    browser.save()

def create_study(browser, name, summary):
    assert browser.onPage(Studies)
    browser.newStudy()
    browser.setName(name)
    browser.setSummary(summary)
    browser.setPublished()
    browser.save()



def test_opal():
    global opal
    browser = opal = Browser(newdriver(), conf.opal.url, LoginPage)
    return load_opal_data(browser)


def load_opal_data(browser):
    browser.ensureLoggedIn(conf.opal.username, conf.opal.password)
    browser.gotoProjects()
    assert browser.onPage(Projects)
    if browser.hasProject(conf.opal.project):
        print("project '{}' already exists, skipping project creation".format(conf.opal.project))
    else:
        print("creating project "+conf.opal.project)
        browser.createProject(conf.opal.project)
    assert browser.hasProject(conf.opal.project)

    browser.gotoProject(conf.opal.project)
    tables = browser.tables()
    print("tables: "+', '.join(tables))
    if browser.hasTable(conf.opal.tablename):
        print('removing table '+conf.opal.tablename)
        browser.removeTable(conf.opal.tablename)
    print('importing table '+conf.opal.tablename)
    browser.importTable(os.path.abspath(conf.opal.tablefile), conf.opal.tablename)
    assert browser.hasTable(conf.opal.tablename)
    print("indexing table "+conf.opal.tablename)
    browser.gotoTable(conf.opal.tablename)
    browser.gotoSummary()
    browser.index()
    print("setting permissions on "+conf.opal.tablename)
    browser.gotoPermissions()
    if not browser.getPermission(conf.opal.mica_user):
        browser.addUserPermission(conf.opal.mica_user, 'View dictionary and summaries')

    browser.gotoProject()
    if browser.hasTable(conf.opal.viewname):
        print('removing view '+conf.opal.viewname)
        browser.removeTable(conf.opal.viewname)
    print("importing view "+conf.opal.viewname)
    browser.importView(conf.opal.viewname, [conf.opal.tablename], os.path.abspath(conf.opal.viewfile))
    print("indexing view "+conf.opal.viewname)
    browser.gotoSummary()
    browser.index()
    print("setting permissions on "+conf.opal.viewname)
    browser.gotoPermissions()
    if not browser.getPermission(conf.opal.mica_user):
        browser.addUserPermission(conf.opal.mica_user, 'View dictionary and summaries')
    browser.gotoProject()

def remove_opal_data(browser):
    print("removing project "+conf.opal.project)
    browser.ensureLoggedIn(conf.opal.username, conf.opal.password)
    browser.gotoProjects()
    if not browser.hasProject(conf.opal.project):
        print("project '{}' not found, cannot remove it".format(conf.opal.project))
        return
    browser.gotoProject(conf.opal.project)
    print("removing tables from project "+conf.opal.project)
    browser.removeAllTables()
    browser.removeProject()
    

if __name__ == '__main__':
    test_mica()
    #test_opal()

