# -*- coding: utf-8 -*-
"""
Created on Sat May 12 20:47:33 2018

@author: robot

类似于C++中的sscfg  可以将指定名字的变量放到list中
CPP 指代coverage path planning 
"""
    

class Read_Cfg:
    def __init__(self,fileName = '0-0'):
        self.fileName = fileName
    def get(self, str_val ='val' ,ListVal = []):
        ListVal.clear()
        getBoolean = False
        with open(self.fileName)  as txtData:
           lines = txtData.readlines()
           for line in lines:
               lineData = line.split()
               if(len(lineData)==0):
                   continue
               else:
                   if(lineData[0]==str_val):
                       
                       for i in range(1,len(lineData)):
                           ListVal.append(float(lineData[i]))
                       getBoolean = True
                       break
                   else:
                       continue
        return getBoolean

if __name__ == '__main__':
    
    conFileDir = './/data//'    
    degNameCfg = conFileDir + 'map_debug.txt'
    readCfg = Read_Cfg(degNameCfg)
    lista = []
    readMark = readCfg.get('range_y',lista)
    print(lista)
    if(readCfg.get('range_x'),lista):
        print('success')
    else:
        print('failed')
    
    
