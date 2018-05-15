# -*- coding: utf-8 -*-
"""
Created on Sun May 13 22:32:34 2018

@author: stef_leonA
the environment for the multi-robot coverage motion planning 

"""
import plotly.plotly as py
import plotly.graph_objs as go
import plotly
from read_cfg import Read_Cfg
import copy
#import Read_Cfg from read_cfg.py
#import read_cfg
from IPython.display import Image

#py.sign_in('tesla_fox', 'HOTRQ3nIOdYUUszDIfgN')


class Pnt:
    def __init__(self,x=0,y=0):
        self.x = x
        self.y = y
    def pnt2dict(self):
        dic = dict(x = x,y= y)
        return dic
class Circle:
    def __init__(self,pnt = Pnt(),rad = 0):
        self.x = pnt.x
        self.y = pnt.y
        self.rad = rad
        self.x0 = self.x  - self.rad
        self.y0 = self.y  - self.rad
        self.x1 = self.x  + self.rad
        self.y1 = self.y  + self.rad
    def circle2dict(self):
        dic = dict()
        dic['type'] = 'circle'
        dic['xref'] = 'x'
        dic['yref'] = 'y'
        dic['x0'] = self.x0
        dic['y0'] = self.y0
        dic['x1'] = self.x1
        dic['y1'] = self.y1        
        dic['line'] = dict(color = 'rgba(50, 171, 96, 1)')
        return dic

class Line:
    def __init__(self,pnt0 =Pnt(),pnt1=Pnt()):
        self.x0 = pnt0.x
        self.y0 = pnt0.y
        self.x1 = pnt1.x
        self.y1 = pnt1.y
    def line2dict(self):
        dic= dict()
        dic['type']='line'
        dic['x0'] =self.x0
        dic['y0'] =self.y0
        dic['x1'] =self.x1
        dic['y1'] =self.y1
        dic['line'] = dict(color = 'rgb(128, 0, 128)')
        return dic

    
        
        
class Env:
    def __init__(self):
        self.range_x = list()
        self.range_y = list()
        self.grid_x = list()
        self.grid_y = list()
        self.svd = list()
        self.tvd = list()
        self.gridStep = 0
    #画图函数
    def drawFunc(self):
        rangeTrace = go.Scatter(x = self.range_x,
                                y = self.range_y,
                                mode= 'lines+markers',
                                name = 'range',
                                line = dict(shape ='v'))
        layout = dict(title = 'coverage motion planning')
        data = []
        data.append(rangeTrace)
        fig = dict(data = data ,layout = layout)
        plotly.offline.plot(fig,filename = 'environment')
    def drawGrid(self):
        rangeTrace = go.Scatter(x = self.range_x,
                                y = self.range_y,
                                mode= 'lines+markers',
                                name = 'range',
                                line = dict(shape ='v'))
        layout = dict(title = 'coverage motion planning')
        shapeLst = list()
        print(self.gridStep)
        for i in range(len(self.grid_x)):
            pnt = Pnt(self.grid_x[i],self.grid_y[i])
            circ = Circle(pnt,self.gridStep/2)
            circDic = circ.circle2dict()
            shapeLst.append(copy.deepcopy(circDic))
        for i in range(len(self.svd)):
            pnt0 = Pnt(self.grid_x[svd[i]],self.grid_y[svd[i]])
            pnt1 = Pnt(self.grid_x[tvd[i]],self.grid_y[tvd[i]])
            line = Line(pnt0,pnt1)
            lineDic = line.line2dict()
            shapeLst.append(copy.deepcopy(lineDic))
#        print(shapeLst)
        layout['shapes'] = shapeLst
        layout['xaxis'] = {'range':[0,self.range_x]}
        layout['yaxis'] = {'range':[0,self.range_y]}
        layout['autosize'] = False
        layout['height'] = 800
        layout['width']= 800
#        print(layout)
        data = []
        data.append(rangeTrace)
        fig = dict(data = data ,layout = layout)
        plotly.offline.plot(fig,filename = 'environment.png')
#        py.image.save_as(fig,filename ='env.jpeg')
        Image('./env.png')
        print('draw success')


    
if __name__ == '__main__':
    
    conFileDir = './/data//'    
    degNameCfg = conFileDir + 'map_debug.txt'
    readCfg = Read_Cfg(degNameCfg)
    lstx = []
    lsty = []
    gridStep = 3
    grid_x = list()
    grid_y = list()
    svd = []
    tvd = []
    readMark = readCfg.get('range_x',lstx)
    readMark = readCfg.get('range_y',lsty)
    readMark = readCfg.get('grid_x',grid_x)
    readMark = readCfg.get('grid_y',grid_y)
    readCfg.get('svd',svd)
    readCfg.get('tvd',tvd)
    for i  in range(len(svd)):
        svd[i] = int(svd[i])
        tvd[i] = int(tvd[i])
    readCfg.getSingleVal('gridStep',gridStep)
    env = Env()
    env.range_x = lstx
    env.range_y = lsty
    env.grid_x = grid_x
    env.grid_y = grid_y
    env.svd = svd
    env.tvd = tvd
    env.gridStep = gridStep
    env.drawGrid()
#
#    env.drawFunc()


