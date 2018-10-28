import scipy.stats as st
from  tkinter  import *
import threading, os, errno, shlex
from subprocess import Popen, PIPE
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import csv
import numpy as np
import random as rng
from tkinter.colorchooser import *
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg


class UI():
    def __init__(self):
        self.x=[]
        self.y=[]
        self.tk=Tk()
        self.tk.title("Automata")
        self.tk.geometry("200x1900+0+100")

        #Grid size input
        self.sizeLbl=Label(self.tk,text="Size of the grid")
        self.sizeLbl.pack(side=TOP, padx=10, pady=(200,5))
        self.sizeIn=Entry(self.tk,width=10,justify="center")
        self.sizeIn.insert(END,"400")
        self.sizeIn.pack(side=TOP, padx=10, pady=10)


        #Probability
        self.sizeLbl=Label(self.tk,text="Probability")
        self.sizeLbl.pack(side=TOP, padx=10, pady=(10,5))
        self.probIn=Entry(self.tk,width=10,justify="center")
        self.probIn.insert(END,"20")
        self.probIn.pack(side=TOP, padx=10, pady=10)


        #Rule
        self.ruleLbl=Label(self.tk,text="Rule")
        self.ruleLbl.pack(side=TOP, padx=10, pady=(10,5))
        self.ruleIn=Entry(self.tk,width=10,justify="center")
        self.ruleIn.insert(END,"2,7,4,6")
        self.ruleIn.pack(side=TOP, padx=10, pady=(10,5))


        #Start
        self.startBttn= Button(self.tk, text="Run",state="active", command=self.run)
        self.startBttn.pack(side=TOP, padx=10, pady=10)

        #Colors
        self.colora=((250.0,250.0,250.0), '#ffffff')
        self.colorb=((0.0,0.0,0.0), '#000000')
        self.colorPicka=Button(text='Living Color', command=self.getColora)
        self.colorPicka.pack(side=TOP, padx=10, pady=10)
        self.colorPickb=Button(text='Dead Color', command=self.getColorb)
        self.colorPickb.pack(side=TOP, padx=10, pady=10)

        self.fig = plt.figure()
        self.plot = self.fig.add_subplot(1, 1, 1)
        self.canvas = FigureCanvasTkAgg(self.fig, master=self.tk)
        self.canvas.draw()
        self.canvas.get_tk_widget().pack(side=TOP, padx=20, pady=20)

        #Instructions
        self.instructLbl=Label(self.tk,text="WASD: for moving the camera\n\n Up/Down: Zoom +/-\n\n Left: Run/Stop\n\n Right: Setp")
        self.instructLbl.pack(side=TOP, padx=10, pady=10)

    def start(self):
        self.tk.mainloop()

    def run(self):
        pNorm="{:.5f}".format(st.norm.ppf(float(self.probIn.get())/100))
        rule=self.ruleIn.get().split(',')
        ls=rule[0]
        us=rule[1]
        lb=rule[2]
        ub=rule[3]
        automat=Popen(["source/./Automata",self.sizeIn.get(),pNorm,str(int(self.colora[0][0])),str(int(self.colora[0][1])),str(int(self.colora[0][2])),str(int(self.colorb[0][0])),str(int(self.colorb[0][1])), str(int(self.colorb[0][2])),ls,us,lb,ub], stdout=PIPE, bufsize=1)
        with automat.stdout:
            for line in iter(automat.stdout.readline,b''):
                self.x.append(int(line.decode('utf-8').split(',')[0]))
                self.y.append(int(line.decode('utf-8').split(',')[1]))
                self.pltG()

    def getColora(self):
        self.colora = askcolor()
        self.colorPicka.configure(bg = self.colora[1])

    def getColorb(self):
        self.colorb = askcolor()
        self.colorPickb.configure(bg = self.colorb[1])

    def plt(self):
        m=100*np.mean(self.y)/(int(self.sizeIn.get())* int(self.sizeIn.get()))
        n=np.mean(self.y)
        y_mean = [n]*len(self.x)
        mean_line = self.canvas.plot(self.x,y_mean, label='Mean: '+str(round(m,2))+'%', linestyle='--')
        if self.colora[1]=='#ffffff':
            self.canvas.scatter(self.x,self.y,c=self.colorb[1], label='Living Cells')
        else:
            self.canvas.scatter(self.x,self.y,c=self.colora[1], label='Living Cells')
        self.canvas.xlabel('Gen')
        self.canvas.ylabel('Alive')

Life = UI()
Life.start()
