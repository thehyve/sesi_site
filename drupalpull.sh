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

drush vset maintenance_mode 1


# PATCH ORIGINAL MICA CODE
yes | cp -Rfv "$DRUPAL_ROOT/sites/all/patch/mica_distribution" "$DRUPAL_ROOT/profiles/"

# ----------------------------- activate common functions
drush pm-list --pipe --type=module --status=enabled > /tmp/enabledmods
drush pm-list --pipe --type=module --no-core > /tmp/allmods
function isenabled() { grep -Fxq "$1" /tmp/enabledmods  ;}
function isdisabled() { ! grep -Fxq "$1" /tmp/enabledmods  ;}

function ensure_mod() {
    echo "ensure_mod $1";
    if isdisabled $1; then
        if grep -Fxqv "$1" /tmp/allmods; then
            drush --yes dl $1 ;
        fi
        drush --yes en $1 ; 
    fi
}

function ensure_feat() {
    echo "ensure_feat $1";
    if isdisabled $1; then
        drush --yes pm-enable $1 ; 
    fi
}
# ---------------------------------------------------------

# DISABLE these themes and modules to make sure they are never enabled.
isenabled seven && drush --yes pm-disable seven
isenabled bartik && drush --yes pm-disable bartik
isenabled locale && drush --yes dis locale

# Enable some modules that must be enabled.
isdisabled features && drush --yes pm-enable features
isdisabled strongarm && drush --yes pm-enable strongarm

# Install and enable Features Extra module
if isdisabled fe_block; then
    drush --yes dl features_extra
    drush --yes en fe_block
fi

# Enable Rules
isdisabled rules_admin && drush --yes en rules rules_admin

# Install and enable entityreference
ensure_mod entityreference

# Enable Date Popup
isdisabled date_popup && drush --yes en date_popup

# Activate organic groups
if isdisabled og; then
    drush --yes dl og
fi
drush --yes en og og_ui og_context og_access 

# Install and enable og_email
ensure_mod og_email

# Install and enable og_email_blast to send emails to a complete group
# Please note that using the ensure_mod function doesn't work here
# as we need a specific version
if isdisabled og_email_blast; then
    drush --yes dl og_email_blast-7.x-2.x-dev
    drush --yes en og_email_blast
fi
# Install and enable uuid_features module
ensure_mod uuid_features

# Install captcha
if isdisabled captcha; then
    drush --yes dl captcha
    drush --yes en captcha image_captcha
fi
ensure_feat sesi_captcha

# Install easy_social module
ensure_mod easy_social

# Install and enable oauth
# This module is required by twitter module

if isdisabled oauth_common; then
    drush --yes dl oauth
    drush --yes en oauth_common
    drush --yes en oauth_common_providerui
fi

# Install and enable twitter module
ensure_mod twitter

# Install htmlmail dependency
if isdisabled mailmime; then
    drush --yes dl htmlmail mailmime mailsystem
    drush --yes en htmlmail mailmime
fi

# Install and enable og_email
ensure_mod og_email

# Install and enable pet
ensure_mod pet

# Enable project features.
if isdisabled sesi_eid_login; then
    ensure_feat sesi_eid_login
    drush --yes pm-disable beididp_button    
fi

ensure_feat sesi_user_registration
ensure_feat sesi_dataset_inheritance 
ensure_feat sesi_inherit_variable_permissions
ensure_feat sesi_dataset_versioning
ensure_feat sesi_dataset_access_form
ensure_feat sesi_vocabulary

ensure_mod sesi_addtogroup
ensure_mod sesi_notifyexpiration

# Download Autologout module dependencies and enable it
drush --yes dl autologout
drush --yes en autologout

#query
ensure_mod query_interface
ensure_mod query_subscription
ensure_feat sesi_my_queries_screen
ensure_mod query_access_rights

#ontologies and vocabularies
ensure_feat sesi_variable_ontologies
isdisabled query_vocabularies && drush --yes en query_vocabularies

#autologout
ensure_mod autologout
ensure_feat sesi_autologout

#addtogroup
ensure_mod sesi_addtogroup

# Backup first
#drush archive-dump /tmp/micasitebk

# Enable Contact Form
ensure_mod contact
ensure_feat sesi_contact_form

#
ensure_feat sesi_communities_and_files
ensure_feat sesi_user_profile_fields
ensure_feat sesi_default_community
ensure_feat sesi_site_map
ensure_feat sesi_easy_social
ensure_feat sesi_twitter
ensure_feat sesi_printer_friendly
ensure_feat sesi_expiration_date
ensure_feat sesi_membership_mail


# UPDATE JQUERY VERSION
drush -y eval "variable_set('jquery_update_jquery_version', strval(1.8));"

# Expandable text
ensure_mod collapse_text
ensure_feat sesi_collapse_text
ensure_mod text_hierarchical

# Statistics
ensure_mod better_statistics
 
# Remove an old content type and some fields.
#drush --yes php-eval "node_type_delete('page');"
#drush field-delete field_news_tags --bundle=news
#drush field-delete field_news_link --bundle=news
 
# Index content for solr
#drush sapi-i ok_sitewide_index 10000 25
#drush sapi-s

drush --yes features-revert-all

drush cache-clear all
 
# Display list of features to check status manually.
#drush features

#rebuild permissions
drush php-eval 'node_access_rebuild();'

drush cc all
drush cron
drush vset maintenance_mode 0
