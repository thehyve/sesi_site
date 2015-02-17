### Scenario 1
## "Use mica to extract user queries by type, user, per DS, per System"

1. Create a query

Use phpMyAdmin to facilitate accesing to explore the database
http://localhost:7880/phpmyadmin

2. Run query

cd /var/www/html/mica
drush sqlq "select u.uid, u.mail, ds.title, mq.name FROM users u, mica_query mq, node ds WHERE u.uid=mq.user_id AND ds.nid=mq.dataset_id ORDER BY u.name" | cut -f1,5

drush sqlq "SELECT * FROM node where type='variable'" | cut -f1,5

3. create script (genreport1.0.sh)

4. sh sites/all/genreport1.0.sh "select name from user" report_users


5. generate a report
drush sqlq "select u.uid, u.mail, ds.title, mq.name FROM users u, mica_query mq, node ds WHERE u.uid=mq.user_id AND ds.nid=mq.dataset_id ORDER BY u.name" | a2ps  -o /tmp/temp.ps - | ps2pdf /tmp/temp.ps sites/default/files/report.pdf

http://localhost:7880/mica/sites/default/files/report.pdf

6. improve it (genreport1.1.sh)

7. sh sites/all/genreport1.1.sh "select name from user" report_users

### Scenario 1.1
## "Creating a foundation with python tools"
1. create genreport2.1.py

2. create genreport2.2 to export to html
