array = [5, 224, 125, 150, 221, 12, 140, 145, 114, 68, 20, 206,
 203, 186, 27, 225, 38, 213, 90, 6, 66, 118, 143, 25, 6,
 27, 7, 227, 56, 65, 17, 135, 90, 145, 132, 51, 185, 150,
 158, 235, 103, 120, 158, 80, 51, 184, 18, 74, 235, 158,
 182, 60, 108, 157, 206, 153, 76, 176, 16, 152, 20, 128, 85, 35]
 
sum = 0
for i in range(len(array)):
    sum += array[i]
 
print("Sum: ", sum)