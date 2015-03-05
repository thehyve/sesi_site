#!/usr/bin/env python
from __future__ import unicode_literals, division, absolute_import, print_function

import os
import atexit
from pprint import pprint
import yaml

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
from helpers import namespace


# Patch yaml to use our modified dict class
# Note: this will affect yaml process-wide, but for our case that is ok.
def construct_map(loader, node):
    d = namespace()
    yield d
    d.update(loader.construct_mapping(node))
yaml.add_constructor('tag:yaml.org,2002:map', construct_map)

conf = yaml.load("""
opal:
  url: http://localhost:8080
  username: administrator
  password: password
  projects:
    regression_test_project:
      tables:
        diabetes_antwerp:
          file: Diabetes_Antwerp_export.zip
          user_access: [ssl_mica_diego]
      views:
        MDS_Diabetes_Antwerp:
          file: MDS_Diabetes_Antwerp.xml
          tables: [diabetes_antwerp]
          user_access: [ssl_mica_diego]

mica:
  url: http://localhost:7880/mica
  username: mica
  password: mica
  studies:
    regressiontest study:
      summary: A dummy used in automated testing
  datasets:
    regressiontest dataset: 
      studies:
        regressiontest study:
          url: https://10.0.2.2:8443/
          dataset: regression_test_project
          table: MDS_Diabetes_Antwerp
      queries:
        Query test 1:
          variables:
            biobank_id: {}
            donor_age_sampling: {range: [300, '']}
            sample_date: {range: ['', 2005-1-1]}
          result:
            regressiontest study:
              - {study: regressiontest study}
              - {variable: Matched, items: 101, donors: 37}
              - {variable: biobank_id, items: 494, donors: 114}
              - {variable: donor_age_sampling, items: 162, donors: 55}
              - {variable: sample_date, items: 372, donors: 113}
              - {variable: Total, items: 494, donors: 114}
""")



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

    print("page title: " + browser.title)

    assert not browser.loggedIn()
    print("logging in")
    browser.logIn(conf.mica.username, conf.mica.password)
    assert browser.onPage(HomePage)
    assert browser.loggedIn()

    for study, studydata in conf.mica.studies.items():
        print('looking for study '+study)
        browser.gotoStudies()
        if browser.hasStudy(study):
            print('deleting study '+study)
            browser.gotoStudy(study)
            browser.gotoEdit()
            browser.delete()
            browser.gotoStudies()
        print("creating new study "+study)
        create_study(browser, study, studydata.summary)

    for dataset, datasetdata in conf.mica.datasets.items():
        datasetname = dataset+' v1'
        browser.gotoDatasets()
        print("looking for dataset "+datasetname)
        if browser.hasDataset(datasetname):
            print("deleting dataset "+datasetname)
            browser.gotoDataset(datasetname)
            browser.gotoEdit()
            browser.delete()
        print("creating new dataset "+dataset)
        create_dataset(browser, dataset)

        print("Connecting studies to dataset")
        browser.gotoDatasets()
        browser.gotoDataset(datasetname)
        browser.gotoEditStudies()
        for study, connectiondata in datasetdata.studies.items():
            if browser.hasStudy(study):
                browser.deleteStudy(study)
            browser.addStudy(study)
            browser.configureStudy(study, connectiondata.url, connectiondata.dataset, connectiondata.table)
        print("Testing connection")
        browser.testConnections()
        browser.gotoDataset()

        print('Importing variables')
        browser.importVariables()

        for query, querydata in datasetdata.queries.items():
            print("Creating "+query)
            browser.gotoQueries()
            if browser.hasQuery(query):
                browser.deleteQuery(query)
            browser.createQuery()
            browser.setName(query)
            for variable, args in querydata.variables.items():
                browser.addVariable(variable, **args)
            browser.save()
            browser.gotoQueries()

            print("Running query")
            browser.gotoQuery('Query test 1')
            result = browser.result()
            print("result matches: "+ str(result == querydata.result))


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

def remove_mica_data(browser):
    if not browser.loggedIn():
        print("logging in")
        browser.logIn(conf.mica.username, conf.mica.password)

    browser.gotoDatasets()
    for dataset, datasetdata in conf.mica.datasets.items():
        datasetname = dataset+' v1'
        if browser.hasDataset(datasetname):
            print("deleting dataset "+datasetname)
            browser.gotoDataset(datasetname)
            browser.gotoEdit()
            browser.delete()

    browser.gotoStudies()
    for study, studydata in conf.mica.studies.items():
        if browser.hasStudy(study):
            print('deleting study '+study)
            browser.gotoStudy(study)
            browser.gotoEdit()
            browser.delete()
            browser.gotoStudies()



def test_opal():
    global opal
    browser = opal = Browser(newdriver(), conf.opal.url, LoginPage)
    return load_opal_data(browser)


def load_opal_data(browser):
    browser.ensureLoggedIn(conf.opal.username, conf.opal.password)
    browser.gotoProjects()
    assert browser.onPage(Projects)
    
    for project, projectdata in conf.opal.projects.items():
        if browser.hasProject(project):
            print("project '{}' already exists, skipping project creation".format(project))
        else:
            print("creating project "+project)
            browser.createProject(project)
        assert browser.hasProject(project)

        browser.gotoProject(project)
        tables = browser.tables()
        print("tables: "+', '.join(tables))
        for table, tabledata in projectdata.tables.items():
            if browser.hasTable(table):
                print('removing table '+table)
                browser.removeTable(table)
            print('importing table '+table)
            browser.importTable(os.path.abspath(tabledata.file), table)
            assert browser.hasTable(table)
            print("indexing table "+table)
            browser.gotoTable(table)
            browser.gotoSummary()
            browser.index()
            print("setting permissions on "+table)
            browser.gotoPermissions()
            for user in tabledata.get('user_access', ()):
                if not browser.getPermission(user):
                    browser.addUserPermission(user, 'View dictionary and summaries')
            browser.gotoProject()

        for view, viewdata in projectdata.views.items():
            if browser.hasTable(view):
                print('removing view '+view)
                browser.removeTable(view)
            print("importing view "+view)
            browser.importView(view, viewdata.tables, os.path.abspath(viewdata.file))
            print("indexing view "+view)
            browser.gotoSummary()
            browser.index()
            print("setting permissions on "+view)
            browser.gotoPermissions()
            for user in viewdata.get('user_access', ()):
                if not browser.getPermission(user):
                    browser.addUserPermission(user, 'View dictionary and summaries')
            browser.gotoProject()

def remove_opal_data(browser):
    browser.ensureLoggedIn(conf.opal.username, conf.opal.password)
    for project, projectdata in conf.opal.projects.items():
        print("removing project "+project)
        browser.gotoProjects()
        if not browser.hasProject(project):
            print("project '{}' not found, cannot remove it".format(project))
            return
        browser.gotoProject(project)
        print("removing tables from project "+project)
        browser.removeAllTables()
        browser.removeProject()
    

if __name__ == '__main__':
    print('Testing Opal and loading data')
    test_opal()
    print('Testing Mica')
    test_mica()

