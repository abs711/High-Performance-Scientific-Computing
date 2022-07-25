# 
#  This file is part of the course materials for AMATH483/583 at the University of Washington,
#  Spring 2017
# 
#  Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
#  https://creativecommons.org/licenses/by-nc-sa/4.0/
# 
#  Author: Andrew Lumsdaine
# 

import matplotlib
matplotlib.use('Agg')


import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

import csv
from itertools import takewhile

import csv
import sys
import os
import io
import re


plt.figure(figsize=(9,4))

names = []

for name in sys.argv[1:]:

    infile = name

    names.append(os.path.basename(name).replace(".out.txt",""))

    legs = []
    with open(infile, 'r') as csvfile:
        bulk = csvfile.read()
        blocks = re.compile(r"\n{2,}").split(bulk)

        for b in blocks:
            title = b[0:4]
            legs.append(title);

            Ns = []
            Ps = []
            Ts = []
            Ss = []

            reader = csv.DictReader(io.StringIO(b[5:]), delimiter='\t')

            for row in reader:

              if row['procs'] != None and row['ms_per'] != None:
                  Ns.append(int(row['procs']))
                  Ts.append(float(row['ms_per']))
                  Ss.append(Ts[0]/float(row['ms_per']))



            plt.loglog(Ns, Ss)

pp = PdfPages('time.pdf')

#plt.axis([0, 2048, .01, 24])

plt.legend(names, loc='upper left', fontsize='small')
plt.title('Euclidean Norm Computation')
plt.xlabel('Processes')
plt.ylabel('Speedup')
plt.xticks([1, 2, 4, 8, 16, 32],[1, 2, 4, 8, 16, 32])
bottom,top = plt.ylim()

foo = 1
while foo > bottom:
    foo = foo / 2
bar = 1
while bar < top:
    bar = bar * 2

bax = []
x = foo
while x < bar:
    bax.append(x);
    x = x * 2;

print(bax)

plt.yticks([])
plt.yticks(bax, bax)


pp.savefig()
pp.close()
# plt.show()




    

