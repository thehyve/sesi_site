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


def htmlinfo(htmlf, text):
    htmlf.write(' <div class="glyphicon glyphicon-info-sign" aria-hidden="true"></div> %s <br />' % text)


if __name__ == '__main__':
    
    # todo: improve to add date to output filename
    
    htmlf = open("/var/www/html/mica/sites/default/files/queriesperds.html", "w")
    htmlheader(htmlf, "Mica Queries per dataset REPORT example")

    # 
    #htmlf.write('<h2>Communities with project visibility: VISIBLE </h2>')
    #htmlinfo(htmlf,'''
    #    This communities (and content associated) will be visible on lists.
    #''')

    lines = drush_sql('''
 SELECT q.id id, ds.title dataset, u.name user, q.name query,  varia.title variable, concat("node/",ds.nid,"/queries/",q.id) path
      FROM node as ds, users as u, mica_query as q, mica_query_term as mqt, node as varia
      WHERE ds.type="dataset"
      AND q.dataset_id = ds.nid
      AND u.uid = q.user_id
      AND mqt.query_id = q.id
      AND mqt.variable_id = varia.nid
      ORDER BY ds.title ASC, u.name ASC, ds.title ASC, varia.title ASC
      ''')
    htmltotal(htmlf, lines)
    htmltable(htmlf, lines)

    # 
    htmlf.write('<h2>Requests</h2>')
    #htmlinfo(htmlf,'''
    #    This communities (and content associated) will be visible on lists.
    #''')

    lines = drush_sql('''
SELECT title, path, hostname, COUNT( * ) 
FROM `accesslog` 
WHERE path LIKE "node/%/queries/%"
GROUP BY path
ORDER BY title
      ''')
    htmltotal(htmlf, lines)
    htmltable(htmlf, lines)



    htmlf.close()
    print "http://localhost:7880/mica/sites/default/files/queriesperds.html"
