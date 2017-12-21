import pandas as pd


if __name__ == '__main__':
  fn = r'HCALmapCALIB_J.xls'
  df = pd.read_excel(fn, sheetname = 'RBX')
  df.head()
