
mp={}
f = open('kwName.txt','r',encoding='UTF-8')
while True:
    line=f.readline()
    if not line:
        break
    s=line.split()
    if len(s)<2:
        continue
    name=s[1].lower()
    id=int(s[0])
    mp[name]=id
f.close()


grp=[]
f=open('kwMap.txt','r',encoding='UTF-8')
while True:
    line=f.readline()
    if not line:
        break
    s=line.split()
    nl=[]
    n=len(s)
    for i in range(1,n):
        nl.append(int(s[i]))
    grp.append(nl)
f.close()


qry=[]
f=open('query.txt','r',encoding='UTF-8')
while True:
    line=f.readline()
    if not line:
        break
    s=line.split()
    nl=[]
    n=len(s)
    for i in range(0,n):
        nl.append(mp[s[i]])
    qry.append(nl)
f.close()

f=open('newquery.txt','w')
print(len(qry),file=f)
for L in qry:
    print(len(L),file=f)
    for i in range(0,len(L)):
        print(len(grp[L[i]]),end=' ',file=f)
        for x in grp[L[i]]:
            print(x,end=' ',file=f)
        print('',file=f)
f.close()