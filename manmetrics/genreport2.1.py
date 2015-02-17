import subprocess


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


if __name__ == '__main__':
    
    users = drush_sql("select uid, name, mail from users")
    
    skip = 2         
    for line in users:

        # skip headers
        if skip > 0:
            skip -= 1
            continue
            
        # split in tabs
        entry = line.split('\t')
        if len(entry) < 3:
            continue
            
        print "%s %s %s" % (entry[0].ljust(5), entry[1].ljust(40), entry[2].ljust(50))
