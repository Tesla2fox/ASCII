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
#import Read_Cfg from read_cfg.py
#import read_cfg

py.sign_in('tesla_fox', 'HOTRQ3nIOdYUUszDIfgN')


class Env:
    def __init__(self):
        self.range_x = list()
        self.range_y = list()    
    #画图函数
    def drawFunc(self):
        rangeTrace = go.Scatter(x = self.range_x,
                                y = self.range_y,
                                mode= 'lines+markers',
                                name = lname,
                                line = dict(shape ='v'))
#        layout = dict(title = '操作员 '+str(i)+' 工作负荷示意图',
#                              xaxis = dict(title = '时间'),
#              yaxis = dict(title = '操作员工作负荷'),
#              )
        layout = dict(title = 'coverage motion planning')
        data = []
        data.append(rangeTrace)
        fig = dict(data = data ,layout = layout)
        plotly.offline.plot(fig,filename = 'humStateFig'+str(i) + filePostfix)

    
if __name__ == '__main__':
    
    conFileDir = './/data//'    
    degNameCfg = conFileDir + 'map_debug.txt'
    readCfg = Read_Cfg(degNameCfg)
    lstx = []
    lsty = []
    readMark = readCfg.get('range_x',lstx)
    readMark = readCfg.get('range_y',lsty)
    env = Env()
    env.range_x = lstx
    env.range_y = lsty
    env.drawFunc()


