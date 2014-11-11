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

# ------------------------------- #
# Enable sesi_communities_and_files feature
# ------------------------------- #
drush pm-enable --yes sesi_communities_and_files
drush --yes features-revert sesi_communities_and_files

# ------------------------------- #
# Enable Default Community Config #
# ------------------------------- #
drush --yes pm-enable sesi_default_community
drush --yes features-revert sesi_default_community

# ------------------------ #
# Enable Menu Links Config #
# ------------------------ #
drush --yes pm-enable sesi_menu_links
drush --yes features-revert sesi_menu_links

# --------------- #
# Enable Site Map #
# --------------- #
drush --yes pm-enable sesi_site_map
drush --yes features-revert sesi_site_map

# ------------------ #
# Enable Easy Social #
# ------------------ #
drush --yes pm-enable sesi_easy_social
drush --yes features-revert sesi_easy_social

# -------------- #
# Enable Twitter #
# -------------- #
drush --yes pm-enable sesi_twitter
drush --yes features-revert sesi_twitter

# --------------------------------- #
# Enable feature for Homepage       #
# --------------------------------- #
drush --yes pm-enable sesi_homepage
drush --yes features-revert sesi_homepage

# ------------------------------ #
# Enable Printer Friendly Config #
# ------------------------------ #
drush --yes pm-enable sesi_printer_friendly
drush --yes features-revert sesi_printer_friendly

# -------------------------------------------------- #
# Display list of features to check status manually. #
# -------------------------------------------------- #
drush features

