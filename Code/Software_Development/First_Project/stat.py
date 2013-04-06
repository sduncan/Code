import math

#p = [100, 200, 300, 400]
#I guess this stuff might be useful for giving people stats.
def mean(data):
    sum = 0
    for i in range(len(data)):
        sum += data[i]
    sum /= len(data)
    return sum

def stddev(data):
    avg = mean(data)
    sqdev = []
    for i in range(len(data)):
        sqdev.append((data[i]-avg)*(data[i]-avg))
    return math.sqrt(mean(sqdev))

#print stddev(p)
