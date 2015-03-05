#!/usr/bin/env python
from __future__ import unicode_literals, print_function

import sys
import time
import re
import httplib
from collections import OrderedDict

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

    def waitForProcessing(self, timeout=300):
        self.waitForCondition(lambda: not self.header() == 'Processing' or 
                                  self.elementExists(css='p.error', contains_text='An error has occured'), 
                              timeout=timeout)



class NamedMicaPage (MicaPage):
    def __init__(self, driver, name):
        super(NamedMicaPage, self).__init__(driver)
        self.name = name


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


class Dataset (NamedMicaPage):
    def onPage(self):
        return self.header() == self.name

    def gotoEdit(self):
        self.clickLink('New draft')
        return DatasetEdit(self.driver, self.name).waitFor()

    def gotoEditStudies(self):
        self.clickLink('Edit Studies')
        return DatasetStudies(self.driver, self.name).waitFor()

    def importVariables(self):
        self.clickLink('Import Variables')
        self.waitForProcessing()
        if not self.hasMessage('Import finished'):
            raise StandardError('Importing variables failed')

    def gotoQueries(self):
        self.clickLink('Queries')
        return Queries(self.driver, self.name).waitFor()
        

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


class DatasetEdit (NamedMicaPage, DatasetCreate):
    def onPage(self):
        return self.header() == 'Edit Dataset '+self.name
    
    def delete(self):
        self.clickButton('Delete')
        self.waitForCondition(lambda: self.header() == 'Are you sure you want to delete {}?'.format(self.name))
        self.clickButton('Delete')
        self.waitForProcessing()
        d = Datasets(self.driver).waitFor()
        if not self.hasMessage('Dataset successfully deleted'):
            raise StandardError("Deleting dataset {} failed".format(self.name))
        return d

class DatasetStudies (NamedMicaPage):
    #fieldquery = 'form#dataset-connectors table.table td a'
    fieldxpath = "form[@id='dataset-connectors']//table[%s]//td" % xpath_class('table')

    def onPage(self):
        return self.header() == self.name + ' -- Studies'

    def hasStudy(self, study):
        return self.elementExists(xpath=contains(self.fieldxpath, study))

    def addStudy(self, study):
        self.findElement(css='option', text=study).click()
        self.clickButton('Add Study')

    def deleteStudy(self, study):
        self.findElement(xpath=contains(self.fieldxpath, study)+
                         "/preceding-sibling::td//input[@type='checkbox']").click()
        self.clickButton('Delete selected items')
        

    def configureStudy(self, study, server, datasource, table):
        self.findElement(xpath=contains('/following-sibling::td//a', 'Edit', 
                                        prefix=contains(self.fieldxpath, study))).click()
        conntypeoption = 'div.modal-content select#edit-connection-type option'
        self.waitForCondition(C.element_visible(css=conntypeoption, text='Opal'))
        self.findElement(css=conntypeoption, text='Opal').click()
        self.waitForCondition(C.element_visible(css='input#edit-opal-url'))
        clear_send(self.findElement(css='input#edit-opal-url'), server)
        clear_send(self.findElement(css='input#edit-datasource'), datasource)
        clear_send(self.findElement(css='input#edit-table'), table)
        self.clickButton('Save')
        self.waitForCondition(lambda: not self.elementExists(css='div.modal-content'), timeout=15)
        if not self.elementExists(xpath=contains('/following-sibling::td', 'Opal',
                                                 prefix=contains(self.fieldxpath, study))):
            raise StandardError('Failed to configure study {}'.format(study))
        return

    def testConnections(self):
        self.clickButton('Test connections')
        # update: This seems to work now that the configureStudy method doesn't confuse xpath and css selectors anymore
        # Somehow if a request is made too quickly at this point we trigger a selenium error,
        # and the browser returns an empty status line to selenium triggering an exception. 
        # succes = False
        # while not succes:
        #     try:
        #         self.waitForCondition(C.element_visible(css='div.alert'))
        #         succes = True
        #     except httplib.BadStatusLine as e:
        #         print('caught known error BadStatusLine: {}, retrying'.format(e), file=sys.stderr)
        #         time.sleep(1)
        self.waitForCondition(C.element_visible(css='div.alert'))
        if not self.hasMessage('All connections are successful'):
            errtxt = '\n'.join(e.text for e in self.driver.find_elements(css='div.alert.alert-error'))
            raise StandardError('Connecting to Opal failed: '+errtxt)

    def gotoDataset(self):
        self.findElement(css='ul.breadcrumb li:last-of-type a').click()
        return Dataset(self.driver, self.name).waitFor()
        

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

        
class Study (NamedMicaPage):
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


class StudyEdit (NamedMicaPage, StudyCreate):
    def onPage(self):
        return self.header() == 'Edit Study '+self.name
    
    def delete(self):
        self.clickButton('Delete')
        assert self.header() == 'Are you sure you want to delete {}?'.format(self.name)
        self.clickButton('Delete')
        self.waitForProcessing()
        s = HomePage(self.driver).waitFor()
        if not self.hasMessage('Study {} has been deleted'.format(self.name)):
            raise StandardError("Deleting study {} failed".format(self.name))
        return s


class Queries (NamedMicaPage):
    def onPage(self):
        return (self.header() == self.name + ' -- Queries' and 
                self.elementExists(css='div.main-container table.table'))

    def _fieldquery(self, query):
        return ('//table[%s]' % xpath_class('table'))+ "//td[.//text() = %s]" % xpath_string_escape(query)

    def createQuery(self):
        self.clickLink('Add Query')
        return QueryAdd(self.driver, self.name).waitFor()

    def hasQuery(self, query):
        return self.elementExists(xpath=self._fieldquery(query))

    def gotoQuery(self, query):
        self.findElement(xpath=self._fieldquery(query)+'/a').click()
        return QueryResult(self.driver, self.name, query).waitFor()

    def deleteQuery(self, query):
        self.findElement(xpath=self._fieldquery(query)
                         +contains('following-sibling::td//a', 'Delete', prefix='/')).click()
        self.waitForCondition(lambda: self.elementExists(css='div.modal-content button'))
        self.clickButton('Delete')
        self.waitForCondition(lambda: not self.hasQuery(query))


class QueryEdit (MicaPage):
    def __init__(self, driver, datasetname, queryname=None):
        super(QueryEdit, self).__init__(driver)
        self.datasetname = datasetname
        self._queryname = queryname

    @property
    def queryname(self):
        if self._queryname == None:
            self._queryname = self.findElement(css='input#edit-name').get_attribute('value')
        return self._queryname

    def onPage(self):
        return self.header() == self.name + ' -- Edit Query'

    def gotoDataset(self):
        self.clickLink(self.datasetname)
        return Dataset(self.driver, self.datasetname)

    def setName(self, name):
        clear_send(self.findElement(css='input#edit-name'), name)
        self._queryname = name

    def addVariable(self, variable, values=None, any_value=None, exact_value=None, range=None, in_=True):
        if sum(int(bool(x)) for x in (values, any_value, exact_value, range)) > 1:
            raise TypeError('Only one of values, any_value, exact_value or range can be specified')

        self.findElement(xpath="//table[@id='variables']"+contains('td', variable)+
                         '/following-sibling::td[last()]//a').click()
        self.waitForCondition(lambda: self.elementExists(css='div#modal-content button'))
        if in_ == False:
            self.findElement(css="select#edit-inverted option[value='notin']").click()
        if values is not None:
            clear_send(self.findElement(css='input#edit-values'), values)

        if any_value:
            self.findElement(css='input#edit-exact-radio-exists').click()
        if exact_value is not None:
            self.findElement(css='input#edit-exact-radio-exact').click()
            clear_send(self.findElement(css='input#edit-values'), exact_value)
        if range is not None:
            self.findElement(css='input#edit-exact-radio-range').click()
            clear_send(self.findElement(css='input#edit-min'), range[0])
            clear_send(self.findElement(css='input#edit-max'), range[1])

        self.findElement(css='div.modal-content button', text='Save').click()
        self.waitForCondition(lambda: self.elementExists(xpath="//table[@id='queryterms']"
                                                         +contains('td', variable)), 
                              timeout=15)

    def save(self):
        self.clickButton('Save and Run')
        return QueryResult(self.driver, self.datasetname, self.queryname).waitFor()
        


class QueryAdd (QueryEdit):
    def onPage(self):
        return self.header() == self.datasetname + ' -- Add Query'


class QueryResult (MicaPage):
    def __init__(self, driver, datasetname, queryname):
        super(QueryResult, self).__init__(driver)
        self.datasetname = datasetname
        self.queryname = queryname

    def onPage(self):
        return self.header() == self.datasetname + ' -- ' + self.queryname

    def gotoEdit(self):
        self.clickLink('Edit')
        return QueryEdit(self.driver, self.datasetname, self.queryname)

    def gotoDataset(self):
        self.clickLink(self.datasetname)
        return Dataset(self.driver, self.datasetname)

    def gotoQueries(self):
        self.clickLink('Queries')
        return Queries(self.driver, self.datasetname)

    def result(self):
        table = self.findElement(css='div#result-wrapper table.query-table')
        headers = [e.text.split('\n')[0].split(' :')[0] 
                   for e in table.find_elements(css='tr:first-child th')]
        num_fixed_headers = 3 # Study, Matched, Total
        if len(headers) <= num_fixed_headers:
            raise StandardError("Result table incomplete. Headers found: "+', '.join(headers))
        
        variables = headers[2:-1]
        result = OrderedDict()

        rowidx = 1
        data = [e.text for e in table.find_elements(css='tr:nth-child({}) td'.format(rowidx))]
        while data:
            if len(data) != len(headers):
                raise StandardError("Error: Length of data does not match length of header.\nheader: {}\ndata: {}"
                                    .format(', '.join(headers), ', '.join(data)))
            row = [OrderedDict(study=data[0])]
            for i, d in enumerate(data[1:], 1):
                match = re.match(r'(?P<items>.*) items( \((?P<percent>.*)%\))?\n(?P<donors>.*) donors', d)
                cell = OrderedDict(variable=headers[i])
                cell['items'] = int(match.group('items'))
                cell['donors'] = int(match.group('donors'))
                row.append(cell)
            result[data[0]] = row
            rowidx += 1
            data = [e.text for e in table.find_elements(css='tr:nth-child({}) td'.format(rowidx))]
        return result


            
            
        


def clear_send(element, keys):
    element.clear()
    element.send_keys(keys)
