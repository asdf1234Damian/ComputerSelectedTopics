import matplotlib.pyplot as plt
import csv

x = []
y = []

with open('PromediosPy1.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(int(row[0]))
        y.append(int(row[1]))

plt.plot(x,y, label='Promedio de 1s')
plt.xlabel('Gen')
plt.ylabel('1s')
plt.title('Tamaño 500x500\n')
plt.legend()
plt.show()
