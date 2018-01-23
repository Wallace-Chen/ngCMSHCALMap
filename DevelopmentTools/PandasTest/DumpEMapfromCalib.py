import pandas as pd


if __name__ == '__main__':
  fn = r'HCALmapCALIB_J.xls'
  df = pd.read_excel(fn, sheetname = 'uHTR')
  #print (df.head())

  print "#i crate slot tb dcc spigot htr_fi fib_ch det eta phi type"
  for index, row in df.iterrows():
    if row['t/b'] == 'top':
      print row['index'], row['crate'], row['HTR'], 't', row['dcc'], row['spigot'], row['htr_fib'], row['fib_ch'], row['det'], row['eta'], row['phi'], row['type']
    elif row['t/b'] == 'bot':
      print row['index'], row['crate'], row['HTR'], 'b', row['dcc'], row['spigot'], row['htr_fib'], row['fib_ch'], row['det'], row['eta'], row['phi'], row['type']
    else:
      print row['index'], row['crate'], row['HTR'], row['t/b'], row['dcc'], row['spigot'], row['htr_fib'], row['fib_ch'], row['det'], row['eta'], row['phi'], row['type']
