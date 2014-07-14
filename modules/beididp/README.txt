Introduction
------------
This module allows users to authenticate with their Belgian eID card, 
using Fedict's eID Identity provider (IDP).

The Drupal website will act as the Relying Party, while the IDP will take
care of the communication with the eID card itself, using a java applet.


No Service Level Agreement
--------------------------
Please note that Fedict does not provide an SLA.
It is therefore recommended to set up your own IDP server.
By default, a test service hosted by e-contract is used.


Installation
------------
* Drupal site (Relying Party):

- The Drupal OpenID module has to be disabled to avoid conflicts with BeidIDP
- PHP library bcmath and/or gmp has to be enabled
- PHP version 5.3 is recommended (5.4 should work as well)
- Cron should be enabled (poormanscron module or another scheduler)


* Securing session cookies

While using the eID-card is more secure than sending username and password,
Drupal itself is still vulnerable to session hijacking if the (Drupal) session
cookies can be intercepted. So:
- HTTPS must be enabled on the webserver
- Read the instructions on http://drupal.org/https-information and install
  additional modules and/or make the necessary configuration changes

 
* Identity provider:

- Either use an existing one (default is a test service hosted by e-contract), 
  or set up your own IdP 
- More info and source code can be found on http://code.google.com/p/eid-idp/
- Please subscribe to the eID applet mailing list to receive information
  about updates and issues: http://groups.google.com/group/eid-applet 


* Client / Browser:
session.cookie_secure 
- Supported browser (IE 7+, FF 3+, Safari, Chrome 10+)
- Either have the latest Java 1.6 runtime installed, or the necessary
  rights to install it (if not present, the IDP will try to install the 
  JVM automatically) on your desktop
- Running Javascript and Java applets must be allowed


* Middleware:

- The IDP applet can work with or without eID middleware, so there is no need
  to install it on the client.


* Hardware:

- An eID card reader
- A valid Belgian eID card


Using / hashing the unique RRN number
-------------------------------------
Depending on the privacy settings on the remote IDP server, the IDP will show 
the citizen's unique identifier (Rijksregister nummer) as part of the OpenID
identifier (RRN at the end of the URL).
However, you need a special authorization from the Privacy Commission to use
/ store this number.

To avoid this issue, the remote IDP server should be configured to hash the
RRN before sending it to the Drupal site. In case the IDP server does not
hash the RRN, and you cannot change the configuration on the IDP server,
this module provides the option to hash the RRN on the Drupal site itself.

As an extra protection against rainbow table attacks, a prefix and a suffix
are added to the RRN. The prefix and suffix are stored on the file system
instead of putting the variables directly into the database.
Please change the value of the prefix and suffix in Drupal's settings.php file
immediately after installation and restart the PHP engine: 

  $conf['beididp_hash_prefix'] = 'yourprefix';
  $conf['beididp_hash_suffix'] = 'yoursuffix';

Do not change this option afterwards: if you do, existing (eID) users will not
be able to log in anymore, since their BE IDP identifier will not match. 


Submodules
----------
- beididp_block
UI: exposes the eID button in a Drupal block.
 
- beididp_button
UI: addes the eID button to the login forms.

- beididp_checkrole
Select which roles must log in using the Belgian eID card.

- beididp_fields
Map eID information (like name, address ...) to Drupal user fields.

- beididp_migrate
Updates the URLs of the eID identities, useful when migrating from one IDP to
another. The module assumes that (the hash of) the RRN at the end of the URL
remains unchanged.


Credits
-------
Initial development: Fusebox BVBA (fusebox.be) and Fedict (www.fedict.be)
