#!/usr/bin/env python3

print("Provide a size of a map:")
n = int(input())
map_size = n
n = n-1

maps = []
for i in range(map_size):
    z = int(input())
    maps.append(z)
    
m = int((n+2)*(n+1)/2)
m
multi_size = []
for j in range(m):
    current = 0;
    for i in range(j, map_size):
        current = maps[i] + current
        multi_size.append(current)
        
               
multi_size.sort(reverse=True)
multi_size

string = ""
for i in range(m):
    string = string + str(multi_size[i]) + " "
    
string = string + "\n"

f = open("multiset.txt", "a")
f.write(string)
f.close()      
    
