import scipy.stats as st
from  tkinter  import *
import threading, os, errno, shlex
from subprocess import Popen, PIPE
import matplotlib.pyplot as plt
import csv
import numpy as np
import random as rng
from tkinter.colorchooser import *


class UI:
    def __init__(self):
        self.tk=Tk()
        self.tk.title("Automata")
        self.tk.geometry("200x1000+0+0")

        #Grid size input
        self.sizeLbl=Label(self.tk,text="Size of the grid")
        self.sizeLbl.pack(side=TOP, padx=10, pady=(200,5))
        self.sizeIn=Entry(self.tk,width=10,justify="center")
        self.sizeIn.insert(END,"100")
        self.sizeIn.pack(side=TOP, padx=10, pady=10)


        #Probability
        self.sizeLbl=Label(self.tk,text="Probability")
        self.sizeLbl.pack(side=TOP, padx=10, pady=(10,5))
        self.probIn=Entry(self.tk,width=10,justify="center")
        self.probIn.insert(END,"0")
        self.probIn.pack(side=TOP, padx=10, pady=10)


        #Start
        self.startBttn= Button(self.tk, text="Normal",state="active", command=self.run)
        self.startBttn.pack(side=TOP, padx=10, pady=10)

        #Start with colors
        self.startCBttn= Button(self.tk, text="Colors",state="active", command=self.runCol)
        self.startCBttn.pack(side=TOP, padx=10, pady=10)

        #StartQueen
        self.startQBttn= Button(self.tk, text="Queens",state="active", command=self.runCol)
        self.startQBttn.pack(side=TOP, padx=10, pady=10)

        #Colors
        self.colora=((250.0,250.0,250.0), '#ffffff')
        self.colorb=((0.0,0.0,0.0), '#000000')
        self.colorPicka=Button(text='Living Color', command=self.getColora)
        self.colorPicka.pack(side=TOP, padx=10, pady=10)
        self.colorPickb=Button(text='Dead Color', command=self.getColorb)
        self.colorPickb.pack(side=TOP, padx=10, pady=10)

        #Instructions
        self.instructLbl=Label(self.tk,text="WASD: for moving the camera\n\n Up/Down: Zoom +/-\n\n Left: Run/Stop\n\n Right: Setp")
        self.instructLbl.pack(side=TOP, padx=10, pady=10)

    def start(self):
        self.tk.mainloop()

    def run(self):
        pNorm="{:.5f}".format(st.norm.ppf(float(self.probIn.get())/100))
        automat=Popen(["./Automata",self.sizeIn.get(),pNorm,str(int(self.colora[0][0])),str(int(self.colora[0][1])),str(int(self.colora[0][2])),str(int(self.colorb[0][0])),str(int(self.colorb[0][1])), str(int(self.colorb[0][2])),'0'])
        automat.wait()
        self.plot()

    def runCol(self):
        pNorm="{:.5f}".format(st.norm.ppf(float(self.probIn.get())/100))
        automat=Popen(["./Automata",self.sizeIn.get(),pNorm,str(int(self.colora[0][0])),str(int(self.colora[0][1])),str(int(self.colora[0][2])),str(int(self.colorb[0][0])),str(int(self.colorb[0][1])), str(int(self.colorb[0][2])),'1'])
        automat.wait()
        self.plot()

    def getColora(self):
        self.colora = askcolor()
        self.colorPicka.configure(bg = self.colora[1])

    def getColorb(self):
        self.colorb = askcolor()
        self.colorPickb.configure(bg = self.colorb[1])

    def plot(self):
        x = []
        y = []
        with open('gens','r') as csvfile:
            plots = csv.reader(csvfile, delimiter=',')
            for row in plots:
                x.append(int(row[0]))
                y.append(int(row[1]))
        m=100*np.mean(y)/(int(self.sizeIn.get())* int(self.sizeIn.get()))
        n=np.mean(y)
        y_mean = [n]*len(x)
        mean_line = plt.plot(x,y_mean, label='Mean: '+str(round(m,2))+'%', linestyle='--')
        if self.colora[1]=='#ffffff':
            plt.plot(x,y,self.colorb[1], label='Pheromones')
        else:
            plt.plot(x,y,self.colora[1], label='Pheromones')
        plt.xlabel('Gen')
        plt.ylabel('Pheromones')
        plt.title('Size'+self.sizeIn.get()+'x'+self.sizeIn.get()+'\n')
        plt.legend()
        plt.show()


Life = UI()
Life.start()
