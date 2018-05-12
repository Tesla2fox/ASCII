import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from numpy import sin, cos, pi, array

spring_constant = 22.93
length = 0.16
mass = 0.1

# initial conditions
init = array([-0.35, 0, 0.08, 1]) # initial values
      #array([theta, theta_dot, x, x_dot])

#Return derivatives of the array z (= [theta, theta_dot, x, x_dot])
def deriv(z, t, spring_k, spring_l, bob_mass):
    k = spring_k
    l = spring_l
    m = bob_mass
    g = 9.8

    theta = z[0]
    thetadot = z[1]
    x = z[2]
    xdot= z[3]

    return array([
        thetadot,
        (-1.0/(l+x)) * (2*xdot*thetadot + g*sin(theta)),
        xdot,
        g*cos(theta) + (l+x)*thetadot**2 - (k/m)*x
        ])

#Create time steps
time = np.linspace(0.0,10.0,1000)

#Numerically solve ODE
y = odeint(deriv,init,time, args = (spring_constant, length, mass))

l = length
r = l+y[:,2]
theta = y[:,0]
dt = np.mean(np.diff(time))

x = r*sin(theta)
y = -r*cos(theta)

##MATPLOTLIB BEGINS HERE##

fig = plt.figure()
ax = fig.add_subplot(111, autoscale_on=False, 
                     xlim=(-1.2*r.max(), 1.2*r.max()),
                     ylim=(-1.2*r.max(), 0.2*r.max()), aspect = 1.0)
ax.grid()

##ANIMATION STUFF BEGINS HERE##

line, = ax.plot([], [], 'o-', lw=2)

time_template = 'time = %.1fs'
time_text = ax.text(0.05, 0.9, '', transform=ax.transAxes)
foox = []
fooy = []
#foo.set_data(foox, fooy)

def init():
    global line, time_text, foo
    line.set_data([], [])
#    foo.set_data([], [])
    time_text.set_text('')
    return line, time_text#, foo


def animate(i):
    global foox, fooy, foo
    thisx = [0, x[i]]
    thisy = [0, y[i]]

    foox += [x[i]]
    fooy += [y[i]]

    line.set_data(thisx, thisy)
#    foo.set_data(foox, fooy)

    time_text.set_text(time_template%(i*dt))
    return line, time_text#, foo

ani = animation.FuncAnimation(fig, animate, np.arange(1, len(y)), interval=25, blit=False, init_func=init)

plt.show()
