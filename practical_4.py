import cv2
import numpy

def unary(x):
	return (('1' * x) + '0')

path = f'sena.png'
img = cv2.imread(path , 0)

y = []
# y = img[0][0:10]
for i in range(256):
	for j in range(256):
		y.append(img[i][j])

y_max = numpy.max(y)
y_min = numpy.min(y)
y_cap = [0 for i in range(len(y))]
d = [0 for i in range(len(y))]
t = [0 for i in range(len(y))]
x = [0 for i in range(len(y))]
bin_x = []
code_x = []

# print(y)
print(f'ymax {y_max} ymin {y_min}')

y_cap[0] = 0
d[0] = y[0]
t[0] = -1 * y_min
x[0] = t[0] + abs(d[0])
# print(f'y {y[0]} y_ {y_cap[0]} d {d[0]} t {t[0]} x {x[0]}')
bin_x.append(bin(x[0])[2:])
if (len(bin_x[0]) <= 5) :
	code_x.append(bin_x[0] + '0')
else : 
	bin_x[0] = '0'*(8-len(bin_x[0])) + bin_x[0]
	code_x.append(bin_x[0][3:] + unary(int(bin_x[0][0:3],2)))
# print(f'bin_x0 {bin_x[0]}')
# print(f'codex0 {code_x[0]}')


print(len(y_cap))
output = len(code_x[0])
for i in range(1,len(y)):
	
	y_cap[i] = int(y[i-1])
	
	d[i] = y[i] - y_cap[i]
	
	t[i] = min((y_max - y_cap[i]), (y_cap[i] - y_min))

	if (d[i] >= 0) and (d[i] <= t[i]):
		x[i] = 2 * d[i]
	elif (d[i] >= -1*t[i]) and (d[i] < 0):
		x[i] = (2 * abs(d[i])) - 1
	else :
		x[i] = t[i] + abs(d[i])

	bin_x.append(bin(x[i])[2:])	

	if (len(bin_x[i]) <= 5):
		code_x.append(bin_x[i] + '0')
	else :
		bin_x[i] = '0'*(8-len(bin_x[i])) + bin_x[i]
		code_x.append(bin_x[i][3:] + unary(int(bin_x[i][0:3],2)))
	# print(f'y {y[i]} y_ {y_cap[i]} d {d[i]} t {t[i]} x {x[i]} bin_x {bin_x[i]} code {code_x[i]}')

	output += len(code_x[i])

print(output)

# file = open("sena_compress.txt","w")
# for i in code_x:
# 	file.write(i)
# file.close()

# print(f'y {y}')
# print(f'y_cap {y_cap}') 
# print(f'd {d}')
# print(f't {t}')
# print(f'x {x}')
# print(f'code {code_x}')