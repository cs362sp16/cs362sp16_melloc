import sys
import os

g1 = sys.argv[1]
g2 = sys.argv[2]
seed = sys.argv[3]
originalDirectory = os.getcwd()

os.chdir(g1)
os.system("make clean; make testdominion; ./testdominion " + seed + " > " + originalDirectory + "/out1")

os.chdir(originalDirectory)
os.chdir(g2)
os.system("make clean; make testdominion; ./testdominion " + seed + " > " + originalDirectory + "/out2")

f1 = originalDirectory + "/out1"
f2 = originalDirectory + "/out2"

l1 = []
l2 = []



n = 0
for l in open(f1):
    l1.append ((n, l))
    n += 1

n = 0
for l in open(f2):
    l2.append ((n, l))
    n += 1

print "LENGTH",f1,len(l1)
print "LENGTH",f2,len(l2)

for i in xrange(0,min(len(l1),len(l2))):
    (n, nl1) = l1[i]
    (n, nl2) = l2[i]
    if nl1 != nl2:
        print "MISMATCH AT LINE",i+1
        print f1,nl1[:-1]
        print f2,nl2[:-1]
        print "PRIOR TO DIVERGENCE:"
        print f1,(l1[i-1][1])[:-1]
        print f2,(l2[i-1][1])[:-1]
        break
