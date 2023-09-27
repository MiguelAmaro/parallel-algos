import math
import random as rnd
from statistics import mean

#https://www.youtube.com/watch?v=EaR3C4e600k&t=335s

n = 1000000
c = 0
for i in range(n):
    x = -1.0 + 2.0*rnd.random()
    y = -1.0 + 2.0*rnd.random()
    if x**2 + y**2 <= 1:
        c +=1

res_analytical = math.pi/4
res = c/n
print("monte carlo result: ", res, " expected: ", res_analytical)

#example 2
#rules:
#   probability of winning a round in a game:
#   P(win) = p
#   if loose 2 rounds consequtevly then game is over
#   analytic solution
#cases:     w         ll              lw
#   e = (1+e)(p) + (2)(1-p)(1-p) + (2+e)(1-p)(p)

rounds = []
p = 0.65
for i in range(n*2):
    roundcount = 0
    conseclosscount = 0
    
    while conseclosscount < 2:
        roundcount += 1
        sample = rnd.random()
        if sample < p:
            conseclosscount = 0
        else:
            conseclosscount += 1
    
    rounds.append(roundcount)

res_analytical = (2-p)/(1-p)**2
res = mean(rounds)
print("monte carlo result: ", res, " expected: ", res_analytical)
