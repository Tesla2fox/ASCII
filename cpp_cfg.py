# -*- coding: utf-8 -*-
"""
Created on Sat May 12 20:47:33 2018

@author: robot

用于生成C++的cfg
CPP 指代coverage path planning 
"""
import time 
import datetime 


class CPP_Cfg:
    def __init__(self):
        self.range_x = []
        self.range_y = []
    

class Read_Cfg:
    def __init__(self,fileName = '0-0'):
        self.fileName = fileName
    


if __name__ == '__main__':
    cpp_cfg = CPP_Cfg()
    cpp_cfg.range_x = [0,100,100,0]
    cpp_cfg.range_y = [0,0,100,100]
    
    conFileDir = 'D://py_code//coverageMotionPlanning//data//'
    conFileCfg = conFileDir + 'CPP_Cfg.txt'
    f_con = open(conFileCfg , 'w')
    
    #write time 
    f_con.write('time '+ datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")+'\n')
    
    f_con.write('range_x ')
    for pntx in cpp_cfg.range_x:
        f_con.write(' '+ str(pntx))
    f_con.write('\n')

    f_con.write('range_y ')
    for pnty in cpp_cfg.range_y:
        f_con.write(' '+ str(pnty))
    f_con.write('\n')
    
    f_con.close()
    
    
    degNameCfg = conFileDir + 'map_debug.txt'
    
    
    
