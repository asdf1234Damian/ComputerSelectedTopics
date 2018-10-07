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
        self.tk.geometry("200x800")

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
        self.probIn.insert(END,"10")
        self.probIn.pack(side=TOP, padx=10, pady=10)
        self.pTypes={'Normal'}
        self.pSel=StringVar(self.tk)
        self.pSel.set('Normal')
        self.probType=OptionMenu(self.tk, self.pSel,*self.pTypes)
        self.probType.pack(side=TOP, padx=10, pady=10)

        #Rule
        self.ruleLbl=Label(self.tk,text="Rule")
        self.ruleLbl.pack(side=TOP, padx=10, pady=(10,5))
        self.ruleIn=Entry(self.tk,width=10,justify="center")
        self.ruleIn.insert(END,"2,3,3,3")
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

        #Instructions
        self.instructLbl=Label(self.tk,text="WASD: for moving the camera\n\n Up/Down: Zoom +/-\n\n Left: Run/Stop\n\n Right: Setp")
        self.instructLbl.pack(side=TOP, padx=10, pady=10)

    def start(self):
        self.tk.mainloop()

    def run(self):
        rule=self.ruleIn.get().split(',')
        ls=rule[0]
        us=rule[1]
        lb=rule[2]
        ub=rule[3]
        automat=Popen(["./Automata",self.sizeIn.get(),self.probIn.get(),str(int(self.colora[0][0])),str(int(self.colora[0][1])),str(int(self.colora[0][2])),str(int(self.colorb[0][0])),str(int(self.colorb[0][1])), str(int(self.colorb[0][2])),ls,us,lb,ub])
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
            plt.plot(x,y,self.colorb[1], label='Living Cells')
        else:
            plt.plot(x,y,self.colora[1], label='Living Cells')
        plt.xlabel('Gen')
        plt.ylabel('Alive')
        plt.title('Size'+self.sizeIn.get()+'x'+self.sizeIn.get()+'\n')
        plt.legend()
        plt.show()


Life = UI()
Life.start()
