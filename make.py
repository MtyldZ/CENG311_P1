import random

f = open("input-2^28.txt", "a")

i = 0
limit = 2 ** 26
while(i < limit):
    number = str(random.randint(0,100)) + " "
    f.write(number)
    i+=1

f.close()
