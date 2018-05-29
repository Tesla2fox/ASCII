# -*- coding: utf-8 -*-
"""
Created on Fri May 25 15:19:12 2018

@author: robot
"""

import plotly.plotly as py
import plotly.graph_objs as go
import plotly
from read_cfg import Read_Cfg
import copy



py.sign_in('tesla_fox', 'HOTRQ3nIOdYUUszDIfgN')

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
class Rect:
    def __init__(self,pnt =Pnt(),width =0,height =0):
        self.x0 = pnt.x
        self.y0 = pnt.y
        self.x1 = self.x0 + width
        self.y1 = self.y0 + height
    def rect2dict(self):
        dic = dict()
        dic['type']='rect'
        dic['x0'] = self.x0
        dic['y0'] = self.y0
        dic['x1'] = self.x1
        dic['y1'] = self.y1
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
        self.vob = list()
        self.path_x = list()
        self.path_y = list()
        
        
        self.s_grid_x = list()
        self.s_grid_y = list()
        self.s_vob = list()
        self.s_svd = list()
        self.s_tvd = list()
        
        self.tvx_0 = list()
        self.tvy_0 = list()
        self.svx_0 = list()
        self.svy_0 = list()
        
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
    def addline(self):
#        在环境中增加虚线
        return 1
    def drawGrid(self):
        rangeTrace = go.Scatter(x = self.path_x,
                                y = self.path_y,
                                mode= 'lines',
                                name = 'range',
                                line = dict(shape ='spline'))
        
        
#        layout = dict(title = 'coverage motion planning')
        layout = dict()

        shapeLst = list()
        print(self.gridStep)
#        for i in range(len(self.grid_x)):
#            pnt = Pnt(self.grid_x[i] - self.gridStep/2,self.grid_y[i] - self.gridStep/2)
##            circ = Circle(pnt,self.gridStep/2)
##            circDic = circ.circle2dict()
##            if(self.vob[i]==0):
##                circDic['fillcolor'] = 'rgb(55, 128, 191)'
#            rect  = Rect(pnt,self.gridStep,self.gridStep)
#            rectDic = rect.rect2dict()
#            rectDic['line']['dash'] = 'dot'
#            shapeLst.append(copy.deepcopy(rectDic))
        for i in range(len(self.s_grid_x)):
            pnt = Pnt(self.s_grid_x[i] - self.gridStep,self.s_grid_y[i] - self.gridStep)
            rect  = Rect(pnt,self.gridStep*2,self.gridStep*2)
            rectDic = rect.rect2dict()            
            shapeLst.append(copy.deepcopy(rectDic))
            rectDic['line']['color'] = 'rgba(50, 171, 96, 1)'
            rectDic['line']['width'] = 3
            if(self.s_vob[i]==0):
                rectDic['fillcolor'] = 'rgb(152 245 255)'
            shapeLst.append(copy.deepcopy(rectDic))
        
        
        
            
            
#            shapeLst.append(copy.deepcopy(circDic))
#        for i in range(len(self.svd)):
#            pnt0 = Pnt(self.grid_x[svd[i]],self.grid_y[svd[i]])
#            pnt1 = Pnt(self.grid_x[tvd[i]],self.grid_y[tvd[i]])
#            line = Line(pnt0,pnt1)
#            lineDic = line.line2dict()
#            shapeLst.append(copy.deepcopy(lineDic))
#        print(shapeLst)
        layout['shapes'] = shapeLst
        layout['xaxis'] = {'range':[0,self.range_x]}
        layout['yaxis'] = {'range':[0,self.range_y]}
        layout['xaxis'] = dict(
        autorange=True,
        showgrid=False,
        zeroline=False,
        showline=False,
        autotick=True,
        ticks='',
        showticklabels=False)
        layout['yaxis'] = dict(
        autorange=True,
        showgrid=False,
        zeroline=False,
        showline=False,
        autotick=True,
        ticks='',
        showticklabels=False)
        layout['autosize'] = False
        layout['height'] = 1200
        layout['width']= 1000
#        print(layout)
        data = []
        data.append(rangeTrace)
        fig = dict(data = data ,layout = layout)
        plotly.offline.plot(fig,filename = 'environment')
#        py.image.save_as(fig,filename ='env.jpeg')
        Image('./env.png')
        print('draw success')

if __name__ == '__main__':
    conFileDir = './/data//'    
    degNameCfg = conFileDir + 'map_debug.txt'
    readCfg = Read_Cfg(degNameCfg)
    gridStep = 7.5
    grid_x = list()
    grid_y = list()
    svd = []
    tvd = []
    vob = []
    readMark = readCfg.get('range_x',lstx)
    readMark = readCfg.get('range_y',lsty)
    readMark = readCfg.get('grid_x',grid_x)
    readMark = readCfg.get('grid_y',grid_y)
    readCfg.get('obType',vob)
    readCfg.get('svd',svd)
    readCfg.get('tvd',tvd)
    for i  in range(len(svd)):
        svd[i] = int(svd[i])
        tvd[i] = int(tvd[i])
    
    s_grid_x = list()
    s_grid_y = list()
    s_vob = list()
    s_svd = list()
    s_tvd = list()
    
    

    readMark = readCfg.get('s_grid_x',s_grid_x)
    readMark = readCfg.get('s_grid_y',s_grid_y)
    readCfg.get('s_obType',s_vob)
    readCfg.get('s_svd',s_svd)
    readCfg.get('s_tvd',s_tvd)
        
    

    tvx_0 = list()
    tvy_0 = list()
    svx_0 = list()
    svy_0 = list()


    path_x_0 = list()
    path_y_0 = list()

    plNameCfg = conFileDir + 'planDebug.txt'
    plCfg = Read_Cfg(plNameCfg)

    plCfg.get('path_x_0',path_x_0)
    plCfg.get('path_y_0',path_y_0)
    
    plCfg.get('tvx_0',tvx_0)
    plCfg.get('tvy_0',tvy_0)
    plCfg.get('svx_0',svx_0)
    plCfg.get('svy_0',svy_0)
    
    
    env = Env()
    env.range_x = lstx
    env.range_y = lsty
    env.grid_x = grid_x
    env.grid_y = grid_y
    env.svd = svd
    env.tvd = tvd
    
    env.s_grid_x = s_grid_x
    env.s_grid_y = s_grid_y
    env.s_vob = s_vob
    env.s_svd = s_svd
    env.s_tvd = s_tvd
    
    
    env.path_x = path_x_0
    env.path_y = path_y_0
    
    
    
    
    
    
    
    env.gridStep = gridStep
    env.vob = vob
    print(env.vob)
    env.drawGrid()
#    env.drawFunc()


