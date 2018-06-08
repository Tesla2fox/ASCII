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
import math
from random import randint 


class CPP_Cfg:
    def __init__(self):
        self.range_x = []
        self.range_y = []
    

random.seed(10)

if __name__ == '__main__':
    cpp_cfg = CPP_Cfg()
    cpp_cfg.range_x = [0,1005,1005,0]
    cpp_cfg.range_y = [0,0,1005,1005]
    max_range_x = max(cpp_cfg.range_x)
    max_range_y = max(cpp_cfg.range_y)

    max_range_x_grid = math.floor(max_range_x/20)
    max_range_y_grid = math.floor(max_range_y/20)
    
    print(max_range_x_grid)
    print(max_range_y_grid)
    robNum = 80
    start_x = []
    start_y = []

    s_0 = []
    s_1 = []

#    for i in range(21):
#        start_x.append(200+i*20)
#        start_y.append(450)
#
#    for i in range(len(start_x)):
#        s_ind0  = math.floor((start_x[i]+5)/20)
#        s_ind1  = math.floor((start_y[i]+5)/20)
#        s_0.append(s_ind0)
#        s_1.append(s_ind1)
#        
#    for i in range(10):
#        start_x.append(800)
#        start_y.append(300+i*20)
        
    while  len(start_x)<robNum:
        u_sx = randint(0,max_range_x_grid*2-1)*10
        u_sy = randint(0,max_range_y_grid*2-1)*10
        s_ind0  = math.floor((u_sx)/20)
        s_ind1  = math.floor((u_sy)/20)
#        print(ob_ind0,ob_ind1)
        reasonable = True
        for i in range(len(s_0)):
            if((s_0[i] == s_ind0)and(s_1[i] == s_ind1)):
                reasonable = False
                print('wwwwwwwwww')
                break
        if reasonable:
            start_x.append(u_sx)
            start_y.append(u_sy)
            s_0.append(s_ind0)
            s_1.append(s_ind1)
    print(start_x)
    print(start_y)
    print(s_0)
    print(s_1)
        
    
    

#    print(s_0)
#    print(s_1)
        
    conFileDir = './/data//'
    conFileCfg = conFileDir + str(robNum)+'_'+str(max_range_x_grid)+'_'+str(max_range_y_grid)+'_'+str(obNum)+'CPP_Cfg.txt'
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
    
    obNum = -1
    while  len(ob_x)<=obNum:
        u_obx = randint(0,max_range_x-5)
        u_oby = randint(0,max_range_y-5)
        ob_ind0  = math.floor((u_obx+5)/20)
        ob_ind1  = math.floor((u_oby+5)/20)
        print(ob_ind0,ob_ind1)
        reasonable = True
        for i in range(len(s_0)):
            if((s_0[i] == ob_ind0)and(s_1[i] == ob_ind1)):
                reasonable = False
                print('wwwwwwwwww')
                break
        if reasonable:
            ob_x.append(u_obx)
            ob_y.append(u_oby)
    print(len(ob_x))
#    print(ob_y)
    
#            print(u_obx)
#            print(u_oby)
                
    
    
#    for i in range(0,130,10):
#        ob_x.append(i)
#        ob_y.append(140)
#    
#    for i in range(140,310,10):
#        ob_x.append(130)
#        ob_y.append(i)
    
    
    f_con.write('obPnt_x ')
    for pnty in ob_x:
        f_con.write(' '+ str(pnty))
    f_con.write('\n')
        

    f_con.write('obPnt_y ')
    for pnty in ob_y:
        f_con.write(' '+ str(pnty))
    f_con.write('\n')
        
    
    f_con.close()
    

       
    conFileDir = './/data//'
    conFileCfg = conFileDir + '_java_'+str(robNum)+'_'+str(max_range_x_grid)+'_'+str(max_range_y_grid)+'_'+str(obNum)+'CPP_Cfg.txt'
    f_ja = open(conFileCfg , 'w')
    
    for i in range(len(s_0)):
        f_ja.write('EnvironmentGrid['+str(s_0[i])+']['+str(s_1[i])+'] = 2;\n')
    
    for i in range(len(ob_y)):
        s_ind0  = math.floor((ob_x[i]+5)/20)
        s_ind1  = math.floor((ob_y[i]+5)/20)
        f_ja.write('EnvironmentGrid['+str(s_ind0)+']['+str(s_ind1)+'] = 1;\n')
        
    f_ja.close()
    
    
