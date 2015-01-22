from __future__ import unicode_literals, division, absolute_import, print_function

import inspect
from collections import namedtuple
from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver.common.by import By


__all__ = ['Locator', 'css', 'class_name', 'id', 'link_text', 'name', 
           'partial_link_text', 'tag', 'xpath', 'locator_from_args', 
           'find_element', 'find_elements']


locator_keys = dict(
    css = By.CSS_SELECTOR,
    class_name = By.CLASS_NAME,
    id = By.ID,
    link_text = By.LINK_TEXT,
    name = By.NAME,
    partial_link_text = By.PARTIAL_LINK_TEXT,
    tag = By.TAG_NAME,
    xpath = By.XPATH,
)

# Inherit from a namedtuple so that a Locator can easily be converted to the 
# format that selenium webdriver expects. This should be considered an 
# implementation detail and not relied on. 
class Locator (namedtuple('Locator', ('key', 'value'))):
    contains_text = None

    def __new__(cls, key, value=None, contains_text=None):
        if value == None:
            value = key
            key = cls.__name__
        key = locator_keys[key]
        obj = super(Locator, cls).__new__(cls, key, value)
        if contains_text:
            obj.contains_text = contains_text
        return obj

    def __repr__(self):
        return '{0}({1}{2})'.format(type(self).__name__, repr(self.value), 
                                    ", contains_text="+repr(self.contains_text) if hasattr(self, 'contains_text') else '')

    # A separate implementation for the find_element(s) methods for efficiency reasons. We could always call
    # driver.find_elements, but that potentially returns a large list of data from the browser 
    # that we don't need.
    def _find_element(self, driver):
        if not self.contains_text:
            return driver.find_element(self.key, self.value)
        elems = [e for e in driver.find_elements(self.key, self.value) if self.contains_text in e.text]
        if not elems:
            raise NoSuchElementException("Unable to locate element: "+repr(self))
        return elems[0]

    def _find_elements(self, driver):
        if not locator.contains_text:
            return driver.find_elements(self.key, self.value)
        return [e for e in driver.find_elements(self.key, self.value) if locator.contains_text in e.text]

    def _has_element(self, driver):
        try:
            self._find_element(driver)
            return True
        except InvalidSelectorException:
            # don't hide invalid xpath selectors
            raise
        except NoSuchElementException:
            return False


class css (Locator): pass
class class_name (Locator): pass
class id (Locator): pass
class link_text (Locator): pass
class name (Locator): pass
class partial_link_text (Locator): pass
class tag (Locator): pass
class xpath (Locator): pass

locators = dict()
for cls in Locator.__subclasses__():
    locators[cls.__name__] = cls

def locator_from_args(locator, kwargs, stackdepth=1):
    if locator == None:
        locator = kwargs.get('locator')
        locator_keys_ = locator_keys
        for key in kwargs.keys():
            if key in locator_keys_:
                if locator:
                    raise TypeError("Multiple locators specified in call to {}. Use only one argument named {} or locator.".format(
                        inspect.stack()[stackdepth][3], ', '.join(locator_keys.keys())))
                locator = locators[key](kwargs[key])
    if 'contains_text' in kwargs:
        locator.contains_text = kwargs['contains_text']
    return locator
