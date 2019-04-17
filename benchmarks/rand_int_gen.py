import random
from sys import argv

def convert(x):
        s = ""
        for a in x:
                s+=str(a)
                s+=','
        return s

a = 1
b = 9
c = int(argv[2])

f = open(argv[1],"w+")
x = [random.randint(a,b) for x in range(c)]
s = convert(x)
s = s[:len(s)-1]
s += "\n"

f.write(s)
f.close()
