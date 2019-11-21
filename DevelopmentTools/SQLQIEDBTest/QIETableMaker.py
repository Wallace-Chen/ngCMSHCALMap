from sqlalchemy import create_engine
import pandas as pd
import os
import optparse
import sys

stdout = sys.stdout

def GetLMapDataFrame( rel_lmap_path ):
  sql_engine_lmap = create_engine( rel_lmap_path )
  sql_con_lmap = sql_engine_lmap.raw_connection()

  df_HBlmap = pd.read_sql("SELECT * FROM ngHBLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  df_HBclmap = pd.read_sql("SELECT * FROM ngHBCalibLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  HBlmaplist = ['Side', 'Eta', 'Phi', 'Depth', 'Det', 'QIECH', 'QIEid']
  df_HBsublmap = df_HBlmap[HBlmaplist]
  df_HBsubclmap = df_HBclmap[HBlmaplist]

  df_HElmap = pd.read_sql("SELECT * FROM ngHELogicalMap", con = sql_con_lmap, index_col = ['ID'])
  df_HEclmap = pd.read_sql("SELECT * FROM ngHECalibLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  HElmaplist = ['Side', 'Eta', 'Phi', 'Depth', 'Det', 'QIECH', 'QIEid']
  df_HEsublmap = df_HElmap[HElmaplist]
  df_HEsubclmap = df_HEclmap[HElmaplist]

  df_HFlmap = pd.read_sql("SELECT * FROM ngHFLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  df_HFclmap = pd.read_sql("SELECT * FROM ngHFCalibLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  HFlmaplist = ['Side', 'Eta', 'Phi', 'Depth', 'Det', 'QIECH', 'QIE10id']
  df_HFsublmap = df_HFlmap[HFlmaplist]
  df_HFsubclmap = df_HFclmap[HFlmaplist]

  df_HOlmap = pd.read_sql("SELECT * FROM ngHOLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  df_HOclmap = pd.read_sql("SELECT * FROM ngHOCalibLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  HOlmaplist = ['Side', 'Eta', 'Phi', 'Depth', 'Det', 'QIECH', 'QIEid']
  df_HOsublmap = df_HOlmap[HOlmaplist]
  df_HOsubclmap = df_HOclmap[HOlmaplist]

  sql_con_lmap.close()
  return df_HBsublmap, df_HEsublmap, df_HFsublmap, df_HOsublmap, df_HBsubclmap, df_HEsubclmap, df_HFsubclmap, df_HOsubclmap

def GetQIE8DataFrame( rel_qie8_path ):
  sql_engine_qie8 = create_engine( rel_qie8_path )
  sql_con_qie8 = sql_engine_qie8.raw_connection()
  
  df_qie8 = pd.read_sql("SELECT * FROM QIE8CalibFNALNormal", con = sql_con_qie8, index_col = ['index'])
  df_qie8.drop(['Mode', 'Run'], axis=1, inplace=True)
  df_qie8_offset_pv = pd.pivot_table(df_qie8, index = ['QIE8ID', 'Ch'], columns=['Cap','Rng'], values='Offset')
  df_qie8_slope_pv = pd.pivot_table(df_qie8, index = ['QIE8ID', 'Ch'], columns=['Cap','Rng'], values='Slope')

  # QIECH = 999991
#  df_qie8_offset_pv_ave_1 = df_qie8_offset_pv.groupby([df_qie8_offset_pv.index.get_level_values(1)], axis=0).mean()
#  df_qie8_offset_pv_ave_1.reset_index(inplace = True)
#  df_qie8_offset_pv_ave_1['QIE8ID'] = [999991] * df_qie8_offset_pv_ave_1.shape[0]
#  df_qie8_offset_pv_ave_1.set_index(['QIE8ID', 'Ch'], inplace = True)
  
#  df_qie8_slope_pv_ave_1 = df_qie8_slope_pv.groupby([df_qie8_offset_pv.index.get_level_values(1)], axis=0).mean()
#  df_qie8_slope_pv_ave_1.reset_index(inplace = True)
#  df_qie8_slope_pv_ave_1['QIE8ID'] = [999991] * df_qie8_slope_pv_ave_1.shape[0]
#  df_qie8_slope_pv_ave_1.set_index(['QIE8ID', 'Ch'], inplace = True)

  # QIECH = 999994
  df_qie8_offset_pv_ave_2 = df_qie8_offset_pv.groupby([df_qie8_offset_pv.index.get_level_values(1)], axis=0).mean()
  df_qie8_offset_pv_ave_2.reset_index(inplace = True)
  df_qie8_offset_pv_ave_2['QIE8ID'] = [999994] * df_qie8_offset_pv_ave_2.shape[0]
  df_qie8_offset_pv_ave_2.set_index(['QIE8ID', 'Ch'], inplace = True)
  
  df_qie8_slope_pv_ave_2 = df_qie8_slope_pv.groupby([df_qie8_offset_pv.index.get_level_values(1)], axis=0).mean()
  df_qie8_slope_pv_ave_2.reset_index(inplace = True)
  df_qie8_slope_pv_ave_2['QIE8ID'] = [999994] * df_qie8_slope_pv_ave_2.shape[0]
  df_qie8_slope_pv_ave_2.set_index(['QIE8ID', 'Ch'], inplace = True)

#  df_qie8_offset_pv = df_qie8_offset_pv.append(df_qie8_offset_pv_ave_1)
#  df_qie8_slope_pv = df_qie8_slope_pv.append(df_qie8_slope_pv_ave_1) 
  df_qie8_offset_pv = df_qie8_offset_pv.append(df_qie8_offset_pv_ave_2)
  df_qie8_slope_pv = df_qie8_slope_pv.append(df_qie8_slope_pv_ave_2)
  sql_con_qie8.close()
  return df_qie8_offset_pv, df_qie8_slope_pv

def GetQIE10DataFrame( rel_qie10_path ):
  sql_engine_qie10 = create_engine( rel_qie10_path )
  sql_con_qie10 = sql_engine_qie10.raw_connection()
  df_qie10 = pd.read_sql("SELECT * FROM qieparams", con = sql_con_qie10)
  #df_qie10 = pd.read_sql("SELECT * FROM qieparams", con = sql_con_qie10, index_col = ['index'])
  df_qie10.drop(['id', 'date', 'directoryname'], axis=1, inplace=True)
  df_qie10_offset_pv = pd.pivot_table(df_qie10, index = ['serial', 'qie'], columns=['capID','range'], values='offset')
  df_qie10_slope_pv = pd.pivot_table(df_qie10, index = ['serial', 'qie'], columns=['capID','range'], values='slope')

  df_qie10_offset_pv_ave = df_qie10_offset_pv.groupby([df_qie10_offset_pv.index.get_level_values(1)], axis=0).mean()
  df_qie10_offset_pv_ave.reset_index(inplace = True)
  df_qie10_offset_pv_ave['serial'] = [999993] * df_qie10_offset_pv_ave.shape[0]
  df_qie10_offset_pv_ave.set_index(['serial', 'qie'], inplace = True)
  
  df_qie10_slope_pv_ave = df_qie10_slope_pv.groupby([df_qie10_offset_pv.index.get_level_values(1)], axis=0).mean()
  df_qie10_slope_pv_ave.reset_index(inplace = True)
  df_qie10_slope_pv_ave['serial'] = [999993] * df_qie10_slope_pv_ave.shape[0]
  df_qie10_slope_pv_ave.set_index(['serial', 'qie'], inplace = True)

  df_qie10_offset_pv = df_qie10_offset_pv.append(df_qie10_offset_pv_ave)
  df_qie10_slope_pv = df_qie10_slope_pv.append(df_qie10_slope_pv_ave)
  sql_con_qie10.close()
  return df_qie10_offset_pv, df_qie10_slope_pv

def GetQIE11DataFrame( rel_qie11_path, shuntAndGsel ):
  sql_engine_qie11 = create_engine( rel_qie11_path )
  sql_con_qie11 = sql_engine_qie11.raw_connection()
  SQLQuery = "SELECT * FROM qieshuntparams WHERE " + shuntAndGsel
  #df_qie11 = pd.read_sql("SELECT * FROM qieshuntparams WHERE shunt=1 AND Gsel=0", con = sql_con_qie11)
  df_qie11 = pd.read_sql(SQLQuery, con = sql_con_qie11)
  df_qie11.drop(['id', 'shunt', 'Gsel', 'uncertainty'], axis=1, inplace=True)
  df_qie11_offset_pv = pd.pivot_table(df_qie11, index = ['barcode', 'qie'], columns=['capID','range'], values='offset')
  df_qie11_slope_pv = pd.pivot_table(df_qie11, index = ['barcode', 'qie'], columns=['capID','range'], values='slope')

  df_qie11_offset_pv_ave = df_qie11_offset_pv.groupby([df_qie11_offset_pv.index.get_level_values(1)], axis=0).mean()
  df_qie11_offset_pv_ave.reset_index(inplace = True)
  df_qie11_offset_pv_ave['barcode'] = [999992] * df_qie11_offset_pv_ave.shape[0]
  df_qie11_offset_pv_ave.set_index(['barcode', 'qie'], inplace = True)
  
  df_qie11_slope_pv_ave = df_qie11_slope_pv.groupby([df_qie11_offset_pv.index.get_level_values(1)], axis=0).mean()
  df_qie11_slope_pv_ave.reset_index(inplace = True)
  df_qie11_slope_pv_ave['barcode'] = [999992] * df_qie11_slope_pv_ave.shape[0]
  df_qie11_slope_pv_ave.set_index(['barcode', 'qie'], inplace = True)

  df_qie11_offset_pv = df_qie11_offset_pv.append(df_qie11_offset_pv_ave)
  df_qie11_slope_pv = df_qie11_slope_pv.append(df_qie11_slope_pv_ave)
  sql_con_qie11.close()
  return df_qie11_offset_pv, df_qie11_slope_pv

def GetHBQIE11DataFrame( rel_hb_qie11_path, shuntAndGsel ):
  sql_engine_hb_qie11 = create_engine( rel_hb_qie11_path )
  sql_con_hb_qie11 = sql_engine_hb_qie11.raw_connection()
  SQLQuery = "SELECT * FROM qieshuntparams WHERE " + shuntAndGsel
  #df_hb_qie11 = pd.read_sql("SELECT * FROM qieshuntparams WHERE shunt=1 AND Gsel=0", con = sql_con_hb_qie11)
  df_hb_qie11 = pd.read_sql(SQLQuery, con = sql_con_hb_qie11)
  df_hb_qie11.drop(['id', 'shunt', 'Gsel'], axis=1, inplace=True)
  df_hb_qie11_offset_pv = pd.pivot_table(df_hb_qie11, index = ['barcode', 'qie'], columns=['capID','range'], values='offset')
  df_hb_qie11_slope_pv = pd.pivot_table(df_hb_qie11, index = ['barcode', 'qie'], columns=['capID','range'], values='slope')

  df_hb_qie11_offset_pv_ave = df_hb_qie11_offset_pv.groupby([df_hb_qie11_offset_pv.index.get_level_values(1)], axis=0).mean()
  df_hb_qie11_offset_pv_ave.reset_index(inplace = True)
  df_hb_qie11_offset_pv_ave['barcode'] = [999991] * df_hb_qie11_offset_pv_ave.shape[0]
  df_hb_qie11_offset_pv_ave.set_index(['barcode', 'qie'], inplace = True)
  
  df_hb_qie11_slope_pv_ave = df_hb_qie11_slope_pv.groupby([df_hb_qie11_offset_pv.index.get_level_values(1)], axis=0).mean()
  df_hb_qie11_slope_pv_ave.reset_index(inplace = True)
  df_hb_qie11_slope_pv_ave['barcode'] = [999991] * df_hb_qie11_slope_pv_ave.shape[0]
  df_hb_qie11_slope_pv_ave.set_index(['barcode', 'qie'], inplace = True)

  df_hb_qie11_offset_pv = df_hb_qie11_offset_pv.append(df_hb_qie11_offset_pv_ave)
  df_hb_qie11_slope_pv = df_hb_qie11_slope_pv.append(df_hb_qie11_slope_pv_ave)
  sql_con_hb_qie11.close()
  return df_hb_qie11_offset_pv, df_hb_qie11_slope_pv

def DumpngHBQIE11Table( df_ngHBsublmap, df_hb_qie11_offset_pv, df_hb_qie11_slope_pv, ofile="HBQIE11.txt" ):

  out = open(ofile, "w")
  df_HBQIE_res = df_ngHBsublmap[['Side', 'Eta', 'Phi', 'Depth', 'Det']]
  offsets = []
  slopes = []

  for index, row in df_ngHBsublmap.iterrows():
    thisindex = (row['QIEid'], row['QIECH'])
    if thisindex in df_hb_qie11_offset_pv.index:
      offsets.append(df_hb_qie11_offset_pv.loc[thisindex, :].values)
      slopes.append(df_hb_qie11_slope_pv.loc[thisindex, :].values)
    else:
      offsets.append(df_hb_qie11_offset_pv.loc[(999991, row['QIECH']), :].values)
      slopes.append(df_hb_qie11_slope_pv.loc[(999991, row['QIECH']), :].values)

  pd.options.mode.chained_assignment = None  # default='warn'
  df_HBQIE_res['Offsets'] = pd.Series(offsets).values
  df_HBQIE_res['Slopes'] = pd.Series(slopes).values
  
  print('# HB QIE8 Constants table')
  print('# Eta Phi Depth Det Offsets*16 Slopes*16')
  sys.stdout = out
  for index, row in df_HBQIE_res.iterrows():
    #if index > 5:
    #  break
    if int(row['Depth']) == 7: continue
    toprint = [int(row['Side'])*int(row['Eta']), int(row['Phi']), int(row['Depth']), row['Det']]
    toprint = toprint + list(map(float, row['Offsets'])) + list(map(float, row['Slopes']))
    print("{: <5d}{: <5d}{: <5d}{}  {: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}".format(*toprint))

    #print("%d   %d   %d   %s   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f   %.5f" % (int(row['Side'])*int(row['Eta']), int(row['Phi']), int(row['Depth']), row['Det'], float(row['Offsets'][0]), float(row['Offsets'][1]), float(row['Offsets'][2]), float(row['Offsets'][3]), float(row['Offsets'][4]), float(row['Offsets'][5]), float(row['Offsets'][6]), float(row['Offsets'][7]), float(row['Offsets'][8]), float(row['Offsets'][9]), float(row['Offsets'][10]), float(row['Offsets'][11]), float(row['Offsets'][12]), float(row['Offsets'][13]), float(row['Offsets'][14]), float(row['Offsets'][15]), float(row['Slopes'][0]), float(row['Slopes'][1]), float(row['Slopes'][2]), float(row['Slopes'][3]), float(row['Slopes'][4]), float(row['Slopes'][5]), float(row['Slopes'][6]), float(row['Slopes'][7]), float(row['Slopes'][8]), float(row['Slopes'][9]), float(row['Slopes'][10]), float(row['Slopes'][11]), float(row['Slopes'][12]), float(row['Slopes'][13]), float(row['Slopes'][14]), float(row['Slopes'][15])))

  sys.stdout = stdout
  out.close()
  return ;

def DumpngHEQIE11Table( df_ngHEsublmap, df_qie11_offset_pv, df_qie11_slope_pv, ofile="HEQIE11.txt", debug = False ):

  out = open(ofile, "w")
  df_HEQIE_res = df_ngHEsublmap[['Side', 'Eta', 'Phi', 'Depth', 'Det']]
  offsets = []
  slopes = []
  QIE11_dbmissing = []
  
  #ngHE em... need to deal with missing QIE11ID
  for index, row in df_ngHEsublmap.iterrows():
    thisindex = (row['QIEid'], row['QIECH'])                                                                                                                                                              
    if thisindex in df_qie11_offset_pv.index:
      offsets.append(df_qie11_offset_pv.loc[thisindex, :].values)
      slopes.append(df_qie11_slope_pv.loc[thisindex, :].values)
    else:
      QIE11_dbmissing.append(thisindex[0])
      offsets.append(df_qie11_offset_pv.loc[(999992, row['QIECH']), :].values)
      slopes.append(df_qie11_slope_pv.loc[(999992, row['QIECH']), :].values)

  if( debug ):
    print('# Missing QIE11 IDs in the database are: ')
    print(list(set(QIE11_dbmissing)))
    return ;

  pd.options.mode.chained_assignment = None  # default='warn'
  df_HEQIE_res['Offsets'] = pd.Series(offsets).values
  df_HEQIE_res['Slopes'] = pd.Series(slopes).values
  
  print('# HE QIE11 Constants table')
  print('# Eta Phi Depth Det Offsets*16 Slopes*16')
  sys.stdout = out
  for index, row in df_HEQIE_res.iterrows():
#    if int(row['Depth']) == 7: continue
    toprint = [int(row['Side'])*int(row['Eta']), int(row['Phi']), int(row['Depth']), row['Det']]
    toprint = toprint + list(map(float, row['Offsets'])) + list(map(float, row['Slopes']))
    print("{: <5d}{: <5d}{: <5d}{}  {: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}".format(*toprint))
#    if row['Det'] != 'HEX':
#      print row['Side']*row['Eta'], row['Phi'], row['Depth'], row['Det'], row['Offsets'][0], row['Offsets'][1], row['Offsets'][2], row['Offsets'][3], row['Offsets'][4], row['Offsets'][5], row['Offsets'][6], row['Offsets'][7], row['Offsets'][8], row['Offsets'][9], row['Offsets'][10], row['Offsets'][11], row['Offsets'][12], row['Offsets'][13], row['Offsets'][14], row['Offsets'][15], row['Slopes'][0], row['Slopes'][1], row['Slopes'][2], row['Slopes'][3], row['Slopes'][4], row['Slopes'][5], row['Slopes'][6], row['Slopes'][7], row['Slopes'][8], row['Slopes'][9], row['Slopes'][10], row['Slopes'][11], row['Slopes'][12], row['Slopes'][13], row['Slopes'][14], row['Slopes'][15]

  sys.stdout = stdout
  out.close()
  return ;

def DumpngHFQIE10Table( df_ngHFsublmap, df_qie10_offset_pv, df_qie10_slope_pv, ofile="HFQIE10.txt", debug = False):

  out = open(ofile, "w")
  df_HFQIE_res = df_ngHFsublmap[['Side', 'Eta', 'Phi', 'Depth', 'Det']]
  offsets = []
  slopes = []
  QIE10_dbmissing = []

  #ngHF have a good db for normal channels, therefore no missing entries. So no average card. But missing some calibration channels
  for index, row in df_ngHFsublmap.iterrows():
    thisindex = (row['QIE10id'], row['QIECH'])
    if thisindex in df_qie10_offset_pv.index:
      offsets.append(df_qie10_offset_pv.loc[thisindex, :].values)
      slopes.append(df_qie10_slope_pv.loc[thisindex, :].values)
    else:
      QIE10_dbmissing.append(thisindex[0])
      offsets.append(df_qie10_offset_pv.loc[(999993, row['QIECH']), :].values)
      slopes.append(df_qie10_slope_pv.loc[(999993, row['QIECH']), :].values)
  
  if( debug ):
    print('# Missing QIE10 IDs in the database are: ')
    print(list(set(QIE10_dbmissing)))
    return ;

  pd.options.mode.chained_assignment = None  # default='warn'
  df_HFQIE_res['Offsets'] = pd.Series(offsets).values
  df_HFQIE_res['Slopes'] = pd.Series(slopes).values
  
  print('# HF QIE10 Constants table')
  print('# Eta Phi Depth Det Offsets*16 Slopes*16')
  sys.stdout = out
  for index, row in df_HFQIE_res.iterrows():
    toprint = [int(row['Side'])*int(row['Eta']), int(row['Phi']), int(row['Depth']), row['Det']]
    toprint = toprint + list(map(float, row['Offsets'])) + list(map(float, row['Slopes']))
    print("{: <5d}{: <5d}{: <5d}{}  {: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}".format(*toprint))
#    print row['Side']*row['Eta'], row['Phi'], row['Depth'], row['Det'], row['Offsets'][0], row['Offsets'][1], row['Offsets'][2], row['Offsets'][3], row['Offsets'][4], row['Offsets'][5], row['Offsets'][6], row['Offsets'][7], row['Offsets'][8], row['Offsets'][9], row['Offsets'][10], row['Offsets'][11], row['Offsets'][12], row['Offsets'][13], row['Offsets'][14], row['Offsets'][15], row['Slopes'][0], row['Slopes'][1], row['Slopes'][2], row['Slopes'][3], row['Slopes'][4], row['Slopes'][5], row['Slopes'][6], row['Slopes'][7], row['Slopes'][8], row['Slopes'][9], row['Slopes'][10], row['Slopes'][11], row['Slopes'][12], row['Slopes'][13], row['Slopes'][14], row['Slopes'][15]

  sys.stdout = stdout
  out.close()
  return ;

def DumpngHOQIE8Table( df_ngHOsublmap, df_qie8_offset_pv, df_qie8_slope_pv, ofile="HOQIE8.txt" ):

  out = open(ofile, "w")
  df_HOQIE_res = df_ngHOsublmap[['Side', 'Eta', 'Phi', 'Depth', 'Det']]
  offsets = []
  slopes = []

  for index, row in df_ngHOsublmap.iterrows():
    thisindex = (row['QIEid'], row['QIECH'])
    if thisindex in df_qie8_offset_pv.index:
      offsets.append(df_qie8_offset_pv.loc[thisindex, :].values)
      slopes.append(df_qie8_slope_pv.loc[thisindex, :].values)
    else:
      offsets.append(df_qie8_offset_pv.loc[(999994, row['QIECH']), :].values)
      slopes.append(df_qie8_slope_pv.loc[(999994, row['QIECH']), :].values)

  pd.options.mode.chained_assignment = None  # default='warn'
  df_HOQIE_res['Offsets'] = pd.Series(offsets).values
  df_HOQIE_res['Slopes'] = pd.Series(slopes).values
  
  print('# HO QIE8 Constants table')
  print('# Eta Phi Depth Det Offsets*16 Slopes*16')
  sys.stdout = out
  for index, row in df_HOQIE_res.iterrows():
    toprint = [int(row['Side'])*int(row['Eta']), int(row['Phi']), int(row['Depth']), row['Det']]
    toprint = toprint + list(map(float, row['Offsets'][0])) + list(map(float, row['Slopes'][0]))
    print("{: <5d}{: <5d}{: <5d}{}  {: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}{: <12.5f}".format(*toprint))
#    if row['Det'] != 'HOX':
#      print row['Side']*row['Eta'], row['Phi'], row['Depth'], row['Det'], row['Offsets'][0], row['Offsets'][1], row['Offsets'][2], row['Offsets'][3], row['Offsets'][4], row['Offsets'][5], row['Offsets'][6], row['Offsets'][7], row['Offsets'][8], row['Offsets'][9], row['Offsets'][10], row['Offsets'][11], row['Offsets'][12], row['Offsets'][13], row['Offsets'][14], row['Offsets'][15], row['Slopes'][0], row['Slopes'][1], row['Slopes'][2], row['Slopes'][3], row['Slopes'][4], row['Slopes'][5], row['Slopes'][6], row['Slopes'][7], row['Slopes'][8], row['Slopes'][9], row['Slopes'][10], row['Slopes'][11], row['Slopes'][12], row['Slopes'][13], row['Slopes'][14], row['Slopes'][15]

  sys.stdout = stdout
  out.close()
  return ;

if __name__ == '__main__':
  # define argument
  parser = optparse.OptionParser('usage: %prog [options]')
  parser.add_option('--QIE11Mode', dest='qie11mode', help='set up QIE11 mode', default='Normal')
  #Normal for shunt6 regular HE channels, shunt1 for calib HE channels; Special for shunt1 for both regular and calib HE channels
  (opt, args) = parser.parse_args()
  # load lmap HB, HE, HF, HO
  df_ngHBsublmap, df_ngHEsublmap, df_ngHFsublmap, df_ngHOsublmap, df_ngHBsubclmap, df_ngHEsubclmap, df_ngHFsubclmap, df_ngHOsubclmap = GetLMapDataFrame( 'sqlite:///../officialMap/HCALLogicalMap.db' )

  # load qie8 tables offsets and slopes
  #df_qie8_offset_pv, df_qie8_slope_pv = GetQIE8DataFrame( 'sqlite:///qie8_database/QIE8ConstantFNALNormal_DropFcs.db' )
  #df_qie8_offset_pv, df_qie8_slope_pv = GetQIE8DataFrame( 'sqlite:////eos/user/h/hua/QIEDB/qie8_database/QIE8ConstantFNALNormal_DropFcs.db' )
  df_qie8_offset_pv, df_qie8_slope_pv = GetQIE8DataFrame( 'sqlite:///../QIEDatabase/QIE8ConstantFNALNormal_DropFcs.db' )
  #print (df_qie8_offset_pv.head())
  #print (df_qie8_slope_pv.head())
  
  # load qie10 tables offsets and slopes
  #df_qie10_offset_pv, df_qie10_slope_pv = GetQIE10DataFrame( 'sqlite:///qie10_database/qieCalibrationParameters_HF_2017-04-24.db' )
  #df_qie10_offset_pv, df_qie10_slope_pv = GetQIE10DataFrame( 'sqlite:////eos/user/h/hua/QIEDB/qie10_database/qieCalibrationParameters_HF_2017-04-24.db' )
  df_qie10_offset_pv, df_qie10_slope_pv = GetQIE10DataFrame( 'sqlite:///../QIEDatabase/qieCalibrationParameters_HF.db' )
  #print (df_qie10_offset_pv.tail())
  #print (df_qie10_slope_pv.tail())

  # load qie11 tables offsets and slopes
  #print opt.heqie11mode
  # https://cms-docdb.cern.ch/cgi-bin/DocDB/ShowDocument?docid=13288
  df_qie11_offset_pv_s1, df_qie11_slope_pv_s1 = GetQIE11DataFrame( 'sqlite:///../QIEDatabase/HE_all640cards_parameters.db', "shunt=1 AND Gsel=0" )
  df_qie11_offset_pv_s6, df_qie11_slope_pv_s6 = GetQIE11DataFrame( 'sqlite:///../QIEDatabase/HE_all640cards_parameters.db', "shunt=6 AND Gsel=18" )
  #print (df_qie11_offset_pv.tail(12))
  #print (df_qie11_slope_pv.tail(12))

  # load HB qie11 tables
  # https://cms-docdb.cern.ch/cgi-bin/DocDB/ShowDocument?docid=13701
  df_hb_qie11_offset_pv_s1, df_hb_qie11_slope_pv_s1 = GetHBQIE11DataFrame( 'sqlite:///../QIEDatabase/HB_QIE11_Calibrations.db', "shunt=1 AND Gsel=0" )
  df_hb_qie11_offset_pv_s6, df_hb_qie11_slope_pv_s6 = GetHBQIE11DataFrame( 'sqlite:///../QIEDatabase/HB_QIE11_Calibrations.db', "shunt=6 AND Gsel=18" )

  if (opt.qie11mode == "Normal"):
    DumpngHEQIE11Table( df_ngHEsublmap, df_qie11_offset_pv_s6, df_qie11_slope_pv_s6, "HE_QIE11Calibrations_RM_shunt6.txt", debug = False )
    DumpngHEQIE11Table( df_ngHEsubclmap, df_qie11_offset_pv_s6, df_qie11_slope_pv_s6, "HE_QIE11Calibrations_CU_shunt6.txt", debug = False )
    DumpngHBQIE11Table( df_ngHBsublmap, df_hb_qie11_offset_pv_s6, df_hb_qie11_slope_pv_s6, "HB_QIE11Calibrations_RM_shunt6.txt" )
    DumpngHBQIE11Table( df_ngHBsubclmap, df_hb_qie11_offset_pv_s6, df_hb_qie11_slope_pv_s6, "HB_QIE11Calibrations_CU_shunt6.txt" )
  elif (opt.qie11mode == "Special"):
    DumpngHEQIE11Table( df_ngHEsublmap, df_qie11_offset_pv_s1, df_qie11_slope_pv_s1, "HE_QIE11Calibrations_RM_shunt1.txt", debug = False )
    DumpngHEQIE11Table( df_ngHEsubclmap, df_qie11_offset_pv_s1, df_qie11_slope_pv_s1, "HE_QIE11Calibrations_CU_shunt1.txt", debug = False )
    DumpngHBQIE11Table( df_ngHBsublmap, df_hb_qie11_offset_pv_s1, df_hb_qie11_slope_pv_s1, "HB_QIE11Calibrations_RM_shunt1.txt" )
    DumpngHBQIE11Table( df_ngHBsubclmap, df_hb_qie11_offset_pv_s1, df_hb_qie11_slope_pv_s1, "HB_QIE11Calibrations_CU_shunt1.txt" )
  else:
    print("#Invalid QIE11 Mode! Please check!")
  DumpngHFQIE10Table( df_ngHFsublmap, df_qie10_offset_pv, df_qie10_slope_pv, "HF_QIE11Calibrations_RM.txt", debug = False )
  DumpngHFQIE10Table( df_ngHFsubclmap, df_qie10_offset_pv, df_qie10_slope_pv, "HF_QIE11Calibrations_CU.txt", debug = False )
  DumpngHOQIE8Table( df_ngHOsublmap, df_qie8_offset_pv, df_qie8_slope_pv , "HO_QIE11Calibrations_RM.txt")
  DumpngHOQIE8Table( df_ngHOsubclmap, df_qie8_offset_pv, df_qie8_slope_pv , "HO_QIE11Calibrations_CU.txt")

  #DumpngHFQIE10Table( df_LMsublmap, df_qie10_offset_pv, df_qie10_slope_pv, debug = False )
  #DumpngHEQIE11Table( df_HEP17sublmap, df_qie11_offset_pv, df_qie11_slope_pv )
