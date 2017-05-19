##########################################
# Simple script to read sqlite DB files
# and print the QIE calibration constants
# F. Yumiceva 2017
#########################################

import sqlite3 as lite
import pandas as pd

#input sqlite file
con = lite.connect('qie10_database/qieCalibrationParameters_All.db')

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
#print tables
#cursor = con.cursor()
#cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
#print(cursor.fetchall())

#dump all the tables
#with open('dump.sql', 'w') as f:
#  for line in con.iterdump():
#    f.write('%s\n' % line)

#CREATE TABLE qieshuntparams(id STRING, serial INT, qie INT, capID INT, range INT,
#shunt INT, directoryname STRING, date STRING    , slope REAL, offset REAL, 
#uncertainty REAL);

with con:    
  cur = con.cursor()    
  cur.execute("SELECT * FROM qieparams")
  rows = cur.fetchall()

  #print "# QIE10BarCode QIE10ID QIE10 Range CapID Slope Offset"
  print "# QIE10BarCode QIE10ID QIE10 Offsets(CapID*4+Range) Slopes(CapID*4+Range)"
  offsets=""
  slopes=""
  offsets_arr= [None]*16
  slopes_arr= [None]*16
  j=0
  for row in rows:
    #print row
    #if qieID == row[2] and range == row[4] and shunt == row[5]:
    #print "#"*50
    #print "QIE barcode: "+row[0]
    #print "QIE id: 500"+ str(row[1])
    #print "qie10: "+ str(row[2])
    #print "capID: "+ str(row[3])
    #print "range: "+ str(row[4])
    #print "slope: "+ str(row[7])
    #print "offset: " + str(row[8])
    QIEID=""
    if(row[1]>=1000 and row[1]<10000):
      QIEID="50"+str(row[1])
    elif(row[1]>=100 and row[1]<1000):
      QIEID="500"+str(row[1])
    else:
      print str(row[1])
    i=int(str(row[3]))*4+int(str(row[4]));
    offsets_arr[i] = row[8]
    slopes_arr[i] = row[7]
    #print offsets_arr[i]
    #print slopes_arr[i]
    j=j+1
    #print j
    if(j==16):
      for x in offsets_arr:
        offsets+=(str(x))+" "
      for y in slopes_arr:
        slopes+=(str(y))+" "
      print QIEID+" "+str(row[2])+" "+offsets+slopes
      offsets=""
      slopes=""
      offsets_arr= [None]*16
      slopes_arr= [None]*16
      j=0
