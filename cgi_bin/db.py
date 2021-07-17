#!/usr/bin/python

import sys
import os

print('Content-Type: text/html\n\n<h1>Search query/h1>')
# query_string = os.environ['QUERY_STRING']

date = os.environ["DATE_LOCAL"]
ip = os.environ["REMOTE_ADDR"]
serv_id = os.environ["SERVER_NAME"]

body = sys.stdin.read( int(os.environ["CONTENT_LENGTH"]) )
# print body
values = [i.split('=') for i in body.split('&')]

filename = './db/db_' + serv_id + '.tmp'

Fout = open ( filename, "a" )
Fout.write ('IP: ' + ip + ' ========== DATE: ' + date + '<br>')
for key, value in values:
	Fout.write ('<b>' + key + '</b>: ' + value + '<br>\n')
	# print('<b>' + key + '</b>: ' + value + '<br>\n')
Fout.write ('<br>')


# import sys
# import os

# print('Content-Type: text/html\n\n<h1>Search query/h1>')
# # query_string = os.environ['QUERY_STRING']

# date = os.environ["DATE_LOCAL"]
# ip = os.environ["REMOTE_ADDR"]
# body = sys.stdin.read( int(os.environ["CONTENT_LENGTH"]) )
# # print body

# values = [i.split('=') for i in body.split('&')] #parse query string
# # SearchParams is an array of type [['key','value'],['key','value']]
# # for example 'k1=val1&data=test' will transform to 
# #[['k1','val1'],['data','test']]
# Fout = open ( "db.tmp", "a" )
# Fout.write ('IP: ' + ip + ' ========== DATE: ' + date + '<br>')
# for key, value in values:
# 	Fout.write ('<b>' + key + '</b>: ' + value + '<br>\n')
# 	print('<b>' + key + '</b>: ' + value + '<br>\n')
# Fout.write ('<br>')



# Fout = open ( "output.txt", "w" )
# Fout.write ("hello")
# print "Content-type: text/html\n\n"
# print "CONTENT_LENGTH = " + os.environ["CONTENT_LENGTH"]
# print "GATEWAY_INTERFACE = " + os.environ["GATEWAY_INTERFACE"]
# print "REMOTE_ADDR = " + os.environ["REMOTE_ADDR"]
# print "REQUEST_METHOD = " + os.environ["REQUEST_METHOD"]
# print "SERVER_NAME = " + os.environ["SERVER_NAME"]
# print "SERVER_PORT = " + os.environ["SERVER_PORT"]
# print "QUERY_STRING = " + os.environ["QUERY_STRING"]
# print "gogogogogogoogogogogogogogogogogogo"
# body = sys.stdin.read( int(os.environ["CONTENT_LENGTH"]) )
# print body



