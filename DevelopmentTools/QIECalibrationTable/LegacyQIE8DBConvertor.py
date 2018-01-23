from sqlalchemy import create_engine
import pandas as pd
import os

if __name__ == '__main__':
  sql_engine = create_engine('sqlite:///afs/cern.ch/user/h/hua/hcal-mapping/Development/CMSSW_8_0_0/src/ngCMSHCALMap/DevelopmentTools/QIECalibrationTable/test.db')
  sql_con = sql_engine.raw_connection()
  #Normal 10001 100327 0 0 0 -0.8283 0.9087 -0.1889 0.9115 2.012 3.1125 4.2129 5.3134 6.4139 7.5143 8.6148 9.7153 10.8157 11.9162 13.0167 14.1172 15.2176 16.3181 18.519 20.72 22.9209 25.1218 27.3228 29.5237 31.7246 35.0261 38.3275 41.6289 44.9303 49.3321 53.734 58.1359 63.6382 69.1406
  col_names = ['Mode', 'Run', 'QIE8ID', 'Ch', 'Cap', 'Rng', 'Offset', 'Slope', 'Fcs00', 'Fcs01', 'Fcs02', 'Fcs03', 'Fcs04', 'Fcs05', 'Fcs06', 'Fcs07', 'Fcs08', 'Fcs09', 'Fcs10', 'Fcs11', 'Fcs12', 'Fcs13', 'Fcs14', 'Fcs15', 'Fcs16', 'Fcs17', 'Fcs18', 'Fcs19', 'Fcs20', 'Fcs21', 'Fcs22', 'Fcs23', 'Fcs24', 'Fcs25', 'Fcs26', 'Fcs27', 'Fcs28', 'Fcs29', 'Fcs30', 'Fcs31']
  df = pd.read_csv('/afs/cern.ch/user/h/hua/hcal-mapping/CMSSW_8_0_0_pre5/src/CalibCalorimetry/HcalAlgos/data/QIE_FNAL_normal.txt', sep=' ', names = col_names)
  print(df.head())
  df.to_sql(name = 'QIE8CalibFNALNormal', con = sql_con, if_exists='append')
