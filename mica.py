#!/usr/bin/env python
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By

from pylenium import Pylenium
import pylenium.conditions as C

from browser import Page
from helpers import *


class MicaPage (Page):
    def loggedIn(self):
        self.ensureScreenWidth()
        return C.element_present(link_text='User menu').test(self.driver)

    def ensureScreenWidth(self):
        size = self.driver.window_size
        if size[0] < 1050:
            self.driver.window_size = (1050, size[1])
        assert self.driver.window_size[0] >= 1050

    def clickDropdown(self, menu, link):
        if not self.elementExists(link_text=link):
            self.clickLink(menu)
        self.clickLink(link)

    def gotoDatasets(self):
        self.clickDropdown('Resources', 'Datasets')
        return Datasets(self.driver).waitFor()

    def gotoStudies(self):
        self.clickDropdown('Resources', 'Studies')
        return Studies(self.driver).waitFor()

    def clickButton(self, name):
        self.findElement(xpath=contains('button', name)).click()

    def header(self):
        hs = self.driver.find_elements(tag='h1')
        if len(hs) != 1:
            return None
        return hs[0].text

    def hasMessage(self, msg, type='success'):
        assert type in ('success', 'warning', 'error')
        return self.elementExists(css='div.alert.alert-'+type, contains_text=msg)


class Autologout (MicaPage):
    def onPage(self):
        return not self.loggedIn() and self.elementExists(css='div.alert.alert-succes', contains_text='You have been logged out')


class HomePage (MicaPage):
    def onPage(self):
        return self.header() == 'CMI - Center for Medical Innovation vzw'

    def ensureLoggedIn(self, username, password):
        if not self.loggedIn():
            self.logIn(username, password)
        assert self.loggedIn()

    def logIn(self, username, password):
        usernamefield = self.driver.find_element(id='edit-name')
        usernamefield.send_keys(username)
        passwordfield = self.driver.find_element(id='edit-pass')
        passwordfield.send_keys(password)
        passwordfield.submit()
        self.driver.wait_until(C.any(C.element_visible(link_text='User menu'), 
                                        C.element_visible(css='div.alert.alert-error')))
        
    def logOut(self):
        assert self.loggedIn()
        self.clickDropdown('User menu', 'Log out')


class Paged (object):
    def __init__(self, *args):
        super(Paged, self).__init__(*args)
        self.loadPagination()

    def loadPagination(self):
        self.pages = {int(e.text): e for e in self.driver.find_elements(css='div.pagination li a') if e.text.isdigit()}

    def numPages(self):
        if not self.pages:
            return 1
        return max(self.pages.keys())

    def currentPage(self):
        if not self.pages:
            return 1
        return int(self.findElement(css="div.pagination li a[href='#']").text)

    def gotoPage(self, num):
        if self.currentPage() == num:
            return
        self.pages[num].click()
        self.loadPagination()


class Paginator (object):
    def __init__(self, page):
        self.page = page

    def __enter__(self):
        self.startpage = self.page.currentPage()
        return self

    def __exit__(self, *exc_info):
        # don't move back if we navigated away from our list
        if self.page.onPage():
            self.page.gotoPage(self.startpage)

    def __iter__(self):
        self.currentpage = 0
        return self

    def next(self):
        if self.currentpage >= self.page.numPages():
            raise StopIteration()
        self.currentpage += 1
        self.page.gotoPage(self.currentpage)
        return self.currentpage
        

class ViewsTable (Paged):
    #fieldquery = <abstract>

    def items(self):
        items = []
        with Paginator(self) as pages:
          for p in pages:
            items.extend(e.text for e in self.driver.find_elements(css=self.fieldquery))
        return items

    def hasItem(self, item):
        with Paginator(self) as pages:
          for p in pages:
            if self.driver.find_elements(css=self.fieldquery, contains_text=item):
                return True
        return False

    def clickItem(self, item):
        with Paginator(self) as pages:
          for p in pages:
            for link in self.driver.find_elements(css=self.fieldquery, text=item):
                link.click()
                return
        raise ValueError('{} not found'.format(item))


#
# Note: The Datasets/DatasetXxx classes are almost exactly equivalent to the Studies/StudyXxx classes. 
# Todo: Factor them out some time. 
#

class Datasets (ViewsTable, MicaPage):
    fieldquery = 'table.views-table td.views-field.views-field-title a'

    def onPage(self):
        return self.header() == 'Datasets'

    def newDataset(self):
        self.clickLink('Add a Dataset')
        return DatasetCreate(self.driver).waitFor()

    def datasets(self):
        return self.items()

    def hasDataset(self, dataset):
        return self.hasItem(dataset)

    def gotoDataset(self, dataset):
        self.clickItem(dataset)
        return Dataset(self.driver, dataset).waitFor()

        
class Dataset (MicaPage):
    def __init__(self, driver, name):
        super(Dataset, self).__init__(driver)
        self.name = name

    def onPage(self):
        return self.header() == self.name

    def gotoEdit(self):
        self.clickLink('New draft')
        return DatasetEdit(self.driver, self.name).waitFor()

    def gotoEditStudies(self):
        self.clickLink('Edit Studies')
        return DatasetStudies(self.driver, self.name).waitFor()
        

class DatasetCreate (MicaPage):
    def onPage(self):
        return self.header() == 'Create Dataset'

    def setName(self, name):
        self.findElement(css='input#edit-title-field-und-0-value').send_keys(name)

    def setTypeStudy(self):
        self.findElement(css='input#edit-field-dataset-type-und-study').click()

    def setTypeHarmonization(self):
        self.findElement(css='input#edit-field-dataset-type-und-harmonization').click()

    def setPublished(self):
        self.findElement(xpath=contains('a', 'Publishing options')).click()
        self.findElement(css='select#edit-workbench-moderation-state-new option[value=published]').click()

    def save(self):
        self.clickButton('Save')
        name = self.header()
        if not self.hasMessage('Dataset {} has been created'.format(name)):
            raise StandardError("Dataset creation failed")
        return Dataset(self.driver, name)        


class DatasetEdit (DatasetCreate):
    def __init__(self, driver, name):
        super(DatasetEdit, self).__init__(driver)
        self.name = name

    def onPage(self):
        return self.header() == 'Edit Dataset '+self.name
    
    def delete(self):
        self.clickButton('Delete')
        self.waitForCondition(lambda: self.header() == 'Are you sure you want to delete {}?'.format(self.name))
        self.clickButton('Delete')
        self.waitForCondition(lambda: self.header() != 'Processing')
        d = Datasets(self.driver).waitFor()
        if not self.hasMessage('Dataset successfully deleted'):
            raise StandardError("Deleting dataset {} failed".format(self.name))
        return d
 
class DatasetStudies (MicaPage):
    def __init__(self, driver, name):
        super(DatasetEdit, self).__init__(driver)
        self.name = name

    def addStudy(self, study):
        self.findElement(css='option', text=study).click()
        self.clickButton('Add Study')


class Studies (ViewsTable, MicaPage):
    fieldquery = 'table.views-table td.views-field.views-field-title-field a'

    def onPage(self):
        return self.header() == 'Studies'

    def newStudy(self):
        self.clickLink('Add new Study')
        return StudyCreate(self.driver).waitFor()

    def studies(self):
        return self.items()

    def hasStudy(self, study):
        return self.hasItem(study)

    def gotoStudy(self, study):
        self.clickItem(study)
        return Study(self.driver, study).waitFor()

        
class Study (MicaPage):
    def __init__(self, driver, name):
        super(Study, self).__init__(driver)
        self.name = name

    def onPage(self):
        return self.header() == self.name

    def gotoEdit(self):
        self.clickLink('New draft')
        return StudyEdit(self.driver, self.name).waitFor()
        

class StudyCreate (MicaPage):
    def onPage(self):
        return self.header() == 'Create Study'

    def setName(self, name):
        self.findElement(css='input#edit-title-field-und-0-value').send_keys(name)

    def setSummary(self, summary):
        self.driver.switch_to.frame(self.findElement(css='div#edit-body div#cke_edit-body-und-0-value iframe'))
        self.findElement(css='html body').send_keys(summary)
        self.driver.switch_to.default_content()

    def setPublished(self):
        self.findElement(xpath=contains('a', 'Publishing options')).click()
        self.findElement(css='select#edit-workbench-moderation-state-new option[value=published]').click()

    def save(self):
        self.clickButton('Save')
        name = self.header()
        if not self.hasMessage('Study {} has been created'.format(name)):
            raise StandardError("Study creation failed")
        return Study(self.driver, name)        


class StudyEdit (StudyCreate):
    def __init__(self, driver, name):
        super(StudyEdit, self).__init__(driver)
        self.name = name

    def onPage(self):
        return self.header() == 'Edit Study '+self.name
    
    def delete(self):
        self.clickButton('Delete')
        assert self.header() == 'Are you sure you want to delete {}?'.format(self.name)
        self.clickButton('Delete')
        self.waitForCondition(lambda: self.header() != 'Processing')
        s = Studies(self.driver).waitFor()
        if not self.hasMessage('Study successfully deleted'):
            raise StandardError("Deleting study {} failed".format(self.name))
        return s
 
