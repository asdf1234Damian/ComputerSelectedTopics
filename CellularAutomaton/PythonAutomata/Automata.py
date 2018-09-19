import pyglet

import random as rng
class Automata(pyglet.window.Window):
    def __init__(self,size,p,ls,us,lb,ub):
        super().__init__(1000,1000)
        self.width=(1000)
        self.height=(1000)
        self.size=size
        self.p=p
        self.ls=ls
        self.us=us
        self.lb=lb
        self.ub=ub
        sefl.flipFlip=false;
        self.cellSize=(width/size)
        self.cells=[None]*size
        self.cellsNext=[None]*size

    def on_draw(self):
        self.clear()
        for y in range(size):
            for x in range(size):
                if self.cells[getIndex(x,y)]==1:
                    cellcords=(x*self.cellSize,y*self.cellSize,
                    x*self.cellSize,(y+1)*self.cellSize,
                    (x+1)*self.cellSize,y*self.cellSize,
                    (x+1)*self.cellSize,(y+1)*self.cellSize)
                    pyglet.graphics.draw_indexed(4,pyglet.gl.GL_TRIANGLES,[0,1,2,1,2,3],('v2i',square_cords))



    def getIndex(self,x,y):
        return (self.size * y +x)

    #def getValue(self,x,y):
    #    if
    #

    def cellsRNG(self):
        for y in range(size):
            for x in range(size):
                if rng.random()<p/10:
                    self.cells[getIndex(x,y)].append(1)
                else:
                    self.cells[getIndex(x,y)].append(0)

    #def fname(arg):
