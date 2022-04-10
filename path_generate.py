import os
# import stat
path = '/'
f = open("exception.txt", "w")
g = open("dirinfo.txt", "w")
h = open("fileinfo.txt", "w")

for i in os.walk(path):
    print(i[0]+"&"+str(os.stat(i[0]).st_mode), file = g)
    for file in i[2]:
        try:
            p = os.path.join(i[0], file)
            print(p+"&"+str(os.stat(p).st_mode),file = h)
        except Exception as err:
            print(err, file=f)
g.close()
f.close()
h.close()