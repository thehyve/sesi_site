import subprocess

def drush_sql(sql):
    
    p = subprocess.Popen(["drush", "sqlq", sql], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, err = p.communicate()
    
    if p.returncode == 0:
        return output.decode("utf-8").split('\n')

    return None


if __name__ == '__main__':
    
    users = drush_sql("select uid, name, mail from users")
    
    for line in users:

        # todo: skip header
        
        entry = line.split('\t')
        if len(entry) < 3:
            continue
        
        # todo: pad spaces to N, to simulate columns
        
        print "%s %s %s" % (entry[0], entry[1], entry[2])
