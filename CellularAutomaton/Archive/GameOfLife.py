from  tkinter  import *
import threading
import random as rng

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

        self.canvas=Canvas(self.tk,width=1000,height=1000,bg="black")
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

        #

    def start(self):
        self.tk.mainloop()

    def run(self):
        self.startBttn(state="DISABLED")
        threading.Timer(1.0/30.0, self.run).start()

    def stop(self):
        self.stopBttn(state="disabled")
        self.runnign=False
        return

    def step(self):
        #print('something')
        self.updateCells()
        self.draw()
        #print('something else')

    def getIndex(self,x,y):
        return (y*self.gridSize)+x

    def getCVal(self,x,y):#

        if not self.toggle:
            return self.cellsOn[self.getIndex(x,y)]
        else:
            return self.cellsOff[self.getIndex(x,y)]

    def getNVal(self,x,y):#
        if x<0:
            x=self.gridSize-1
        elif x==self.gridSize:
            x=0
        if y<0:
            y=self.gridSize-1
        elif y==self.gridSize:
            y=0

        if self.toggle:
            return self.cellsOn[self.getIndex(x,y)]
        else:
            return self.cellsOff[self.getIndex(x,y)]

    def getNeigh(self,x,y):
        #print("NewNeight",x,",",y)
        return (self.getNVal(x-1,y-1)+self.getNVal(x-1,y)+self.getNVal(x-1,y+1)+self.getNVal(x,y-1)+self.getNVal(x,y+1)+self.getNVal(x+1,y-1)+self.getNVal(x+1,y)+self.getNVal(x+1,y+1))


    def setRNG(self):
        for y in range(self.gridSize):
            for x in range(self.gridSize):
                if rng.random()<.10:
                    self.cellsOff[self.getIndex(x,y)]=1;
                    self.canvas.create_rectangle(x*self.cellSize,y*self.cellSize,(x+1)*self.cellSize,(y+1)*self.cellSize, fill="white")
                else:
                    self.cellsOff[self.getIndex(x,y)]=0;
                    self.canvas.create_rectangle(x*self.cellSize,y*self.cellSize,(x+1)*self.cellSize,(y+1)*self.cellSize, fill="black")


    def rule(self,x,y):
        sum=self.getNeigh(x,y)
        if(self.getNVal(x,y)):# TODO: Change to current val
            if(sum>=2 and sum<=3):
                return 1
        elif(sum>=3 and sum<=3):
            return 1
        else:
            return 0

    def setNext(self,x,y):
        if self.toggle:
            if self.rule(x,y):
                self.cellsOff[self.getIndex(x,y)]=1
            else:
                self.cellsOff[self.getIndex(x,y)]=0
        else:
            if self.rule(x,y):
                self.cellsOn[self.getIndex(x,y)]=1
            else:
                self.cellsOn[self.getIndex(x,y)]=0

    #Iterates through the array
    def updateCells(self):
        for x in range(0,self.gridSize):
            for y in range(0,self.gridSize):
                self.setNext(x,y)
        self.toggle=not self.toggle


    def draw(self):
        if self.toggle:
            for y in range(self.gridSize):
                for x in range(self.gridSize):
                    if self.cellsOn[self.getIndex(x,y)]==1:
                        self.canvas.create_rectangle(x*self.cellSize,y*self.cellSize,(x+1)*self.cellSize,(y+1)*self.cellSize, fill="white")
                    else:
                        self.canvas.create_rectangle(x*self.cellSize,y*self.cellSize,(x+1)*self.cellSize,(y+1)*self.cellSize, fill="black")
        else:
            for y in range(self.gridSize):
                for x in range(self.gridSize):
                    if self.cellsOff[self.getIndex(x,y)]==1:
                        self.canvas.create_rectangle(x*self.cellSize,y*self.cellSize,(x+1)*self.cellSize,(y+1)*self.cellSize, fill="white")
                    else:
                        self.canvas.create_rectangle(x*self.cellSize,y*self.cellSize,(x+1)*self.cellSize,(y+1)*self.cellSize, fill="black")


GOL = Automata()
GOL.start()
