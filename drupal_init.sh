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

# --------------- #
# Get drupal root #
# --------------- #
DRUPAL_ROOT=`drush status | grep 'Drupal root' | sed 's/.*:[ ]*//' | sed 's/ *$//'`
echo $DRUPAL_ROOT

# ------------------------ #
# Enable Menu Links Config #
# ------------------------ #
drush --yes pm-enable sesi_menu_links
drush --yes features-revert sesi_menu_links

# -------------------------- #
# Enable User Profile Config #
# -------------------------- #
drush --yes pm-enable sesi_user_profile_fields
drush --yes features-revert sesi_user_profile_fields

# -------------------------------------------------- #
# Display list of features to check status manually. #
# -------------------------------------------------- #
drush features
