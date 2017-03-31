##########################################
# Simple script to read sqlite DB files
# and print the QIE calibration constants
# F. Yumiceva 2017
#########################################

import sqlite3 as lite
import pandas as pd

#input sqlite file
con = lite.connect('qie11_database/qieCalibrationParameters_0xae000000_0xeabb9870.db')

# select QIE chip, shunt value
qieID = 1
shunt = 2
capID = 0
range = 1

# print sqlite version and check connection
with con:
    
    cur = con.cursor()    
    cur.execute('SELECT SQLITE_VERSION()')
    
    data = cur.fetchone()
    #print "SQLite version: %s" % data  

# print tables
#cursor = con.cursor()
#cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
#print(cursor.fetchall())

# dump all the tables
#with open('dump.sql', 'w') as f:
#    for line in con.iterdump():
#        f.write('%s\n' % line)

# CREATE TABLE qieshuntparams(id STRING, serial INT, qie INT, capID INT, range INT,
# shunt INT, directoryname STRING, date STRING    , slope REAL, offset REAL, 
#uncertainty REAL);

with con:    
    
    cur = con.cursor()    
    cur.execute("SELECT * FROM qieshuntparams")

    rows = cur.fetchall()

    for row in rows:
        #print row
        #if qieID == row[2] and range == row[4] and shunt == row[5]:
            print "#"*50
            print "QIE board: "+row[0]
            print "QIE chip: "+ str(row[2])
            print "shunt: "+ str(row[5])
            print "range: "+ str(row[4])
            print "capID: "+ str(row[3])
            print "slope: "+ str(row[8])
            print "offset: " + str(row[9])
