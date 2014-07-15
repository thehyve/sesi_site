#!/usr/bin/env bash

set -e

echo '________ __________ ____ _____________  _____  .____      __________ ____ ___.____    .____    ' 
echo '\______ \\______   \    |   \______   \/  _  \ |    |     \______   \    |   \    |   |    |    '
echo ' |    |  \|       _/    |   /|     ___/  /_\  \|    |      |     ___/    |   /    |   |    |    '
echo ' |    `   \    |   \    |  / |    |  /    |    \    |___   |    |   |    |  /|    |___|    |___ '
echo '/_______  /____|_  /______/  |____|  \____|__  /_______ \  |____|   |______/ |_______ \_______ \ '
echo '        \/       \/                          \/        \/                            \/       \/ '


if ! type "drush" > /dev/null; then
  wget --quiet -O - http://ftp.drupal.org/files/projects/drush-7.x-5.9.tar.gz | tar -zxf - -C /usr/local/share
  ln -s /usr/local/share/drush/drush /usr/bin/drush
fi

# Check drupal status
drush status
 
# Disable these themes to make sure they are never enabled.
drush --yes pm-disable seven
drush --yes pm-disable bartik
 
# Enable some modules that must be enabled.
drush --yes pm-enable features
drush --yes pm-enable strongarm

#backup first
drush archive-dump /tmp/micasitebk
 
# ////////////////////////// Enable project features.
drush --yes pm-enable sesi_eid_login
 

# Enable project theme.
#drush --yes pm-enable ourprettytheme

# ////////////////////////// 
# Update
#drush --yes updb
 
# Disable unused modules and features.
 
# Remove an old content type and some fields.
#drush --yes php-eval "node_type_delete('page');"
#drush field-delete field_news_tags --bundle=news
#drush field-delete field_news_link --bundle=news
 
# Index content for solr
#drush sapi-i ok_sitewide_index 10000 25
#drush sapi-s
 
# Revert all features and clear cache.
### drush --yes features-revert-all
drush cache-clear all
 
# Display list of features to check status manually.
drush features
 

