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


def htmlheader(f, title):
    f.write('<html><head>')
    f.write('<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css">')
    f.write('<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.2/js/bootstrap.min.js"></script>')
    f.write('</head><body>')
    f.write('<img align="right" border="0" src="http://cmi-vzw.be/logor.jpg" width="800" height="80">')

    f.write('<h1>%s</h1>' % title)



if __name__ == '__main__':
    
    users = drush_sql("select uid, name, mail from users")

    # todo: improve to add date to output filename
    
    htmlf = open("/var/www/html/mica/sites/default/files/report.html", "w")
    htmlheader(htmlf, "Mica users")

    htmlf.write('<table class="table">')

    header = True
    
    for line in users:

        # split in tabs
        entry = line.split('\t')
        if len(entry) < 3:
            continue

        # skip headers
        if header:
            header = False
            htmlf.write("<tr> <th>%s</th> <th>%s</th> <th>%s</th> </tr>" % (entry[0], entry[1], entry[2]))
            continue
            
        print "%s %s %s" % (entry[0].ljust(5), entry[1].ljust(40), entry[2].ljust(50))

        htmlf.write("<tr> <td>%s</td> <td>%s</td> <td>%s</td> </tr>" % (entry[0], entry[1], entry[2]))
    
    htmlf.write('</table></body></html>')

    htmlf.close()