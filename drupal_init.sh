#!/usr/bin/env bash

# drupal_init.sh
# --------------
# This script mainly configures the initial contents for Mica Sesi project.
#

set -e

echo ' (                              (                                        '
echo ' )\ )                      (    )\ )           )                         '
echo '(()/(  (     (           ) )\  (()/(     (  ( /(                         '
echo ' /(_)) )(   ))\ `  )  ( /(((_)  /(_))(   )\ )\())                        '
echo '(_))_ (()\ /((_)/(/(  )(_))_   (_))  )\ |(_|_))/                         '
echo '|   \ ((_|_))(((_)_\((_)_| |  |_ _|_(_/((_) |_                           '
echo '| |) | ,_| || | ,_ \) _` | |   | || , \)) |  _|                          '
echo '|___/|_|  \_,_| .__/\__,_|_|  |___|_||_||_|\__|                          '
echo '               |_|                                                       '

echo '---------------------------------------------------------- mmOvOmm -------'
echo ' Remember this file is for adding features related to content '
echo ' (we should not touch content more than once to avoid overwriting changes '
echo ' made by administrator)'
echo '--------------------------------------------------------------------------'

# --------------- #
# Get drupal root #
# --------------- #
DRUPAL_ROOT=`drush status | grep 'Drupal root' | sed 's/.*:[ ]*//' | sed 's/ *$//'`
echo $DRUPAL_ROOT

<<<<<<< HEAD
# -------------------- #
# Update jQuery Update #
# -------------------- #
drush en update 
drush up jquery_update

# --------------------------------- #
# Enable sesi_communities_and_files #
# --------------------------------- #
drush pm-enable --yes sesi_communities_and_files
drush --yes features-revert sesi_communities_and_files

# ------------------------------- #
# Enable sesi_user_profile_fields #
# ------------------------------- #
drush pm-enable --yes sesi_user_profile_fields
drush --yes features-revert sesi_user_profile_fields

# ------------------------------- #
# Enable Default Community Config #
# ------------------------------- #
drush --yes pm-enable sesi_default_community
drush --yes features-revert sesi_default_community

=======
>>>>>>> master
# ------------------------ #
# Enable Menu Links Config #
# ------------------------ #
drush --yes pm-enable sesi_menu_links
drush --yes features-revert sesi_menu_links

# --------------------------------- #
# Enable feature for Homepage       #
# --------------------------------- #
drush --yes pm-enable sesi_homepage
drush --yes features-revert sesi_homepage

# -------------------------------------------------- #
# Display list of features to check status manually. #
# -------------------------------------------------- #
drush features

