import random
import string
t = random.randint(1, 5)
n = random.randint(1, 10)
m = random.randint(1, n)
q = random.randint(1, 1e9+7)
print(t, n, m, q)
for i in range(t):
    p="".join([ i for i in random.choices(string.ascii_letters, k = n)])
    print(p)
for i in range(t):
    p="".join([ i for i in random.choices(string.ascii_letters, k = m)])
    print(p)
print((52**4*26+52**3*35+52**2*11+52*36+35)%63893080)
#"""
# n = 5
# m = 4
# q = 5
# point = [i for i in range(1, n)]
# print(n, m, q * 2)
# random.shuffle(point)
# for i in range(m):
#     print(random.randint(0, i), i + 1, random.randint(0, 10))

# for i in range(q):
#     type = random.randint(1, 10)
#     if type == 1 or type == 2:
#         print(1)
#     elif type == 4:
#         print(2)
#     else:
#         print(5, random.randint(0, 10))

# for i in range(q):
#     type = random.randint(1, 10)
#     if type == 1 or type == 2:
#         print(2)
#     elif type == 4:
#         print(1)
#     else:
#         print(5, random.randint(0, 10))