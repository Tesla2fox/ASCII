#import matplotlib.pyplot as plt
#import numpy as np
#import matplotlib.animation as animation
#
#def main():
#    numframes = 100
#    numpoints = 10
#    color_data = np.random.random((numframes, numpoints))
#    x, y, c = np.random.random((3, numpoints))
#
#    fig = plt.figure()
#    scat = plt.scatter(x, y, c=c, s=100)
#
#    ani = animation.FuncAnimation(fig, update_plot, frames=xrange(numframes),
#                                  fargs=(color_data, scat))
#    plt.show()
#
#def update_plot(i, data, scat):
#    scat.set_array(data[i])
#    return scat,
#
#main()

#import numpy as np
#import matplotlib.pyplot as plt
#import matplotlib.animation as animation
#
#fig, ax = plt.subplots()
#
#g = 9.8                               #value of gravity
#v = 20                                #initial velocity
#theta = 20*np.pi/180                  #initial angle of launch in radians
#tt = 2*v*np.sin(theta)/g              #total time of flight
#t = np.linspace(0, tt, 0.01)          #time of flight into an array
#x = v*np.cos(theta)*t                 #x position as function of time
#line, = ax.plot(x, v*np.sin(theta)*t-(0.5)*g*t**2) #plot of x and y in time
#
#def animate(i):
#    line.set_xdata(v*np.cos(theta)*(t+i/10.0))
#    line.set_ydata(v*np.sin(theta)*(t+i/10.0)-(0.5)*g*(t+i/10.0)**2)  
#    return line,
#
##Init only required for blitting to give a clean slate.
#def init():
#    line.set_xdata(np.ma.array(t, mask=True))
#    line.set_ydata(np.ma.array(t, mask=True))
#    return line,
#
#ani = animation.FuncAnimation(fig, animate, np.arange(1, 200),
#init_func=init, interval=25, blit=True)
#plt.show()


import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

fig, ax = plt.subplots()

g = 9.8                                                        #value of gravity
v = 10.0                                                       #initial velocity
theta = 40.0 * np.pi / 180.0                                   #initial angle of launch in radians
t = 2 * v * np.sin(theta) / g                                  
t = np.arange(0, 0.1, 0.01)                                    #time of flight into an array
x = np.arange(0, 0.1, 0.01)
line, = ax.plot(x, v * np.sin(theta) * x - (0.5) * g * x**2)   # plot of x and y in time

def animate(i):
    """change the divisor of i to get a faster (but less precise) animation """
    print(v * np.cos(theta) * (t + i /100.0))
    line.set_xdata(v * np.cos(theta) * (t + i /100.0))
    line.set_ydata(v * np.sin(theta) * (x + i /100.0) - (0.5) * g * (x + i / 100.0)**2)  
    return line,

plt.axis([0, 15.0, -10.0, 5.0])
ax.set_autoscale_on(True)


ani = animation.FuncAnimation(fig, animate, np.arange(1, 300))
plt.show()