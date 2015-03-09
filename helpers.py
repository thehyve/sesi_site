from collections import OrderedDict

def css_escape(string, quotes="'"):
    return string.replace(quotes, '\\'+quotes)

def xpath_string_escape(s):
    if "'" not in s: return "'%s'" % s
    if '"' not in s: return '"%s"' % s
    return "concat('%s')" % s.replace("'", "',\"'\",'")

def contains(tag='*', text=None, prefix='//', class_=None):
    c = ''
    if class_ is not None:
        c = xpath_class(class_)+' and '
    return '''%s%s[%s.//text()[contains(., %s)]]''' % (prefix, tag, c, xpath_string_escape(text))

def xpath_class(cls):
    if not cls:
        return '.'
    return '''contains(concat(' ',normalize-space(@class),' '),%s)''' % xpath_string_escape(' '+cls+' ')

class namespace(OrderedDict):
    def __init__(self, *args, **kwargs):
        # Set this to prevent recursion with OrderedDict's methods
        root = []
        object.__setattr__(self, '_OrderedDict__root', root)
        root[:] = [root, root, None]
        object.__setattr__(self, '_OrderedDict__map', {})
        super(namespace, self).__init__(*args, **kwargs)

    def __getattr__(self, attr):
        return self[attr]

    def __setattr__(self, attr, data):
        self[attr] = data

    def __delattr__(self, attr):
        del self[attr]
