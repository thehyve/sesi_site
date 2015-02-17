#!/usr/bin/env bash

set -e

echo '  ________             __________                             __   '
echo ' /  _____/  ____   ____\______   \ ____ ______   ____________/  |_ '
echo '/   \  ____/ __ \ /    \|       _// __ \\____ \ /  _ \_  __ \   __\'
echo '\    \_\  \  ___/|   |  \    |   \  ___/|  |_> >  <_> )  | \/|  |'
echo ' \______  /\___  >___|  /____|_  /\___  >   __/ \____/|__|   |__|'
echo '        \/     \/     \/       \/     \/|__|                       '


set -x
DATE_VER=`date '+%m%d%H%M'`
DESTPDF="sites/default/files/$2_$DATE_VER.pdf"
TMPFILE=$(mktemp /tmp/output.XXXXXXXXXX)
drush sqlq "$1" > $TMPFILE
cat "$TMPFILE" | a2ps  -o "$TMPFILE.ps" - | ps2pdf "$TMPFILE.ps" $DESTPDF

echo "please access to http://MICASERVER/mica/$DESTPDF"
