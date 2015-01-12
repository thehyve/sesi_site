# -*- coding: utf-8 -*-
import sys
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import Select
from selenium.common.exceptions import NoSuchElementException
from selenium.common.exceptions import NoAlertPresentException
import unittest, time, re

'''
Base selenium 
'''

class SeleniumBase(unittest.TestCase):
    
    def __init__(self, base_url):
        self.base_url = base_url

        self.sd = webdriver.Firefox()
        #self.sd = webdriver.PhantomJS()
        self.sd.implicitly_wait(15)
        self.verificationErrors = []
        self.accept_next_alert = True
        print "created sd"

    def login(self):
        sd = self.sd
        print "login"
        sd.get(self.base_url + "/mica/")
        sd.find_element_by_css_selector("#edit-name").clear()
        sd.find_element_by_css_selector("#edit-name").send_keys(self.username)
        sd.find_element_by_css_selector("#edit-pass").clear()
        sd.find_element_by_css_selector("#edit-pass").send_keys(self.passwd)
        sd.find_element_by_css_selector("#edit-submit--2").click()
        try: sd.find_element_by_link_text('Log out')
        except:
            print "Unable to login with %s / %s " % (self.username, self.passwd)
            return False
            
        print "login - done"
        return True
    
        
    def destroy(self):
        print "quiting.."
        self.sd.quit()


    def setcheckbox(self, chkbox, value):
        print "setcheckbox %s = %s" % (chkbox.get_attribute ('value'), value)
        result = ''
        
        if value:
            if not chkbox.is_selected():
                chkbox.click()
        else:
            if chkbox.is_selected():
                chkbox.click()



    def is_element_present(self, how, what):
        try: self.sd.find_element(by=how, value=what)
        except NoSuchElementException, e: return False
        return True
    
    def is_alert_present(self):
        try: self.sd.switch_to_alert()
        except NoAlertPresentException, e: return False
        return True
    
    def close_alert_and_get_its_text(self):
        try:
            alert = self.sd.switch_to_alert()
            alert_text = alert.text
            if self.accept_next_alert:
                alert.accept()
            else:
                alert.dismiss()
            return alert_text
        finally: self.accept_next_alert = True

    def clickon(self, selector): 
        print "clickon %s" % selector  
        self.sd.find_element_by_css_selector(selector).click()

    def css(self, selector):
        return self.sd.find_element_by_css_selector(selector)

'''

'''
class Drush(SeleniumBase):

    def __init__(self, url, username, passwd):
        SeleniumBase.__init__(self, url)
        self.username = username
        self.passwd = passwd
    
    def changePermissions(self):
        self.sd.get(self.base_url + "/mica/?q=admin/people/permissions/2")

        #change permissions for authenticated user
        chkbox = self.css("#edit-2-view-any-dataset-query")
        self.setcheckbox(chkbox, True)

        chkbox = self.css("#edit-2-create-edit-delete-own-dataset-query")
        self.setcheckbox(chkbox, True)
        
        chkbox = self.css("#edit-2-use-text-format-full-html")
        self.setcheckbox(chkbox, True)
        
        chkbox = self.css("#edit-2-import-csv-variables-feeds")
        self.setcheckbox(chkbox, True)
               
        self.clickon('#edit-submit')

        
    def changePermConsAdmin(self):
        self.sd.get(self.base_url + "/mica/?q=admin/people/permissions/4")

        chkbox = self.css("#edit-4-administer-taxonomy")
        self.setcheckbox(chkbox, True)
        
        chkbox = self.css("#edit-4-access-toolbar")
        self.setcheckbox(chkbox, False)
        
        self.clickon('#edit-submit')
               
        
if __name__ == "__main__":

    try:
       if len(sys.argv) == 4:
           print sys.argv[1]
           suite = Drush(sys.argv[1], sys.argv[2], sys.argv[3])
       else:
           print "using localhost"
           suite = Drush('http://localhost/','mica','mica')

       if suite.login():       
           suite.changePermissions()
           suite.changePermConsAdmin()

    finally:
        suite.destroy();

