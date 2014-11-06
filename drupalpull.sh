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

# PATCH ORIGINAL MICA CODE
yes | cp -Rfv "$DRUPAL_ROOT/sites/all/patch/mica_distribution" "$DRUPAL_ROOT/profiles/"

# Check drupal status
drush status  
 
# Disable these themes to make sure they are never enabled.
drush --yes pm-disable seven
drush --yes pm-disable bartik
 
# Enable some modules that must be enabled.
drush --yes pm-enable features
drush --yes pm-enable strongarm
drush --yes pm-enable locale

# Install and enable Features Extra module
drush --yes dl features_extra
drush --yes en fe_block

# Activate organic groups
drush --yes dl og
drush --yes en og og_ui og_context og_access og_register

# Enable sesi_communities_and_files feature
drush pm-enable --yes sesi_communities_and_files
drush --yes features-revert sesi_communities_and_files

# Install and enable uuid_features module
drush --yes dl uuid_features
drush --yes en uuid_features

# Install captcha
drush --yes dl captcha
drush --yes en captcha image_captcha

# Install easy_social module
drush --yes dl easy_social
drush --yes en easy_social

# Install and enable oauth
# This module is required by twitter module
drush --yes dl oauth
drush --yes en oauth_common
drush --yes en oauth_common_providerui

# Install and enable twitter module
drush --yes dl twitter
drush --yes en twitter

# Backup first
#drush archive-dump /tmp/micasitebk
 
# Enable project features.
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

drush --yes pm-enable query_interface

drush --yes pm-enable sesi_variable_ontologies
drush --yes features-revert sesi_variable_ontologies

# Download Autologout module dependencies and enable it
drush --yes dl autologout
drush --yes en autologout

# Enable and revert the auto logout feature
drush --yes pm-enable sesi_autologout
drush --yes features-revert sesi_autologout

# Enable project theme.
# drush --yes pm-enable ourprettytheme

# Enable Contact Form
drush --yes pm-enable contact
drush --yes pm-enable sesi_contact_form
drush --yes features-revert sesi_contact_form

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
