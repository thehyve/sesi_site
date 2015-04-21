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
        sd.get(self.base_url + "/")
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
        self.sd.get(self.base_url + "/?q=admin/people/permissions/2")

        #change permissions for authenticated user
        chkbox = self.css("#edit-2-view-any-dataset-query")
        self.setcheckbox(chkbox, True)

        chkbox = self.css("#edit-2-create-edit-delete-own-dataset-query")
        self.setcheckbox(chkbox, True)
        
        chkbox = self.css("#edit-2-use-text-format-full-html")
        self.setcheckbox(chkbox, True)
        
        chkbox = self.css("#edit-2-import-csv-variables-feeds")
        self.setcheckbox(chkbox, True)
        
        chkbox = self.css("#edit-2-create-data-access-request-content")
        self.setcheckbox(chkbox, True)
       

        # ----------------------------
        # Permission setting for Forum 
        # ----------------------------
        chkbox = self.css("#edit-2-create-forum-content")
        self.setcheckbox(chkbox, False)

        chkbox = self.css("#edit-2-edit-own-forum-content")
        self.setcheckbox(chkbox, False)

        chkbox = self.css("#edit-2-delete-own-forum-content")
        self.setcheckbox(chkbox, False)
        # ----------------------------

        self.clickon('#edit-submit')

    def changePermCommunity(self):
        self.sd.get(self.base_url + "/?q=admin/config/group/permissions/node/community")

        chkbox = self.css("#edit-2-create-data-access-request-form-content")
        self.setcheckbox(chkbox, True)

        #member
        self.setcheckbox(self.css('#edit-2-create-community-document-content'), True )
        self.setcheckbox(self.css('#edit-2-update-own-community-document-content'), True )
        self.setcheckbox(self.css('#edit-2-update-any-community-document-content'), False )
        self.setcheckbox(self.css('#edit-2-delete-own-community-document-content'), True )
        self.setcheckbox(self.css('#edit-2-delete-any-community-document-content'), False )

        #group admin 
        entities=['community-document','dataset','event','study','study-variable-attributes','variable','article','data-access-request-form']
        actions =['create','update-own','update-any','delete-own','delete-any']
        for ent in entities:
            for act in actions:
                self.setcheckbox(self.css("#edit-3-%s-%s-content" % (act,ent)), True)                

        self.clickon('#edit-submit')

    def changePermDefaultCommunity(self):
        self.sd.get(self.base_url + "/?q=admin/config/group/permissions/node/default_community")

        chkbox = self.css("#edit-5-create-data-access-request-form-content")
        self.setcheckbox(chkbox, True)

        #group admin 
        entities=['community-document','dataset','event','study','study-variable-attributes','variable','article','data-access-request-form']
        actions =['create','update-own','update-any','delete-own','delete-any']
        for ent in entities:
            for act in actions:
                self.setcheckbox(self.css("#edit-6-%s-%s-content" % (act,ent)), True)                


        self.clickon('#edit-submit')

 
    def changePermConsAdmin(self):
        self.sd.get(self.base_url + "/?q=admin/people/permissions/4")

        chkbox = self.css("#edit-4-administer-taxonomy")
        self.setcheckbox(chkbox, True)
        
        chkbox = self.css("#edit-4-access-toolbar")
        self.setcheckbox(chkbox, False)

        chkbox = self.css("#edit-4-access-user-contact-forms")
        self.setcheckbox(chkbox, True)

        chkbox = self.css("#edit-4-access-user-profiles")
        self.setcheckbox(chkbox, True)

        # changes
        chkbox = self.css("#edit-4-bypass-workbench-moderation")
        self.setcheckbox(chkbox, True)

        chkbox = self.css("#edit-4-view-any-unpublished-content")
        self.setcheckbox(chkbox, False)

        #disable permissions
        entities = ['page', 'forum', 'data-access-review', 'documents', 'teleconference', 'blog']
        actions = ['create', 'edit-own', 'edit-any', 'delete-own', 'delete-any']
        for ent in entities:
            for act in actions:
                self.setcheckbox(self.css("#edit-4-%s-%s-content" % (act,ent)), False)

        #activate permissions
        entities=['contact']
        actions =['create','edit-own','edit-any','delete-own','delete-any']
        for ent in entities:
            for act in actions:
                self.setcheckbox(self.css("#edit-4-%s-%s-content" % (act,ent)), True)

        #activate field permissions
        for act in ['create', 'edit-own', 'edit', 'view-own', 'view']:
            self.setcheckbox(self.css('#edit-4-%s-field-project-visibility' % act), True)

        self.clickon('#edit-submit')

    def changeDACF(self):
        self.sd.get(self.base_url + "/?q=admin/people/permissions/4")

        chkbox = self.css("#edit-node-preview-0")
        self.setcheckbox(chkbox, True)
        
        self.clickon('#edit-submit')
    
    def changeEnableContactForm(self):
        driver=self.sd    

        driver.get(self.base_url + "/?q=admin/structure/menu/manage/main-menu")
        try: 
            driver.find_element_by_link_text('Contact')
            return True
        except:
            pass

        print "Creating contact menu link"
        #create Contact menu link
        driver.find_element_by_css_selector("ul.action-links > li > a").click()
        driver.find_element_by_css_selector("#edit-link-title").send_keys("Contact")
        driver.find_element_by_css_selector("#edit-link-path").send_keys("contact")
        Select(driver.find_element_by_css_selector("#edit-parent")).select_by_visible_text("-- About")
        Select(driver.find_element_by_css_selector("#edit-weight")).select_by_visible_text("10")
        
        self.clickon('#edit-submit')

    def selectCaptchaContactForm(self):
        driver=self.sd    
        driver.get(self.base_url + "/?q=admin/config/people/captcha")
        Select(driver.find_element_by_id("edit-captcha-form-id-overview-captcha-captcha-points-contact-site-form-captcha-type")).select_by_visible_text("Image (from module image_captcha)")
        driver.find_element_by_id("edit-submit").click()

    def createLinksOnCommunityHome(self):
        
        #article
        self.sd.get(self.base_url + "/?q=admin/structure/types/manage/article/fields/og_group_ref")
        chkbox = self.sd.find_element_by_xpath("//*[@id='edit-instance-settings-behaviors-prepopulate-status']")
        self.setcheckbox(chkbox, True)
        self.clickon('#edit-submit')
        
        #event
        self.sd.get(self.base_url + "/?q=admin/structure/types/manage/event/fields/og_group_ref")
        chkbox = self.sd.find_element_by_xpath("//*[@id='edit-instance-settings-behaviors-prepopulate-status']")
        self.setcheckbox(chkbox, True)  
        self.clickon('#edit-submit')

        #study
        self.sd.get(self.base_url + "/?q=admin/structure/types/manage/study/fields/og_group_ref")
        chkbox = self.sd.find_element_by_xpath("//*[@id='edit-instance-settings-behaviors-prepopulate-status']")
        self.setcheckbox(chkbox, True)
        self.clickon('#edit-submit')


    def changeCommunityProjectVisibilityDefault(self):
        self.sd.get(self.base_url + "/?q=admin/structure/types/manage/community/fields/field_project_visibility")
        radio = self.sd.find_element_by_css_selector("#edit-field-project-visibility-und-0")
        radio.click()
        self.clickon('#edit-submit')

    def _selectPublishingOptions(self):
        elems = self.sd.find_elements_by_xpath("//strong[contains(., 'Publishing options')]")
        if len(elems)==0:
            raise NoSuchElementException("Cannot find tab 'Publishing Options'")
        tab = elems[0]
        tab.click()

    def disableCommunityPromoteToFrontPage(self):
        self.sd.get(self.base_url + "/?q=admin/structure/types/manage/community")

        self._selectPublishingOptions()
        self.setcheckbox(self.css("#edit-node-options-promote"), False)
        self.clickon('#edit-submit')

    def changePublishingOptionsDataAccessRequestForm(self):
        self.sd.get(self.base_url + "/?q=admin/structure/types/manage/data-access-request-form")

        self._selectPublishingOptions()
        self.setcheckbox(self.css("#edit-node-options-promote"), False)
        self.setcheckbox(self.css("#edit-node-options-status"), False)
        self.clickon('#edit-submit')


if __name__ == "__main__":

    print '''
                    (                 )
          (   (     )\ )           ( /(
     (    )\  )\ ) (()/(   (       )\())
 (   )\  ((_)(()/(  /(_)) ))\  (  ((_)\\
 )\ ((_)  _   ((_))(_))  /((_) )\  _((_)
((_)| __|| |  _| | | _ \(_))( ((_)| || |
(_-<| _| | |/ _` | |   /| || |(_-<| __ |
/__/|___||_|\__,_| |_|_\ \_,_|/__/|_||_|


    '''

    suite = None
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
           suite.changePermDefaultCommunity()
           suite.changePermCommunity()
           suite.changeEnableContactForm()
           suite.selectCaptchaContactForm()
           suite.changeCommunityProjectVisibilityDefault()
           suite.disableCommunityPromoteToFrontPage()
           suite.changePublishingOptionsDataAccessRequestForm()

    finally:
        if suite:
            suite.destroy()

