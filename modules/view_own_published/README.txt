View Own Unpublished
--------------------
This module makes sure that users who have 'View own unpublished content'
permission from the node module can see their own unpublished content in
listings and views. They should already be able to do that, but it doesn't
always work if modules such as content_access or acl are enabled, as they
change the default grants. See also https://www.drupal.org/node/1190096 and
https://www.drupal.org/node/1225520

Common issues
-------------
If for some reason this module seems not to work, try rebuilding your node
permissions: admin/reports/status/rebuild. Note that this can take significant
time on larger installs and it is HIGHLY recommended that you back up your site
first.
