import matplotlib.pyplot as plt
import numpy as np

def A(DT,i):
  Ts = DT['threads_m'][0]
  Tp = DT['threads_m'][i]
  return Ts/Tp

def E(DT, i):
  A = DT['aceleração'][i]
  t = 2**(i)
  return A/t

M500s_l =[0.679299, 0.718882, 0.757055, 0.712927, 0.795790]
M500t1_l = [0.730276, 0.730445, 0.719253, 0.722729, 0.911397]
M500t2_l = [0.443184, 0.419970, 0.457717, 0.395456, 0.402272]
M500t4_l = [0.438601, 0.418227, 0.418261, 0.400451, 0.400681]
M500t8_l = [0.429232, 0.385304, 0.416196, 0.424079, 0.447032]

M1000s_l = [6.369062, 6.525792, 7.161359, 7.638183, 7.543744]
M1000t1_l = [8.318525, 8.039345, 8.269777, 7.277340, 8.032766]
M1000t2_l = [5.267622, 4.972886, 4.317848, 4.564907, 4.536984]
M1000t4_l = [4.592816, 4.561978, 4.531782, 4.225520, 4.169093]
M1000t8_l = [4.341455, 5.123018, 4.573634, 3.962724, 3.928329]

M2000s_l = [69.756304, 79.520777, 71.530944, 72.513943, 69.466103]
M2000t1_l = [75.905939, 71.125921, 70.138531, 77.632125, 73.778856]
M2000t2_l = [40.183237, 41.381905, 41.422754, 44.082957, 49.109937]
M2000t4_l = [43.132005, 49.719843, 52.782737, 46.681921, 40.956210]
M2000t8_l = [43.154260, 43.415114, 40.384507, 41.338869, 40.756742]

DT500 = {'threads_m' : [np.mean(M500s_l), np.mean(M500t1_l), np.mean(M500t2_l), np.mean(M500t4_l), np.mean(M500t8_l)],
         'threads_l' : [M500s_l, M500t1_l, M500t2_l, M500t4_l, M500t8_l]}

DT1000 = {'threads_m' : [np.mean(M1000s_l), np.mean(M1000t1_l), np.mean(M1000t2_l), np.mean(M1000t4_l), np.mean(M1000t8_l)],
         'threads_l' : [M1000s_l, M1000t1_l, M1000t2_l, M1000t4_l, M1000t8_l]}

DT2000 = {'threads_m' : [np.mean(M2000s_l), np.mean(M2000t1_l), np.mean(M2000t2_l), np.mean(M2000t4_l), np.mean(M2000t8_l)],
         'threads_l' : [M2000s_l, M2000t1_l, M2000t2_l, M2000t4_l, M2000t8_l]}

DT500['aceleração'] = [A(DT500, j) for j in range(1,5)]
DT1000['aceleração'] = [A(DT1000, j) for j in range(1,5)]
DT2000['aceleração'] = [A(DT2000, j) for j in range(1,5)]

DT500['eficiência'] = [E(DT500, j) for j in range(4)]
DT1000['eficiência'] = [E(DT1000, j) for j in range(4)]
DT2000['eficiência'] = [E(DT2000, j) for j in range(4)]

nthreads = [1, 2, 4, 8]

#Gráficos:

"Tempo por número de threads"

fig = plt.figure(figsize=(15, 5))

plt.subplot(1,3,1)
plt.plot(nthreads, DT500['threads_m'][1:], label = "threads")
plt.plot(nthreads, [DT500['threads_m'][0]]*4, label = "sequencial")
plt.legend()
plt.title("Matriz 500x500")

plt.subplot(1,3,2)
plt.plot(nthreads, DT1000['threads_m'][1:], label = "threads")
plt.plot(nthreads, [DT1000['threads_m'][0]]*4, label = "sequencial")
plt.legend()
plt.title("Matriz 1000x1000")

plt.subplot(1,3,3)
plt.plot(nthreads, DT2000['threads_m'][1:], label = "threads")
plt.plot(nthreads, [DT2000['threads_m'][0]]*4, label = "sequencial")
plt.legend()
plt.title("Matriz 2000x2000")

plt.suptitle("Tempo por Nº de threads")
plt.show()

"Aceleração por número de threads"

fig = plt.figure(figsize=(15, 5))

plt.subplot(1,3,1)
plt.plot(nthreads, DT500['aceleração'], label = "aceleração")
plt.legend()
plt.title("Matriz 500x500")

plt.subplot(1,3,2)
plt.plot(nthreads, DT1000['aceleração'], label = "aceleração")
plt.legend()
plt.title("Matriz 1000x1000")

plt.subplot(1,3,3)
plt.plot(nthreads, DT2000['aceleração'], label = "aceleração")
plt.legend()
plt.title("Matriz 2000x2000")

plt.suptitle("Aceleração por Nº de threads")
plt.show()

"Eficiência por número de threads"

fig = plt.figure(figsize=(15, 5))

plt.subplot(1,3,1)
plt.plot(nthreads, DT500['eficiência'], label = "eficiência")
plt.legend()
plt.title("Matriz 500x500")

plt.subplot(1,3,2)
plt.plot(nthreads, DT1000['eficiência'], label = "eficiência")
plt.legend()
plt.title("Matriz 1000x1000")

plt.subplot(1,3,3)
plt.plot(nthreads, DT2000['eficiência'], label = "eficiência")
plt.legend()
plt.title("Matriz 2000x2000")

plt.suptitle("Eficiência por Nº de threads")
plt.show()
