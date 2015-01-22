from __future__ import unicode_literals, division, absolute_import, print_function

import time
import collections
import six
from selenium.webdriver.support import wait as selenium_wait
from selenium.webdriver.support import color, select
from selenium.webdriver.remote import webelement, utils
from selenium.common.exceptions import NoSuchElementException, StaleElementReferenceException, NoSuchFrameException, TimeoutException, InvalidSelectorException

from locator import locator_from_args, find_element, find_elements
import conditions

TIMEOUT = 3
POLL = 0.5
IGNORED_EXCEPTIONS = (NoSuchElementException, StaleElementReferenceException)


class Pylenium (object):
    def __init__(self, driver):
        self.driver = driver

    @property
    def window_size(self):
        s = self.driver.get_window_size()
        return (s['width'], s['height'])

    @window_size.setter
    def window_size(self, size):
        return self.driver.set_window_size(size[0], size[1])

    def find_element(self, locator=None, **kwargs):
        return locator_from_args(locator, kwargs)._find_element(self.driver)

    def find_elements(self, locator=None, **kwargs):
        return locator_from_args(locator, kwargs)._find_elements(self.driver)

    def has_element(self, locator=None, **kwargs):
        return locator_from_args(locator, kwargs)._has_element(self.driver)

    def wait_until(self, *conditions, **kwargs):
        """An wait until implementation that can wait for multiple conditions"""
        timeout = kwargs.get('timeout', TIMEOUT)
        end_time = time.time() + timeout
        poll_interval = kwargs.get('poll_interval', POLL)
        ignored_exceptions = kwargs.get('ignored_exceptions', IGNORED_EXCEPTIONS)
        message = kwargs.get('message', None)
        while(True):
            for method in conditions:
                try:
                    value = method(self)
                    if value:
                        return value
                except ignored_exceptions:
                    pass
            time.sleep(poll_interval)
            if(time.time() > end_time):
                raise TimeoutException(message)

    def wait_until_not(self, *conds, **kwargs):
        return self.waitUntil(conditions.not_(conditions.any(conds)), **kwargs)

    def create_web_element(self, element_id):
        return WebElement(self.driver.create_web_element(element_id))

    def switch_to_active_element(self):
        return WebElement(self.driver.switch_to_active_element())

    def __getattr__(self, attr):
        if attr.startswith('find_element'):
            raise AttributeError("'{}' object has no attribute '{}', use a Pylenium.locator".format(
                type(self).__name__, attr))
        return getattr(self.driver, attr)

    def __dir__(self):
        d = [k for k in dir(self.driver) if not k.startswith('find_element')]
        d.extend(Pylenium.__dict__.keys())
        return d
        


class WebElement (object):
    def __init__(self, element):
        self.element = element

    def find_element(self, locator=None, **kwargs):
        return locator_from_args(locator, kwargs)._find_element(self.element)

    def find_elements(self, locator=None, **kwargs):
        return locator_from_args(locator, kwargs)._find_elements(self.element)

    def has_element(self, locator=None, **kwargs):
        return locator_from_args(locator, kwargs)._has_element(self.element)

    def __getattr__(self, attr):
        if attr.startswith('find_element'):
            raise AttributeError("'{}' object has no attribute '{}', use a Pylenium.locator".format(
                type(self).__name__, attr))
        return getattr(self.element, attr)
    
    def __dir__(self):
        d = [k for k in dir(self.element) if not k.startswith('find_element')]
        d.extend(WebElement.__dict__.keys())
        return d


class Color (color.Color):
    def __new__(cls, color):
        if isinstance(color, tuple):
            color = 'rgb' + repr(tuple(color))
        return color.Color.from_string(color)

class Select (select.Select):
    def select(**kwargs):
        """Select an option. Named argument must be one of:
        index, value, text."""
        if 'index' in kwargs:
            return self.select_by_index(kwargs['index'])
        elif 'value' in kwargs:
            return self.select_by_value(kwargs['value'])
        elif 'text' in kwargs:
            return self.select_by_visible_text(kwargs['text'])
        else:
            raise TypeError("Select.select requires an argument named 'index', 'value' or 'text'")

    def deselect(**kwargs):
        """Deselect an option. Named argument must be one of:
        index, value, text."""
        if 'index' in kwargs:
            return self.deselect_by_index(kwargs['index'])
        elif 'value' in kwargs:
            return self.deselect_by_value(kwargs['value'])
        elif 'text' in kwargs:
            return self.deselect_by_visible_text(kwargs['text'])
        else:
            raise TypeError("Select.deselect requires an argument named 'index', 'value' or 'text'")

def get_root_parent(element):
    return WebElement(util.get_root_parent(element))

