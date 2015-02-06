For this rule action to work, the following parameter has to be supplied: the membership
To do this, make a rule action that add a variable
ADDED VARIABLE
Variable label: OG Membership
Variable name: ogm

Further, there has to be a rule component with the name: rules_mail_group_admins.
call: rules_invoke_component('rules_mail_group_admins', $admin, $membership->gid, $membership->etid, $userprofile['pid']);
This rule will receive 2 parameters from the module (rule component):
1) the uid of the user to send the mail to
2) the nid of the group
3) the uid of the new member
4) the id of the profile of the new member

