import subprocess
from cgi import escape


def drush_sql(sql):
    """
    Run sql query using drush
    :param sql: sql query to run
    :return: array of strings or None if returncode is not zero
    """
    
    p = subprocess.Popen(["drush", "sqlq", sql], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, err = p.communicate()
    
    if p.returncode == 0:
        return output.decode('utf-8', "ignore").rstrip().split('\n')

    return None


def htmlheader(f, title):
    f.write('<html><head>')
    f.write('<style>')
    f.write('table>thead>tr>td { background-color: rgb(211, 173, 173); }')
    f.write('table>tbody>tr:nth-child(odd) td{ background-color: rgb(255, 211, 213); }')
    f.write('table>tbody>tr:nth-child(even) td{}; }')
    f.write('</style>')
    f.write('<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css">')
    f.write('<script src="https://code.jquery.com/jquery-1.11.3.min.js"></script>')
    f.write('<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.2/js/bootstrap.min.js"></script>')
    f.write('</head><body>')
    f.write('<img align="right" border="0" src="http://cmi-vzw.be/logor.jpg" width="800" height="80">')

    f.write('<h1>%s</h1><br/>' % title)

def htmltotal(htmlf, lines):
    if len(lines)>0:
        htmlf.write('Total: %s' % (len(lines)-1))
    else:
        htmlf.write('No results found')

    htmlf.write('<br/>')

def htmltable(htmlf, lines):

    htmlf.write('<table class="table table-stripped">')

    isheader = True

    for line in lines:
        if isheader:
            htmlf.write('<thead>')

        # split in tabs
        entry = line.split('\t')

        htmlf.write("<tr>")
        for val in entry:
            htmlf.write("<td>%s</td>" % escape(val.encode('utf-8','replace')))
        htmlf.write("</tr>")

        if isheader:
            isheader=False
            htmlf.write('</thead><tbody>')

    htmlf.write('</tbody></table>')
    htmlf.write('</body></html>')


def htmltable_withwarn(htmlf, lines):
    '''
    This function saves the previous row info to detect duplicates of visible+invisible
    '''

    htmlf.write('<table class="table table-stripped">')

    isheader = True

    (nid, version, visible) = (None,None, None)

    for line in lines:

        if isheader:
            htmlf.write('<thead>')

        # split in tabs
        entry = line.split('\t')


        htmlf.write("<tr>")

        for i in range(len(entry)):
            value = escape(entry[i].encode('utf-8','replace'))
            if i==5:
                if value=='1':
                    value='<span class="glyphicon glyphicon-eye-open aria-hidden="true"></span>'
                elif value=='0':
                    value=''
                elif value=="NULL":
                    value='N/A'

            htmlf.write("<td>%s</td>" % value)


        htmlf.write('<td>')
        if nid==entry[0] and version==entry[1]:
            htmlf.write('<span class="glyphicon glyphicon-duplicate" aria-hidden="true"></span>')
            if visible!=entry[5]:
                htmlf.write('<span class="glyphicon glyphicon-warning-sign" aria-hidden="true"></span>')

        htmlf.write('</td>')
        (nid, version, visible) = (entry[0],entry[1],entry[5])

        if isheader:
            isheader=False
            htmlf.write('<tr></tr></thead><tbody>')
        else:
            htmlf.write("</tr>")

    htmlf.write('</tbody></table>')
    htmlf.write('</body></html>')


def htmlinfo(htmlf, text):
    htmlf.write(' <div class="glyphicon glyphicon-info-sign" aria-hidden="true"></div> %s <br />' % text)


if __name__ == '__main__':
    
    # todo: improve to add date to output filename
    
    htmlf = open("/var/www/html/mica/sites/default/files/secreport.html", "w")
    htmlheader(htmlf, "Mica Security report")

    # Content in communities
    htmlf.write('<h2>Content in communities</h2>')

    lines = drush_sql('''
      SELECT n.nid, n.vid as version, n.type as type, n.title as title,
      (select comm.title FROM node comm WHERE comm.nid = na.gid) as community,
      (select fpv.field_project_visibility_value
      FROM node comm,field_data_field_project_visibility as fpv
      WHERE comm.nid = na.gid
      AND fpv.entity_id = comm.nid
      ) as visible
      #FROM_UNIXTIME(n.changed) as changed,
      #FROM_UNIXTIME(n.created) as created
      FROM node as n, node_access as na
      WHERE n.nid = na.nid
      AND na.realm="og_access:node"
      AND n.type != "community" and n.type!="default_community"
      ORDER BY n.type ASC, n.title ASC, n.nid ASC, n.vid ASC
      ''')
    htmltotal(htmlf, lines)

    htmlf.write('<span class="glyphicon glyphicon-eye-open" aria-hidden="true"></span>')
    htmlf.write('Content is flagged to visible in the community. <br/>')

    htmlf.write('<span class="glyphicon glyphicon-duplicate" aria-hidden="true"></span>')
    htmlf.write('Content shared in multiple communities. <br/>')

    htmlf.write('<span class="glyphicon glyphicon-warning-sign" aria-hidden="true"></span>')
    htmlf.write('Content shared in multiple communities with different project visibility.  <br/>')

    htmltable_withwarn(htmlf, lines)

    # Visible communities
    htmlf.write('<h2>Communities with project visibility: VISIBLE </h2>')
    htmlinfo(htmlf,'''
        This communities (and content associated) will be visible on lists.
    ''')

    lines = drush_sql('''
      SELECT n.nid, n.title,
      FROM_UNIXTIME(n.changed) as changed,
      FROM_UNIXTIME(n.created) as created
      FROM node as n, field_data_field_project_visibility as fpv
      WHERE n.type="community"
      AND fpv.field_project_visibility_value=1
      AND fpv.entity_id = n.nid
      ORDER BY n.title
      ''')
    htmltotal(htmlf, lines)
    htmltable(htmlf, lines)


    # Public content
    htmlf.write('<h2>Content with group visibility: PUBLIC </h2>')
    htmlinfo(htmlf, "This content is accessible to everybody (no registration required)" )

    lines = drush_sql('''
      SELECT n.nid, n.vid as version, n.type as type, n.title as title,
      FROM_UNIXTIME(n.changed) as changed,
      FROM_UNIXTIME(n.created) as created
      FROM node as n, node_access as na
      WHERE n.nid = na.nid
      AND na.realm="all"
      AND (n.type="community" OR n.type="page" OR n.type="dataset" OR n.type="variable" OR n.type="study" OR n.type="default_community")
      ORDER BY n.type ASC, n.title ASC
      ''')
    htmltotal(htmlf, lines)
    htmltable(htmlf, lines)



    # Active users
    htmlf.write('<h2>Active users</h2>')
    htmlinfo(htmlf, '''
        The access field is updated in Drupal's session every 180 seconds
        if the user is still actively browsing.
        ''' )


    lines = drush_sql('''
      select uid,name,mail,
        FROM_UNIXTIME(access) as access,
        FROM_UNIXTIME(login) as login
      from users where status=1 order by name
      ''')
    htmltotal(htmlf, lines)
    htmltable(htmlf, lines)



    htmlf.close()
    print "http://localhost:7880/mica/sites/default/files/secreport.html"