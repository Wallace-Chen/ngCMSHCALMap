from sqlalchemy import create_engine
import pandas as pd
import os

if __name__ == '__main__':
  sql_engine_lmap = create_engine('sqlite:///../officialMap/HCALLogicalMap.db')
  sql_con_lmap = sql_engine_lmap.raw_connection()
  df_HBlmap = pd.read_sql("SELECT * FROM HBLogicalMap", con = sql_con_lmap, index_col = ['ID'])
  HBlmaplist = ['Side', 'Eta', 'Phi', 'Depth', 'Det', 'QIEch', 'QIEid']
  df_HBsublmap = df_HBlmap[HBlmaplist]
  #print (df_HBsublmap.head())

  sql_engine_qie8 = create_engine('sqlite:///qie8_database/QIE8ConstantFNALNormal_DropFcs.db')
  sql_con_qie8 = sql_engine_qie8.raw_connection()
  df_qie8 = pd.read_sql("SELECT * FROM QIE8CalibFNALNormal", con = sql_con_qie8, index_col = ['index'])
  df_qie8.drop(['Mode', 'Run'], axis=1, inplace=True)
  #print(df_qie8.head())
  #df_qie8_reformat = df_qie8.pivot(index='QIE8ID', columns='Rng', values = 'Offset')
  df_qie8_offset_pv = pd.pivot_table(df_qie8, index = ['QIE8ID', 'Ch'], columns=['Cap','Rng'], values='Offset')
  df_qie8_slope_pv = pd.pivot_table(df_qie8, index = ['QIE8ID', 'Ch'], columns=['Cap','Rng'], values='Slope')
  #print(df_qie8_offset_pv.head(6))
  #print(df_qie8_slope_pv.head(6))
  #print(df_qie8_offset_pv.iloc[0:6, :].values)
  #print(df_qie8_offset_pv.loc[(100000, 0), :].values)

  df_HBQIE_res = df_HBsublmap[['Side', 'Eta', 'Phi', 'Depth', 'Det']]
  df_HBQIE_res.loc[:,'Eta'] = df_HBQIE_res.Side * df_HBQIE_res.Eta
  df_HBQIE_res.drop(['Side'], axis=1, inplace=True)
  offsets = []
  slopes = []

  for index, row in df_HBsublmap.iterrows():
    thisindex = (row['QIEid'], row['QIEch'])
    if thisindex in df_qie8_offset_pv.index:
      offsets.append(df_qie8_offset_pv.loc[thisindex, :].values)
      slopes.append(df_qie8_slope_pv.loc[thisindex, :].values)
    else:
      offsets.append(df_qie8_offset_pv.loc[(999991, row['QIEch']), :].values)
      slopes.append(df_qie8_slope_pv.loc[(999991, row['QIEch']), :].values)
    #print(offsets)
    #print(slopes)

  df_HBQIE_res['Offsets'] = offsets
  df_HBQIE_res['Slopes'] = slopes
  #print (df_HBQIE_res.tail())
  #df_HBQIE_res.to_csv('test.txt', sep=' ', float_format='%12.5f')

  print('# Eta Phi Depth Det Offsets*16 Slopes*16')
  for index, row in df_HBQIE_res.iterrows():
    print row['Eta'], row['Phi'], row['Depth'], row['Det'], row['Offsets'][0], row['Offsets'][1], row['Offsets'][2], row['Offsets'][3], row['Offsets'][4], row['Offsets'][5], row['Offsets'][6], row['Offsets'][7], row['Offsets'][8], row['Offsets'][9], row['Offsets'][10], row['Offsets'][11], row['Offsets'][12], row['Offsets'][13], row['Offsets'][14], row['Offsets'][15], row['Slopes'][0], row['Slopes'][1], row['Slopes'][2], row['Slopes'][3], row['Slopes'][4], row['Slopes'][5], row['Slopes'][6], row['Slopes'][7], row['Slopes'][8], row['Slopes'][9], row['Slopes'][10], row['Slopes'][11], row['Slopes'][12], row['Slopes'][13], row['Slopes'][14], row['Slopes'][15]
