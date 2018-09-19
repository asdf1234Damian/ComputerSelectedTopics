from  tkinter  import *
import threading
import random as rng

class Automata:
    state=False#toggle between which array use
    running=False#toggle between running and stopped
    cellCount=0
    gridSize=400
    cells=[0 for i in range(gridSize*gridSize)]
    #cellsB=[0 for i in range(gridSize)]


    def __init__(self):
        self.tk=Tk()

        self.canvas=Canvas(self.tk,width=800,height=800,bg="black")
        self.canvas.pack(side=RIGHT)

        self.sizeLbl=Label(self.tk,text="Size of the grid")
        self.sizeLbl.pack(side=TOP, padx=10, pady=(200,5))

        self.sizeIn=Entry(self.tk,width=10,justify="center")
        self.sizeIn.insert(END,"400")
        self.sizeIn.pack(side=TOP, padx=10, pady=10)

        self.sizeLbl=Label(self.tk,text="Probability")
        self.sizeLbl.pack(side=TOP, padx=10, pady=(10,5))

        self.sizeIn=Entry(self.tk,width=10,justify="center")
        self.sizeIn.insert(END,"10")
        self.sizeIn.pack(side=TOP, padx=10, pady=10)

        self.startBttn= Button(self.tk, text="Run",state="active", command=self.run)
        self.startBttn.pack(side=TOP, padx=10, pady=10)

        self.stopBttn= Button(self.tk, text="Stop",state="active", command=self.stop)
        self.stopBttn.pack(side=TOP, padx=10, pady=10)

        self.stepBttn=Button(self.tk, text="Step",state="active", command=self.step)
        self.stepBttn.pack(side=TOP, padx=10, pady=10)
        #TODO
        self.loadBttn=Button(self.tk, text="Step",state="active", command=self.step)
        self.loadBttn.pack(side=TOP, padx=10, pady=10)
        #TODO
        self.sizeIn=Entry(self.tk,width=10,text="400")
        self.sizeIn.pack(side=TOP, padx=10, pady=10)
        #TODO
        self.saveBttn=Button(self.tk, text="Step",state="active", command=self.step)
        self.saveBttn.pack(side=TOP, padx=10, pady=10)
        #TODO
        self.clearBttn=Button(self.tk, text="Clear",state="active", command=self.step)
        self.clearBttn.pack(side=TOP, padx=10, pady=10)

        self.setRNG()
        self.draw()

        #

    def start(self):
        self.tk.mainloop()

    def run(self):
        self.startBttn(state="DISABLED")
        threading.Timer(1.0/30.0, self.run).start()

    def stop(self):
        return

    def step(self):
        return

    def getIndex(self,x,y):
        return (y*self.gridSize)+x

    def getVal(self,x,y):
        if x<0:
            x=self.gridSize
        elif x>self.gridSize:
            x=0
        if y<0:
            y=self.gridSize
        elif y>self.gridSize:
            y=0
        return self.cells[]


    def setRNG(self):
        for y in range(self.gridSize):
            for x in range(self.gridSize):
                #TODO change to parameter
                if rng.random()<.10:
                    self.cells[self.getIndex(x,y)]=1;
                else:
                    self.cells[self.getIndex(x,y)]=0;

    def draw(self):
        cellSize=800/self.gridSize
        for y in range(self.gridSize):
            for x in range(self.gridSize):
                if self.cells[self.getIndex(x,y)]==1:
                    self.canvas.create_rectangle(x*cellSize,y*cellSize,(x+1)*cellSize,(y+1)*cellSize, fill="white")


GOL = Automata()
GOL.start()
