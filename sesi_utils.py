import sys
import subprocess
import re
from optparse import OptionParser

'''
LOW LEVEL FUNCTIONS
'''


def drush_sql(sql):
    """
    Run sql query using drush
    :param sql: sql query to run
    :return: array of strings or None if returncode is not zero
    """

    p = subprocess.Popen(["drush", "sqlq", sql], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, err = p.communicate()

    if p.returncode == 0:
        return output.decode("utf-8").split('\n')

    return None


def get_drupal_root():
    ps1 = subprocess.Popen(['drush', 'status'], stdout=subprocess.PIPE)
    ps2 = subprocess.Popen(['grep', 'Drupal root'], stdin=ps1.stdout, stdout=subprocess.PIPE)
    regex = re.search('.*:[ ]*(.*)[ ]*',ps2.communicate()[0])
    return regex.group(1)


def force_disable_module(modulename):
    print "Disabling module: %s" % modulename
    print drush_sql("SELECT status FROM system WHERE name = '%s'" % modulename)
    drush_sql("UPDATE system SET status = '0' WHERE name = '%s'" % modulename)
    drush_sql("DELETE FROM cache_bootstrap WHERE cid = 'system_list'")

'''
HIGHER LEVEL FUNCTIONS
'''


def disable_critical():
    force_disable_module("og_moderation")
    force_disable_module("og_context")
    force_disable_module("entityreference")


if __name__ == '__main__':

    print '''
                         .__             __  .__.__
      ______ ____   _____|__|     __ ___/  |_|__|  |   ______
     /  ___// __ \ /  ___/  |    |  |  \   __\  |  |  /  ___/
     \___ \\\\  ___/ \___ \|  |    |  |  /|  | |  |  |__\___ \\
    /____  >\___  >____  >__|____|____/ |__| |__|____/____  >
         \/     \/     \/  /_____/                        \/

    '''


    parser = OptionParser() #using OptionParser to support python 2.6
    parser.add_option("-f", "--fix", dest="fix", action="store_true", help="repair registry by disabling modules")
    parser.add_option("-d", "--disable", dest="disable", help="disable module directly on sql")
    (options, args) = parser.parse_args()

    if options.fix:
        disable_critical()
        sys.exit(0)
    
    if options.disable:
        force_disable_module(options.disable)
        sys.exit(0)
        
    parser.print_help()
    sys.exit(1)
        
