from  tkinter  import *
import threading
import random as rng
from subprocess import Popen

class Automata:
    toggle=False#toggle between which array use
    running=False#toggle between running and stopped
    cellCount=0
    gridSize=100
    cellsOn=[0]*(gridSize*gridSize)
    cellsOff=[0]*(gridSize*gridSize)
    cellSize=1000.0/gridSize

    def __init__(self):
        self.tk=Tk()
        self.tk.title("Automata")
        self.tk.geometry("200x800")
        self.sizeLbl=Label(self.tk,text="Size of the grid")
        self.sizeLbl.pack(side=TOP, padx=10, pady=(200,5))
        self.sizeIn=Entry(self.tk,width=10,justify="center")
        self.sizeIn.insert(END,"400")
        self.sizeIn.pack(side=TOP, padx=10, pady=10)

        self.sizeLbl=Label(self.tk,text="Probability")
        self.sizeLbl.pack(side=TOP, padx=10, pady=(10,5))

        self.probIn=Entry(self.tk,width=10,justify="center")
        self.probIn.insert(END,"10")
        self.probIn.pack(side=TOP, padx=10, pady=10)

        self.startBttn= Button(self.tk, text="Run",state="active", command=self.run)
        self.startBttn.pack(side=TOP, padx=10, pady=10)
        """
        self.stopBttn= Button(self.tk, text="Stop",state="active", command=self.run)
        self.stopBttn.pack(side=TOP, padx=10, pady=10)

        self.stepBttn=Button(self.tk, text="Step",state="active", command=self.run)
        self.stepBttn.pack(side=TOP, padx=10, pady=10)
        """


    def start(self):
        self.tk.mainloop()

    def run(self):
        automat=Popen(["./Automata",self.sizeIn.get(),self.probIn.get()])
        self.startBttn.config(state="disabled")
        automat.wait()
        self.startBttn.config(state="normal")
        #print(self.sizeIn.get())

GUI = Automata()
GUI.start()
