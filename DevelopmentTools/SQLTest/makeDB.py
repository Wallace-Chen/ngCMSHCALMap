import sqlite3

input = open('test.txt','r')

database = sqlite3.connect("serialNumberToUIDmap.db")

cursor = database.cursor()

cursor.execute("create table if not exists UIDtoSerialNumber(serial INT, uid STRING)")


for line in input:
    if 'uid' in line:
        continue
    uidval = line.split()[0]
    serial = int(line.split()[1])
    uidval = '0x%s 0x%s'%(uidval[:8],uidval[8:])
    values = (serial, uidval)
    cursor.execute("insert into UIDtoSerialNumber values (?, ?)",values)

cursor.close()
database.commit()
database.close()

                          
