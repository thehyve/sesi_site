#!/usr/bin/env bash

set -e

echo '________ __________ ____ _____________  _____  .____      __________ ____ ___.____    .____    ' 
echo '\______ \\______   \    |   \______   \/  _  \ |    |     \______   \    |   \    |   |    |    '
echo ' |    |  \|       _/    |   /|     ___/  /_\  \|    |      |     ___/    |   /    |   |    |    '
echo ' |    `   \    |   \    |  / |    |  /    |    \    |___   |    |   |    |  /|    |___|    |___ '
echo '/_______  /____|_  /______/  |____|  \____|__  /_______ \  |____|   |______/ |_______ \_______ \ '
echo '        \/       \/                          \/        \/                            \/       \/ '

# Get drupal root
DRUPAL_ROOT=`drush status | grep 'Drupal root' | sed 's/.*:[ ]*//' | sed 's/ *$//'`
echo $DRUPAL_ROOT

if ! type "drush" > /dev/null; then
  wget --quiet -O - http://ftp.drupal.org/files/projects/drush-7.x-5.9.tar.gz | tar -zxf - -C /usr/local/share
  ln -s /usr/local/share/drush/drush /usr/bin/drush
fi

# Get field_group patch and apply it
if [ ! -f 2078201-27-fieldgroup_notice_flood.patch ]; then
    echo 'field_group module patch does not exist'
    wget https://www.drupal.org/files/2078201-27-fieldgroup_notice_flood.patch
fi

patch -p1 -N --silent "$DRUPAL_ROOT/profiles/mica_distribution/modules/field_group/field_group.module" 2078201-27-fieldgroup_notice_flood.patch || true

#adding patch for core mica xml converter
patch -p1 -N --silent "$DRUPAL_ROOT/profiles/mica_distribution/modules/mica/extensions/mica_opal/mica_opal_view/ServicesOpalFormatter.inc" patch/fix_vocabulary_url.patch || true
patch -p1 -N --silent "$DRUPAL_ROOT/profiles/mica_distribution/modules/mica/extensions/mica_opal/mica_opal_view/ServicesOpalFormatter.inc" patch/dataset_name_in_xml_export.patch || true

# Check drupal status
drush status
 
# Disable these themes to make sure they are never enabled.
drush --yes pm-disable seven
drush --yes pm-disable bartik
 
# Enable some modules that must be enabled.
drush --yes pm-enable features
drush --yes pm-enable strongarm
drush --yes pm-enable locale

#backup first
drush archive-dump /tmp/micasitebk
 
# ////////////////////////// Enable project features.
drush --yes pm-enable sesi_eid_login
drush --yes pm-disable beididp_button
drush --yes features-revert sesi_eid_login

drush --yes pm-enable sesi_user_registration
drush --yes features-revert sesi_user_registration

drush --yes pm-enable sesi_dataset_inheritance
drush --yes features-revert sesi_dataset_inheritance

drush --yes pm-enable sesi_dataset_versioning
drush --yes features-revert sesi_dataset_versioning

drush --yes pm-enable sesi_vocabulary
drush --yes features-revert sesi_vocabulary

# ////////////////////////// Download Autologout module dependencies and enable it
drush --yes dl autologout
drush --yes en autologout
# ////////////////////////// Enable and revert the auto logout feature
drush --yes pm-enable sesi_autologout
drush --yes features-revert sesi_autologout

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
