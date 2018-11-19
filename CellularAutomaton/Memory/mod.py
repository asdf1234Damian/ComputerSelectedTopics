current=0
next=1
memory=4
for i in range( 10):
    print("{}, {}".format(current,next))
    current=next
    next=(current +1)% memory
