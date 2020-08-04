import matplotlib
import matplotlib.pyplot as plt
import numpy as np
theory_data = open("result/theory_pressure.dat")
t_p = []
for value in theory_data:
    t_p.append(float(value))
analyze_data = open("result/pressure.dat")
a_p=[]
for value in analyze_data:
    a_p.append(float(value))
analyze_pressure = analyze_data.readlines()
x_data = open("result/x_coordinator.dat")
x = []
for value in x_data:
    x.append(float(value))

plt.plot(x,t_p, label='theory')
plt.plot(x, a_p, label='analyze')
plt.xlabel('x [-]')
plt.ylabel('Φ [-]')
plt.yticks
plt.legend()
plt.savefig('data_1.PNG')