import sys
import sqlite3
import plotly.plotly as plt
import plotly.figure_factory as ff

def ValidationPlot_HBHE_FEC(subdet,var):
  conn = sqlite3.connect('../officialMap/HCALLogicalMap.db')
  c = conn.cursor()
  print "Opened database successfully";

  xlist = []
  ylist = []
  zlist = []

  rbx_hbp = ['HBP01','HBP02','HBP03','HBP04','HBP05','HBP06','HBP07','HBP08','HBP09','HBP10','HBP11','HBP12','HBP13','HBP14','HBP15','HBP16','HBP17','HBP18']
  rbx_hbm = ['HBM01','HBM02','HBM03','HBM04','HBM05','HBM06','HBM07','HBM08','HBM09','HBM10','HBM11','HBM12','HBM13','HBM14','HBM15','HBM16','HBM17','HBM18']
  rbx_hep = ['HEP01','HEP02','HEP03','HEP04','HEP05','HEP06','HEP07','HEP08','HEP09','HEP10','HEP11','HEP12','HEP13','HEP14','HEP15','HEP16','HEP17','HEP18']
  rbx_hem = ['HEM01','HEM02','HEM03','HEM04','HEM05','HEM06','HEM07','HEM08','HEM09','HEM10','HEM11','HEM12','HEM13','HEM14','HEM15','HEM16','HEM17','HEM18']

  if subdet in ('HBP','ngHBP'):
    rbx=rbx_hbp
  elif subdet in ('HBM','ngHBM'):
    rbx=rbx_hbm
  elif subdet in ('ngHEP'):
    rbx=rbx_hep
  elif subdet in ('ngHEM'):
    rbx=rbx_hem
  
  rm =[1,2,3,4]

  for thisrbx in rbx:
    for thisrm in rm:
      ylist.append(thisrbx+'RM'+str(thisrm))
      if subdet in ('HBP','HBM'):
        cursor = c.execute("SELECT RBX, RM, RM_FI, FI_CH, Crate, uHTR, uHTR_FI, Side, Eta, Phi, Depth from HBLogicalMap where RBX=? AND RM=? ORDER BY RM_FI,FI_CH", (thisrbx,thisrm))
      elif subdet in ('ngHBP','ngHBM'):
        cursor = c.execute("SELECT ngRBX, RM, RM_FI, FI_CH, Crate, uHTR, uHTR_FI, Side, Eta, Phi, Depth from ngHBLogicalMap where ngRBX=? AND RM=? ORDER BY RM_FI,FI_CH", (thisrbx,thisrm))
      elif subdet in ('ngHEP','ngHEM'):
        cursor = c.execute("SELECT ngRBX, RM, RM_FI, FI_CH, Crate, uHTR, uHTR_FI, Side, Eta, Phi, Depth from ngHELogicalMap where ngRBX=? AND RM=? ORDER BY RM_FI,FI_CH", (thisrbx,thisrm))

      zlistrbxrm=[]
      for row in cursor:
        if(len(ylist)==1):
          xlist.append('RMFI'+str(row[2])+'FICH'+str(row[3]))
        
        if var=='Crate':
          zlistrbxrm.append(row[4])
        elif var=='uHTR':
          zlistrbxrm.append(row[5])
        elif var=='uHTR_FI':
          zlistrbxrm.append(row[6])
        elif var=='Eta': 
          zlistrbxrm.append(row[7]*row[8])
        elif var=='Phi':
          zlistrbxrm.append(row[9])
        elif var=='Depth': 
          zlistrbxrm.append(row[10])
      zlist.append(zlistrbxrm)
  print "Operation done successfully";
  conn.close()

  #fig = ff.create_annotated_heatmap(zlist, x=xlist, y=ylist, annotation_text=z_text, colorscale='Viridis')
  fig = ff.create_annotated_heatmap(zlist, x=xlist, y=ylist, colorscale='Viridis')
  fig['layout']['xaxis'].update(side='bottom')
  fig['layout'].update(height=1500, width=1500, title=subdet+' '+var+' in FrontEnd coordiantes')
  plt.plot(fig, filename=subdet+'_'+var+'_in_FrontEnd')

def main():
  ValidationPlot_HBHE_FEC(sys.argv[1],sys.argv[2])
  #for arg in sys.argv[1:]:
  #  print arg

if __name__ == "__main__":
  main()
