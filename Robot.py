# -*- coding: utf-8 -*-
"""
Created on Fri May 11 16:20:17 2018
"
drawTrajectory 
"

@author: robot
"""
import random
import math 

class Point2D:
    def __init__(self,x = 0,y = 0,range_x = 50,range_y = 50):
        self.x = x
        self.y = y
        self.range_x = range_x
        self.range_y = range_y 
    def displayPoint2D(self):
        print("x= ",self.x,"y = ",self.y)
    def randomPosition(self):
        self.x= random.uniform(0,self.range_x)
        self.y = random.uniform(0,self.range_y)



class PointDir:
    def __init__(self,x = 0,y = 0,w = 0,range_x = 50,range_y = 50):
        self.x = x
        self.y = y
        self.w = w
        self.range_x = range_x
        self.range_y = range_y 
    def displayPoint2D(self):
        print("x= ",self.x,"y = ",self.y,
              "w = ",self.w)
    def randomPosition(self):
        self.x= random.uniform(0,self.range_x)
        self.y = random.uniform(0,self.range_y)
        self.w  = random.uniform(0,math.pi*2)

"""
机器人目前还不可以是异构的
"""
class Robot:
    def __init__(self,pnt = PointDir() ,vel =1):
        self.pnt = pnt
        self.p
    def random(self):
        self.pnt.randomPosition()
    def printRobot(self):
        self.pnt.displayPoint2D()
    def 

        
        
        
if __name__ =="__main__":
    rob = Robot()
    rob.printRobot()
    rob.random()
    rob.printRobot() 
    

    
            
