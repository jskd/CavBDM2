import os
import random
import glob, os, os.path

nb_jointure = 32
nb_element = 256
random_min = -32767
random_max = 32767
list_s = []
list_r = []

main_dir= 'res/demo/tp6'
r_dir = main_dir + '/R'
s_dir = main_dir + '/S'

os.makedirs(main_dir, exist_ok=True)
os.makedirs(r_dir, exist_ok=True)
os.makedirs(s_dir, exist_ok=True)

# remove all file in r_dir
filelist = glob.glob(os.path.join(r_dir, "*"))
for f in filelist:
    os.remove(f)

# remove all file in s_dir
filelist = glob.glob(os.path.join(s_dir, "*"))
for f in filelist:
    os.remove(f)

# generation valeur de jointure
i=0
while i < nb_jointure :
    val= random.randint(random_min,random_max)
    if val in list_s or val in list_r:
        continue
    else:
        list_s.append(val)
        list_r.append(val)
    i+=1

# generation s
while len(list_s) < nb_element :
    val= random.randint(random_min,random_max)
    if val in list_s or val in list_r:
        continue
    else:
        list_s.append(val)

# generation r
while len(list_r) < nb_element :
    val= random.randint(random_min,random_max)
    if val in list_s or val in list_r:
        continue
    else:
        list_r.append(val)

# melange
random.shuffle(list_r)
random.shuffle(list_s)

# enregistrement des segment
file_number=0
while(len(list_r) > 0):
    f= open('res/demo/tp6/R/'+str(file_number)+'.txt', 'w+')
    for index in range(10):
        f.write(str(list_r.pop(0))+ "\n")
        if(len(list_r) == 0):
            break
    file_number+=1

# enregistrement des segment
file_number=0
while(len(list_s) > 0):
    f= open('res/demo/tp6/S/'+str(file_number)+'.txt', 'w+')
    for index in range(10):
        f.write(str(list_s.pop(0))+ "\n")
        if(len(list_s) == 0):
            break
    file_number+=1
