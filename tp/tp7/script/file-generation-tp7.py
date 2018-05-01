import os
import random
import glob, os, os.path

nb_element = 96
random_min = -32767
random_max = 32767
list_r = []

main_dir= 'res/demo/tp7'
r_dir = main_dir + '/R'

os.makedirs(main_dir, exist_ok=True)
os.makedirs(r_dir, exist_ok=True)

# remove all file in r_dir
filelist = glob.glob(os.path.join(r_dir, "*"))
for f in filelist:
    os.remove(f)

# generation r
while len(list_r) < nb_element :
    val= random.randint(random_min,random_max)
    if val in list_r:
        continue
    else:
        list_r.append(val)

# melange
random.shuffle(list_r)

# enregistrement des segment
file_number=0
while(len(list_r) > 0):
    f= open( r_dir + "/" + str(file_number)+'.txt', 'w+')
    for index in range(10):
        f.write(str(list_r.pop(0))+ "\n")
        if(len(list_r) == 0):
            break
    file_number+=1
