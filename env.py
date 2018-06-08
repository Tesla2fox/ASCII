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
import random


py.sign_in('tesla_fox', 'HOTRQ3nIOdYUUszDIfgN')

class Pnt:
    def __init__(self,x=0,y=0):
        self.x = x
        self.y = y
    def pnt2dict(self):
        dic = dict(x = x,y= y)
        return dic
    def display(self):
        print('x = ',self.x,'y = ',self.y)
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

def frange(start,stop, step=1.0):
    while start < stop:
        yield start
        start +=step
def randColor():
    strcolor = 'rgba('
    strcolor = strcolor + str(random.randint(1,255))+','
    strcolor = strcolor + str(random.randint(1,255))+','
    strcolor = strcolor + str(random.randint(1,255))+',1)'
    return strcolor
        
class Env:
    def __init__(self):
        self.range_x = list()
        self.range_y = list()
        self.grid_x = list()
        self.grid_y = list()
        self.svd = list()
        self.tvd = list()
        self.gridStep = 7.5
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
        
        self.shapeLst = list()
        self.drawData = list()
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
        lineXmax = max(self.s_grid_x)+self.gridStep
        lineYmax = max(self.s_grid_y)+self.gridStep
        lineXmin = min(self.s_grid_x)-self.gridStep
        lineYmin = min(self.s_grid_y)-self.gridStep

        
        for xx in frange(self.s_grid_x[0],max(self.s_grid_x)+1.0,self.gridStep*2):
            pnt0 = Pnt(xx,lineYmin)
            pnt1 = Pnt(xx,lineYmax)
            line = Line(pnt0,pnt1)
            lineDic = line.line2dict()
            lineDic['line']['dash'] = 'dot'
            self.shapeLst.append(copy.deepcopy(lineDic))

        for yy in frange(self.s_grid_y[0],max(self.s_grid_y)+1.0,self.gridStep*2):
            pnt0 = Pnt(lineXmin,yy)
            pnt1 = Pnt(lineXmax,yy)
            line = Line(pnt0,pnt1)
            lineDic = line.line2dict()
            lineDic['line']['dash'] = 'dot'
            self.shapeLst.append(copy.deepcopy(lineDic))
            
        return 1
    def addGraph(self):
        
        mark_x = []
        mark_y = []
        for i in range(len(self.svx_0)):
            pnt0 = Pnt(self.svx_0[i],self.svy_0[i])
            pnt1 = Pnt(self.tvx_0[i],self.tvy_0[i])
            mark_x.append(self.svx_0[i])
            mark_x.append(self.tvx_0[i])
            mark_y.append(self.svy_0[i])
            mark_y.append(self.tvy_0[i])            
            line = Line(pnt0,pnt1)
            lineDic = line.line2dict()
            lineDic['line']['color'] = 'red'
            lineDic['line']['width'] = 3
            self.shapeLst.append(copy.deepcopy(lineDic))
        
        makeTrace = go.Scatter(mode = 'markers',x = mark_x,
                               y = mark_y,
                               marker = dict(
                                       color = 'black',
                                       size = 10)
                               ,name = 'spanning-tree')
        return makeTrace
            
    def addGrid(self,gridType = True):
#        add the basic grid        
        if(gridType):
            lstx = self.grid_x
            lsty = self.grid_y
            vob = self.vob
            gridstep = self.gridStep
            #case 3
            g_color = 'rgba(50, 171, 96, 0.6)'
            #case 1
#            g_color = 'rgba(50, 171, 96, 1)'
        else:
            lstx = self.s_grid_x
            lsty = self.s_grid_y
            vob = self.s_vob
            gridstep = self.gridStep *2
            g_color = 'purple'
        print(gridstep)
        for i in range(len(lstx)):
            pnt = Pnt(lstx[i] - (gridstep/2),lsty[i] - (gridstep/2))
#            pnt.display()
            rect  = Rect(pnt,gridstep,gridstep)
            rectDic = rect.rect2dict()            
            rectDic['line']['color'] = g_color
            rectDic['line']['width'] = 1
            if(vob[i]==0):
                rectDic['fillcolor'] = 'rgba(152 245 255,0.6)'
            self.shapeLst.append(copy.deepcopy(rectDic))
    def addRobotStartPnt(self):
        robotCfg =  './/data//' + 'planDebug.txt'
        robCfg = Read_Cfg(robotCfg)
        lstx = []
        lsty = []
        robCfg.get('start_x',lstx)
        robCfg.get('start_y',lsty)
        for i in range(len(lstx)):
            rangeLst = go.Scatter(x = [lstx[i]],
                                y = [lsty[i]],
                                mode ='markers',
                                marker = dict(symbol = 'cross-dot',
                                              size = 15),
                                name = 'Robot-' + str(i+1))
            self.drawData.append(rangeLst)
    def addSpanningTree(self):
        robotCfg =  './/data//' + 'planDebug.txt'
        robCfg = Read_Cfg(robotCfg)
        lstx = []
        lsty = []
        robCfg.get('start_x',lstx)
        robCfg.get('start_y',lsty)
        robNum = len(lstx)
        for i in range(robNum):
            _tvx = []
            _tvy = []
            _svx = []
            _svy = []
            robCfg.get('tvx_'+str(i),_tvx)
#            print(_tvx)
            robCfg.get('tvy_'+str(i),_tvy)
            robCfg.get('svx_'+str(i),_svx)
            robCfg.get('svy_'+str(i),_svy)
            mark_x = []
            mark_y = []            
            for p in range(len(_tvx)):
                pnt0 = Pnt(_tvx[p],_tvy[p])
                pnt1 = Pnt(_svx[p],_svy[p])
                mark_x.append(_tvx[p])
                mark_x.append(_svx[p])
                mark_y.append(_tvy[p])
                mark_y.append(_svy[p])
                line = Line(pnt0,pnt1)
                lineDic = line.line2dict()
#                print(randColor())
                lineDic['line']['color'] = 'rgba(15,15,15,0.5)'
                lineDic['line']['width'] = 3
                
                self.shapeLst.append(copy.deepcopy(lineDic))
            markTrace = go.Scatter(mode ='markers',
                                   x= mark_x,
                                   y= mark_y,
                                   marker =dict(size =15),
                                   name = 'Spanning-Tree_'+str(i+1))
            self.drawData.append(markTrace)
        return 1
    def addPath(self):
        robotCfg =  './/data//' + 'planDebug.txt'
        robCfg = Read_Cfg(robotCfg)
        lstx = []
        lsty = []
        robCfg.get('start_x',lstx)
        robCfg.get('start_y',lsty)
        robNum = len(lstx)
        for i in range(robNum):
            _path_x = []
            _path_y = []
            robCfg.get('path_x_'+str(i),_path_x)
            robCfg.get('path_y_'+str(i),_path_y)
            pathTrace = go.Scatter(x = _path_x,
                                y = _path_y,
                                mode= 'lines',
                                line = dict(shape = 'spline',
#                                            dash = 'dot',
                                            width = 4),
                                name = 'Path_'+str(i+1))
            self.drawData.append(pathTrace)
        
            
    def drawPic(self,name ='env',fileType = True):
        
        layout = dict()
        layout['shapes'] = self.shapeLst
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
        scaleanchor = "x",
        autorange=True,
        showgrid=False,
        zeroline=False,
        showline=False,
        autotick=True,
        ticks='',
        showticklabels=False)
        layout['font'] = dict(
            family='sans-serif',
            size=25,
            color='#000'
        )
        layout['autosize'] = False
        layout['height'] = 1000
        layout['width']= 1000   
#        print(layout)
        fig = dict(data = self.drawData ,layout = layout)
        if(fileType):
            plotly.offline.plot(fig,filename = name)
        else:
            py.image.save_as(fig,filename = name+'.jpeg')
    

        
 
    def drawGrid(self):
        layout = dict()
        self.shapeLst = list()
        self.addline()
        markTrace   = self.addGraph()
        rangeTrace = go.Scatter(x = self.path_x,
                                y = self.path_y,
                                mode= 'lines',
                                line = dict(shape ='spline'),
                                name = 'path')

        startTrace = go.Scatter(mode = 'markers',x = self.path_x[0:1],
                               y = self.path_y[0:1],
                               marker = dict(
                                       color = 'blue',
                                       size = 15,
                                       symbol = 'x-dot')
                               ,name = 'start')
        terminalTrace = go.Scatter(mode = 'markers',x = self.path_x[-1:],
                               y = self.path_y[-1:],
                               marker = dict(
                                       color = 'red',
                                       size = 15,
                                       symbol = 'cross-dot')
                               ,name = 'terminal'
                               )
#        layout = dict(title = 'coverage motion planning')
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
            rectDic['line']['color'] = 'rgba(50, 171, 96, 1)'
            rectDic['line']['width'] = 3
            if(self.s_vob[i]==0):
                rectDic['fillcolor'] = 'rgba(152 245 255,0.6)'
            self.shapeLst.append(copy.deepcopy(rectDic))
        layout['shapes'] = self.shapeLst
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
        scaleanchor = "x",
        autorange=True,
        showgrid=False,
        zeroline=False,
        showline=False,
        autotick=True,
        ticks='',
        showticklabels=False)
        layout['autosize'] = False
        layout['height'] = 1000
        layout['width']= 1000
#        print(layout)
        data = []
        data.append(rangeTrace)
        data.append(markTrace)
        data.append(startTrace)
        data.append(terminalTrace)
        fig = dict(data = data ,layout = layout)
        plotly.offline.plot(fig,filename = 'multiPlan')
#        py.image.save_as(fig,filename ='stc_demon.jpeg')
        Image('./env.png')
        print('draw success')

if __name__ == '__main__':
    conFileDir = './/data//'    
    degNameCfg = conFileDir + 'map_debug.txt'
    readCfg = Read_Cfg(degNameCfg)
    gridStep = 10
    
    lstx = list()
    lsty = []
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
    
    
    env.tvx_0 = tvx_0
    env.tvy_0 = tvy_0
    env.svx_0 = svx_0
    env.svy_0 = svy_0
    
    
    
    env.gridStep = gridStep
    env.vob = vob
#    case 1
#    env.addGrid()
#    env.addRobotStartPnt()
#    env.drawPic(name = 'c_env',fileType = False)
#     case 2
    env.addGrid()
    env.addSpanningTree()    
    env.drawPic(name = 'c_spanning-tree',fileType = True)
#     case 3
#    env.addGrid()
#    env.addPath()
#    env.addRobotStartPnt()
#    env.drawPic('c_path',fileType = True)

    
#    env.drawGrid()
#    env.drawFunc()


