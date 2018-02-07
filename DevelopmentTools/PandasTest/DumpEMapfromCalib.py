import pandas as pd
import os

if __name__ == '__main__':
  #fn = os.environ['CMSSW_BASE']+'/src/ngCMSHCALMap/DevelopmentTools/PandasTest/HCALmapCALIB_J.xls'
  #df = pd.read_excel(fn, sheetname = 'uHTR')
  #print (df.head())
  '''
  print "#i crate slot tb dcc spigot htr_fi fib_ch det eta phi type"
  for index, row in df.iterrows():
    if row['t/b'] == 'top':
      print row['index'], row['crate'], row['HTR'], 't', row['dcc'], row['spigot'], row['htr_fib'], row['fib_ch'], 'CALIB_'+row['det'], row['eta'], row['phi'], row['type']
    elif row['t/b'] == 'bot':
      print row['index'], row['crate'], row['HTR'], 'b', row['dcc'], row['spigot'], row['htr_fib'], row['fib_ch'], 'CALIB_'+row['det'], row['eta'], row['phi'], row['type']
    else:
      print row['index'], row['crate'], row['HTR'], row['t/b'], row['dcc'], row['spigot'], row['htr_fib'], row['fib_ch'], 'CALIB_'+row['det'], row['eta'], row['phi'], row['type']
  '''
  #fn = os.environ['CMSSW_BASE']+'/src/ngCMSHCALMap/DevelopmentTools/PandasTest/ngCU_Lmap_template.xls'
  fn = os.environ['CMSSW_BASE']+'/src/ngCMSHCALMap/DevelopmentTools/PandasTest/HCALmapCALIB_J.xls'
  #df = pd.read_excel(fn, sheetname = 'c34fibers')
  df = pd.read_excel(fn, sheetname = 'master_order')
  print "#HO CALIB channels Emap"
  print "#i crate slot tb dcc spigot uhtr_fi fib_ch det eta phi depth"
  for index, row in df.iterrows():
    #print row['i'], row['cr'], row['sl'], row['tb'], row['dcc'], row['spigot'], row['uhtr_fib'], row['fib_ch'], row['subdet'], row['ieta'], row['iphi'], row['depth']
    if row['name'] == 'CALIB_HO':
      tb = 'b'
      htr = row['uhtr']
      if row['fpga'] == 'top' :
        tb = 't'  
      print '4200458C', row['crate'], htr, tb, row['dcc'], row['spigot'], row['htr_fib'], row['fi_ch'], row['name'], row['eta'], row['phi'], row['ch_type']
  '''
  fn = r'HOHF_CUfiber_J_template.xls'
  df = pd.read_excel(fn, sheetname = 'uHTR')
  print "#HFHO CALIB channels Emap"
  print "#i crate slot tb dcc spigot uhtr_fi fib_ch det eta phi depth"
  '''
