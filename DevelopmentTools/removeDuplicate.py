#!/usr/bin/python
import sys
import os
import time
import math
import re
from optparse import OptionParser # Command line parsing

def main():
   usage = "usage: %prog options"
   version = "%prog."
   parser = OptionParser(usage=usage,version=version)
   parser.add_option("-f", "--file", action="store", dest="inputfile", type="string", default="", help="input emap text file")

   (options, args) = parser.parse_args()

   print 'inputfile : ', options.inputfile

   myre = re.compile(r'(.* )(H.*)')

   in_file = open(options.inputfile)

   results = {}
   others = []

   for line in in_file:
      mo = myre.search(line)
      if mo:
         field_1, field_2 = mo.groups()
         found = False 
         for key,value in results.items():
            if key == field_2:
               found = True
               print ("           field_1 : %s  field_2 : %s" %(field_1, field_2))
               print ("  DUP!! -->  value : %s  key : %s\n" %(value, key))
            if value == field_1:
               print ("   WARNING DUP field_1 : %s??\n" % field_1)
         if not found:
            results[field_2] = field_1
      else:
         others.append(line)

   out_file = open("new_"+options.inputfile, "w")
   for key,value in results.items():
      out_file.write("%s%s\n" %(value,key))
   for peritem in others:
      out_file.write("%s" %peritem)
   out_file.close()

if __name__ == "__main__":
   main()
