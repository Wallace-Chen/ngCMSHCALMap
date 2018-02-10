from sqlalchemy import create_engine
import pandas as pd
import os

def GetLMapDataFrame( rel_lmap_path ):
  sql_engine_lmap = create_engine( rel_lmap_path )
  sql_con_lmap = sql_engine_lmap.raw_connection()

  df_HBlmap = pd.read_sql("SELECT * FROM HBLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  df_HBclmap = pd.read_sql("SELECT * FROM HBCalibLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  HBlmaplist = ['Side', 'Eta', 'Phi', 'Depth', 'Det', 'QIECH', 'QIE8id']
  df_HBsublmap = df_HBlmap[HBlmaplist]
  df_HBsubclmap = df_HBclmap[HBlmaplist]

  df_HElmap = pd.read_sql("SELECT * FROM ngHELogicalMap", con = sql_con_lmap, index_col = ['ID'])
  df_HEclmap = pd.read_sql("SELECT * FROM ngHECalibLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  HElmaplist = ['Side', 'Eta', 'Phi', 'Depth', 'Det', 'QIECH', 'QIE11id']
  df_HEsublmap = df_HElmap[HElmaplist]
  df_HEsubclmap = df_HEclmap[HElmaplist]

  df_HFlmap = pd.read_sql("SELECT * FROM ngHFLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  df_HFclmap = pd.read_sql("SELECT * FROM ngHFCalibLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  HFlmaplist = ['Side', 'Eta', 'Phi', 'Depth', 'Det', 'QIECH', 'QIE10id']
  df_HFsublmap = df_HFlmap[HFlmaplist]
  df_HFsubclmap = df_HFclmap[HFlmaplist]

  df_HOlmap = pd.read_sql("SELECT * FROM HOLogicalMap", con = sql_con_lmap, index_col = ['ID'])                                                                                                             
  HOlmaplist = ['Side', 'Eta', 'Phi', 'Depth', 'Det', 'QIECH', 'QIE8id']
  df_HOsublmap = df_HOlmap[HOlmaplist]

  sql_con_lmap.close()
  return df_HBsublmap, df_HEsublmap, df_HFsublmap, df_HOsublmap, df_HBsubclmap, df_HEsubclmap, df_HFsubclmap

def GetQIE8DataFrame( rel_qie8_path ):
  sql_engine_qie8 = create_engine( rel_qie8_path )
  sql_con_qie8 = sql_engine_qie8.raw_connection()
  
  df_qie8 = pd.read_sql("SELECT * FROM QIE8CalibFNALNormal", con = sql_con_qie8, index_col = ['index'])
  df_qie8.drop(['Mode', 'Run'], axis=1, inplace=True)
  df_qie8_offset_pv = pd.pivot_table(df_qie8, index = ['QIE8ID', 'Ch'], columns=['Cap','Rng'], values='Offset')
  df_qie8_slope_pv = pd.pivot_table(df_qie8, index = ['QIE8ID', 'Ch'], columns=['Cap','Rng'], values='Slope')

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

  sql_con_qie10.close()
  return df_qie10_offset_pv, df_qie10_slope_pv

def GetQIE11DataFrame( rel_qie11_path, shuntAndGsel):
  sql_engine_qie11 = create_engine( rel_qie11_path )
  sql_con_qie11 = sql_engine_qie11.raw_connection()
  SQLQuery = "SELECT * FROM qieshuntparams WHERE " + shuntAndGsel
  #df_qie11 = pd.read_sql("SELECT * FROM qieshuntparams WHERE shunt=1 AND Gsel=0", con = sql_con_qie11)
  df_qie11 = pd.read_sql(SQLQuery, con = sql_con_qie11)
  df_qie11.drop(['id', 'shunt', 'Gsel', 'uncertainty'], axis=1, inplace=True)
  df_qie11_offset_pv = pd.pivot_table(df_qie11, index = ['barcode', 'qie'], columns=['capID','range'], values='offset')
  df_qie11_slope_pv = pd.pivot_table(df_qie11, index = ['barcode', 'qie'], columns=['capID','range'], values='slope')

  sql_con_qie11.close()
  return df_qie11_offset_pv, df_qie11_slope_pv

def DumpHBQIE8Table( df_HBsublmap, df_qie8_offset_pv, df_qie8_slope_pv ):

  df_HBQIE_res = df_HBsublmap[['Side', 'Eta', 'Phi', 'Depth', 'Det']]
  offsets = []
  slopes = []

  for index, row in df_HBsublmap.iterrows():
    thisindex = (row['QIE8id'], row['QIECH'])
    if thisindex in df_qie8_offset_pv.index:
      offsets.append(df_qie8_offset_pv.loc[thisindex, :].values)
      slopes.append(df_qie8_slope_pv.loc[thisindex, :].values)
    else:
      offsets.append(df_qie8_offset_pv.loc[(999991, row['QIECH']), :].values)
      slopes.append(df_qie8_slope_pv.loc[(999991, row['QIECH']), :].values)

  pd.options.mode.chained_assignment = None  # default='warn'
  df_HBQIE_res['Offsets'] = pd.Series(offsets).values
  df_HBQIE_res['Slopes'] = pd.Series(slopes).values
  
  print('# HB QIE8 Constants table')
  print('# Eta Phi Depth Det Offsets*16 Slopes*16')
  for index, row in df_HBQIE_res.iterrows():
    #if index > 5:
    #  break
    print row['Side']*row['Eta'], row['Phi'], row['Depth'], row['Det'], row['Offsets'][0], row['Offsets'][1], row['Offsets'][2], row['Offsets'][3], row['Offsets'][4], row['Offsets'][5], row['Offsets'][6], row['Offsets'][7], row['Offsets'][8], row['Offsets'][9], row['Offsets'][10], row['Offsets'][11], row['Offsets'][12], row['Offsets'][13], row['Offsets'][14], row['Offsets'][15], row['Slopes'][0], row['Slopes'][1], row['Slopes'][2], row['Slopes'][3], row['Slopes'][4], row['Slopes'][5], row['Slopes'][6], row['Slopes'][7], row['Slopes'][8], row['Slopes'][9], row['Slopes'][10], row['Slopes'][11], row['Slopes'][12], row['Slopes'][13], row['Slopes'][14], row['Slopes'][15]

  return ;

def DumpHEQIE11Table( df_HEsublmap, df_qie11_offset_pv, df_qie11_slope_pv ):

  df_HEQIE_res = df_HEsublmap[['Side', 'Eta', 'Phi', 'Depth', 'Det']]
  offsets = []
  slopes = []

  #ngHE have a good db, therefore no missing entries. So no average card
  for index, row in df_HEsublmap.iterrows():
    thisindex = (row['QIE11id'], row['QIECH'])                                                                                                                                                              
    if thisindex in df_qie11_offset_pv.index:
      offsets.append(df_qie11_offset_pv.loc[thisindex, :].values)
      slopes.append(df_qie11_slope_pv.loc[thisindex, :].values)
    else:
      print(thisindex)
    #  offsets.append(df_qie8_offset_pv.loc[(999994, row['QIECH']), :].values)
    #  slopes.append(df_qie8_slope_pv.loc[(999994, row['QIECH']), :].values)

  pd.options.mode.chained_assignment = None  # default='warn'
  df_HEQIE_res['Offsets'] = pd.Series(offsets).values
  df_HEQIE_res['Slopes'] = pd.Series(slopes).values
  
  print('# HE QIE11 Constants table')
  print('# Eta Phi Depth Det Offsets*16 Slopes*16')
  for index, row in df_HEQIE_res.iterrows():
    print row['Side']*row['Eta'], row['Phi'], row['Depth'], row['Det'], row['Offsets'][0], row['Offsets'][1], row['Offsets'][2], row['Offsets'][3], row['Offsets'][4], row['Offsets'][5], row['Offsets'][6], row['Offsets'][7], row['Offsets'][8], row['Offsets'][9], row['Offsets'][10], row['Offsets'][11], row['Offsets'][12], row['Offsets'][13], row['Offsets'][14], row['Offsets'][15], row['Slopes'][0], row['Slopes'][1], row['Slopes'][2], row['Slopes'][3], row['Slopes'][4], row['Slopes'][5], row['Slopes'][6], row['Slopes'][7], row['Slopes'][8], row['Slopes'][9], row['Slopes'][10], row['Slopes'][11], row['Slopes'][12], row['Slopes'][13], row['Slopes'][14], row['Slopes'][15]

  return ;

def DumpHFQIE10Table( df_HFsublmap, df_qie10_offset_pv, df_qie10_slope_pv ):

  df_HFQIE_res = df_HFsublmap[['Side', 'Eta', 'Phi', 'Depth', 'Det']]
  offsets = []
  slopes = []

  #ngHF have a good db, therefore no missing entries. So no average card
  for index, row in df_HFsublmap.iterrows():
    thisindex = (row['QIE10id'], row['QIECH'])
    if thisindex in df_qie10_offset_pv.index:
      offsets.append(df_qie10_offset_pv.loc[thisindex, :].values)
      slopes.append(df_qie10_slope_pv.loc[thisindex, :].values)
    else:
      print(thisindex)
    #  offsets.append(df_qie10_offset_pv.loc[(999994, row['QIECH']), :].values)
    #  slopes.append(df_qie10_slope_pv.loc[(999994, row['QIECH']), :].values)

  pd.options.mode.chained_assignment = None  # default='warn'
  df_HFQIE_res['Offsets'] = pd.Series(offsets).values
  df_HFQIE_res['Slopes'] = pd.Series(slopes).values
  
  print('# HF QIE10 Constants table')
  print('# Eta Phi Depth Det Offsets*16 Slopes*16')
  for index, row in df_HFQIE_res.iterrows():
    print row['Side']*row['Eta'], row['Phi'], row['Depth'], row['Det'], row['Offsets'][0], row['Offsets'][1], row['Offsets'][2], row['Offsets'][3], row['Offsets'][4], row['Offsets'][5], row['Offsets'][6], row['Offsets'][7], row['Offsets'][8], row['Offsets'][9], row['Offsets'][10], row['Offsets'][11], row['Offsets'][12], row['Offsets'][13], row['Offsets'][14], row['Offsets'][15], row['Slopes'][0], row['Slopes'][1], row['Slopes'][2], row['Slopes'][3], row['Slopes'][4], row['Slopes'][5], row['Slopes'][6], row['Slopes'][7], row['Slopes'][8], row['Slopes'][9], row['Slopes'][10], row['Slopes'][11], row['Slopes'][12], row['Slopes'][13], row['Slopes'][14], row['Slopes'][15]

  return ;

def DumpHOQIE8Table( df_HOsublmap, df_qie8_offset_pv, df_qie8_slope_pv ):

  df_HOQIE_res = df_HOsublmap[['Side', 'Eta', 'Phi', 'Depth', 'Det']]
  offsets = []
  slopes = []

  for index, row in df_HOsublmap.iterrows():
    thisindex = (row['QIE8id'], row['QIECH'])
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
  for index, row in df_HOQIE_res.iterrows():
    if row['Det'] != 'HOX':
      print row['Side']*row['Eta'], row['Phi'], row['Depth'], row['Det'], row['Offsets'][0], row['Offsets'][1], row['Offsets'][2], row['Offsets'][3], row['Offsets'][4], row['Offsets'][5], row['Offsets'][6], row['Offsets'][7], row['Offsets'][8], row['Offsets'][9], row['Offsets'][10], row['Offsets'][11], row['Offsets'][12], row['Offsets'][13], row['Offsets'][14], row['Offsets'][15], row['Slopes'][0], row['Slopes'][1], row['Slopes'][2], row['Slopes'][3], row['Slopes'][4], row['Slopes'][5], row['Slopes'][6], row['Slopes'][7], row['Slopes'][8], row['Slopes'][9], row['Slopes'][10], row['Slopes'][11], row['Slopes'][12], row['Slopes'][13], row['Slopes'][14], row['Slopes'][15]

  return ;

if __name__ == '__main__':
  # load lmap HB, HE, HF, HO
  df_HBsublmap, df_HEsublmap, df_HFsublmap, df_HOsublmap, df_HBsubclmap, df_HEsubclmap, df_HFsubclmap = GetLMapDataFrame( 'sqlite:///../officialMap/HCALLogicalMap.db' )
  #print (df_HBsublmap.head())
  #print (df_HEsublmap.head())
  #print (df_HFsublmap.head())
  #print (df_HOsublmap.head())
  #print (df_HBsubclmap.head())
  #print (df_HEsubclmap.head())
  #print (df_HFsubclmap.head())

  # load qie8 tables offsets and slopes
  #df_qie8_offset_pv, df_qie8_slope_pv = GetQIE8DataFrame( 'sqlite:///qie8_database/QIE8ConstantFNALNormal_DropFcs.db' )
  df_qie8_offset_pv, df_qie8_slope_pv = GetQIE8DataFrame( 'sqlite:////eos/user/h/hua/QIEDB/qie8_database/QIE8ConstantFNALNormal_DropFcs.db' )
  #print (df_qie8_offset_pv.head())
  #print (df_qie8_slope_pv.head())
  
  # load qie10 tables offsets and slopes
  #df_qie10_offset_pv, df_qie10_slope_pv = GetQIE10DataFrame( 'sqlite:///qie10_database/qieCalibrationParameters_HF_2017-04-24.db' )
  df_qie10_offset_pv, df_qie10_slope_pv = GetQIE10DataFrame( 'sqlite:////eos/user/h/hua/QIEDB/qie10_database/qieCalibrationParameters_HF_2017-04-24.db' )
  #print (df_qie10_offset_pv.head())
  #print (df_qie10_slope_pv.head())

  # load qie11 tables offsets and slopes
  df_qie11_offset_pv, df_qie11_slope_pv = GetQIE11DataFrame( 'sqlite:////eos/user/h/hua/QIEDB/qie11_database/HE_all640cards_parameters.db', "shunt=1 AND Gsel=0" )
  #df_qie11_offset_pv, df_qie11_slope_pv = GetQIE11DataFrame( 'sqlite:////eos/user/h/hua/QIEDB/qie11_database/HE_all640cards_parameters.db', "shunt=6 AND Gsel=18" )
  #print (df_qie11_offset_pv.head())
  #print (df_qie11_slope_pv.head())

  DumpHBQIE8Table( df_HBsublmap, df_qie8_offset_pv, df_qie8_slope_pv )
  DumpHEQIE11Table( df_HEsublmap, df_qie11_offset_pv, df_qie11_slope_pv )
  DumpHFQIE10Table( df_HFsublmap, df_qie10_offset_pv, df_qie10_slope_pv )
  DumpHOQIE8Table( df_HOsublmap, df_qie8_offset_pv, df_qie8_slope_pv )
  #DumpHBQIE8Table( df_HBsubclmap, df_qie8_offset_pv, df_qie8_slope_pv )
  #DumpHEQIE11Table( df_HEsubclmap, df_qie11_offset_pv, df_qie11_slope_pv )
  #DumpHFQIE10Table( df_HFsubclmap, df_qie10_offset_pv, df_qie10_slope_pv )
