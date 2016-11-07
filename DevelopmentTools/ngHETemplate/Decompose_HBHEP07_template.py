import glob, os, sys

def PrintFrontEndToGeoLine(det,rm,geo):
  print( "Subdet : " + det + " RM : " + rm + " Geo : " + geo)
  filename = "HBHEP07_template.txt"
  with open(filename) as f:
    mysubstring = []
    for line in f:
      if line[0] == '#':
        continue
      mysubstring = line.split(' ')
      if( mysubstring[5]==det and mysubstring[8]==rm ) : 
        if(geo=='eta'):
          print ( mysubstring[8] + " " + mysubstring[12] + " " + mysubstring[13] + " " + mysubstring[1] )
          #print mysubstring
        elif(geo=='dep'):
          print ( mysubstring[8] + " " + mysubstring[12] + " " + mysubstring[13] + " " + mysubstring[3] )

def PrintFrontEndToGeoCPPCode(det,rm,geo):
  print( "const int " + det + geo + "Inrmfifichid_" + "RM" + rm + "[Nrm_fiber*Nfiber_ch]=")
  print("{")
  index=0
  filename = "HBHEP07_template.txt"
  with open(filename) as f:
    mysubstring = []
    for line in f:
      if line[0] == '#':
        continue
      mysubstring = line.split(' ')
      if( mysubstring[5]==det and mysubstring[8]==rm ) :
        if index==0: 
          sys.stdout.write("  ")
        if(geo=='eta'):
          if(mysubstring[1]=='N/C'):
            sys.stdout.write("0,  ")
          else:
            if( mysubstring[12]=='8' and mysubstring[13]=='5' ):
              sys.stdout.write( mysubstring[1] + "  ")
            else:
              sys.stdout.write( mysubstring[1] + ", ")
        elif(geo=='dep'):
          if(mysubstring[3]=='N/C'):
            sys.stdout.write("0, ")
          else:
            if( mysubstring[12]=='8' and mysubstring[13]=='5' ):
              sys.stdout.write( mysubstring[3] + "  ")
            else:
              sys.stdout.write( mysubstring[3] + ", ")
        index=index+1
        if index==6:
          sys.stdout.write( "//RM fiber " + mysubstring[12])
          print ""
          index=0
  print("};")
  print ""


det_all = ['ngHE']
rm_all = ['1','2','3','4']
geo_all = ['eta','dep']

for det in det_all:
  for rm in rm_all:
    for geo in geo_all:
      PrintFrontEndToGeoCPPCode(det,rm,geo)
      #PrintFrontEndToGeoLine(det,rm,geo)
