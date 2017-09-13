import sqlite3

conn = sqlite3.connect('../officialMap/HCALLogicalMap.db')
c = conn.cursor()
print "Opened database successfully";

cursor = c.execute("SELECT Side, Eta, RBX, RM, RM_FI, FI_CH from HBLogicalMap")
for row in cursor:
   print "Side = ", row[0]
   print "Eta = ", row[1]
   print "RBX = ", row[2]
   print "RM = ", row[3]
   print "RM_FI = ", row[4]
   print "FI_CH = ", row[5], "\n"

print "Operation done successfully";
conn.close()
