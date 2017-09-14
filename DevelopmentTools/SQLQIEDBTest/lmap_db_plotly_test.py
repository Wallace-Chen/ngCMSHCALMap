import sqlite3
import plotly.plotly as plt
import plotly.figure_factory as ff

conn = sqlite3.connect('../officialMap/HCALLogicalMap.db')
c = conn.cursor()
print "Opened database successfully";

xlist = []
ylist = []
zlist = []

#tablename = 'ngHBLogicalMap'
rbx = ['HBP01','HBP02','HBP03','HBP04','HBP05','HBP06','HBP07','HBP08','HBP09','HBP10','HBP11','HBP12','HBP13','HBP14','HBP15','HBP16','HBP17','HBP18']
#rbx = ['HBM01','HBM02','HBM03','HBM04','HBM05','HBM06','HBM07','HBM08','HBM09','HBM10','HBM11','HBM12','HBM13','HBM14','HBM15','HBM16','HBM17','HBM18']
#rbx = ['HEP01','HEP02','HEP03','HEP04','HEP05','HEP06','HEP07','HEP08','HEP09','HEP10','HEP11','HEP12','HEP13','HEP14','HEP15','HEP16','HEP17','HEP18']
#rbx = ['HEM01','HEM02','HEM03','HEM04','HEM05','HEM06','HEM07','HEM08','HEM09','HEM10','HEM11','HEM12','HEM13','HEM14','HEM15','HEM16','HEM17','HEM18']

rm =[1,2,3,4]
for thisrbx in rbx:
  for thisrm in rm:
    ylist.append(thisrbx+'RM'+str(thisrm))
    #cursor = c.execute("SELECT Side, Eta, ngRBX, RM, RM_FI, FI_CH from ngHBLogicalMap where ngRBX=? AND RM=? ORDER BY RM_FI,FI_CH", (thisrbx,thisrm))
    #cursor = c.execute("SELECT Crate, uHTR, ngRBX, RM, RM_FI, FI_CH from ngHELogicalMap where ngRBX=? AND RM=? ORDER BY RM_FI,FI_CH", (thisrbx,thisrm))
    cursor = c.execute("SELECT Crate, uHTR, RBX, RM, RM_FI, FI_CH from HBLogicalMap where RBX=? AND RM=? ORDER BY RM_FI,FI_CH", (thisrbx,thisrm))

    zlistrbxrm=[]
    for row in cursor:
      if(len(ylist)==1):
        xlist.append('RMFI'+str(row[4])+'FICH'+str(row[5]))
      #zlistrbxrm.append(row[0])
      zlistrbxrm.append(row[1])
      #print "Side = ", row[0]
      #print "Eta = ", row[1]
      #print "RBX = ", row[2]
      #print "RM = ", row[3]
      #print "RM_FI = ", row[4]
      #print "FI_CH = ", row[5], "\n"
    zlist.append(zlistrbxrm)
print xlist
print ylist
print zlist
print "Operation done successfully";
conn.close()

#fig = ff.create_annotated_heatmap(zlist, x=xlist, y=ylist, annotation_text=z_text, colorscale='Viridis')
fig = ff.create_annotated_heatmap(zlist, x=xlist, y=ylist, colorscale='Viridis')
fig['layout']['xaxis'].update(side='bottom')
fig['layout'].update(height=1500, width=1500, title='HBP uHTR in FrontEnd coordiantes')
plt.plot(fig, filename='HBP_uHTR_in_FrontEnd')
