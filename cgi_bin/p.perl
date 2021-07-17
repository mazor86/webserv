#!/usr/bin/perl
use CGI;
print "Content-type: text/html\n\n";
print "IT IS NEW PERL SCRIPT\n";
$my_cgi = new CGI;
$your_name = $my_cgi->param('name');
print "Hello $your_name!!!";