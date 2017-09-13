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
#rbx = ['HBP01','HBP02','HBP03','HBP04','HBP05','HBP06','HBP07','HBP08','HBP09','HBP10','HBP11','HBP12','HBP13','HBP14','HBP15','HBP16','HBP17','HBP18']
rbx = ['HBM01','HBM02','HBM03','HBM04','HBM05','HBM06','HBM07','HBM08','HBM09','HBM10','HBM11','HBM12','HBM13','HBM14','HBM15','HBM16','HBM17','HBM18']
rm =[1,2,3,4]
for thisrbx in rbx:
  for thisrm in rm:
    ylist.append(thisrbx+'RM'+str(thisrm))
    cursor = c.execute("SELECT Side, Eta, ngRBX, RM, RM_FI, FI_CH from ngHBLogicalMap where ngRBX=? AND RM=? ORDER BY RM_FI,FI_CH", (thisrbx,thisrm))
    zlistrbxrm=[]
    for row in cursor:
      if(len(ylist)==1):
        xlist.append('RMFI'+str(row[4])+'FICH'+str(row[5]))
      zlistrbxrm.append(row[0]*row[1])
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
fig['layout'].update(height=1500, width=1500, title='ngHBM Eta in FrontEnd coordiantes')
plt.plot(fig, filename='annotated_heatmap_text')
