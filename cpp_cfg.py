# -*- coding: utf-8 -*-
"""
Created on Sat May 12 20:47:33 2018

@author: robot

用于生成C++的cfg
CPP 指代coverage path planning 
"""
import time 
import datetime
import random
from random import randint 


class CPP_Cfg:
    def __init__(self):
        self.range_x = []
        self.range_y = []
    

if __name__ == '__main__':
    cpp_cfg = CPP_Cfg()
    cpp_cfg.range_x = [0,315,315,0]
    cpp_cfg.range_y = [0,0,315,315]
    max_range_x = max(cpp_cfg.range_x)
    max_range_y = max(cpp_cfg.range_y)

    start_x = [20,200,150,10,310]
    start_y = [0,30,170,310,300]

    
    conFileDir = './/data//'
    conFileCfg = conFileDir + 'CPP_Cfg_1.txt'
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
    
    
    gridStep = 10
    f_con.write('gridStep '+str(gridStep)+'\n')
    
    f_con.write('start_x ')
    for pntx in start_x:
        f_con.write(' '+ str(pntx))
    f_con.write('\n')

    f_con.write('start_y ')
    for pnty in start_y:
        f_con.write(' '+ str(pnty))
    f_con.write('\n')
        
    ob_x = []
    ob_y = []
    for i in range(30):
        ob_x.append(randint(0,max_range_x))
        ob_y.append(randint(0,max_range_y))
    
    for i in range(0,130,10):
        ob_x.append(i)
        ob_y.append(140)
    
    for i in range(140,310,10):
        ob_x.append(130)
        ob_y.append(i)
    
    
    f_con.write('obPnt_x ')
    for pnty in ob_x:
        f_con.write(' '+ str(pnty))
    f_con.write('\n')
        

    f_con.write('obPnt_y ')
    for pnty in ob_y:
        f_con.write(' '+ str(pnty))
    f_con.write('\n')
        
    
    f_con.close()
       
    
    
