#!/usr/bin/env bash
set -e
set -x

TMPFILE="/tmp/report"

drush sqlq "$1" > $TMPFILE
cat "$TMPFILE" 

