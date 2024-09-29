
'''
a = [(2,), (3,), (4,), (5,), (6,)]
result = ','.join(map(lambda x: str(x[0]), a))
print(result)
#a = list(map(lambda char: (int(char),), result.split(',')))
#print(a)

'''
a = '1(=s=)1#=w=#2(=s=)2'
print(list(map(lambda pair: tuple(pair.split('((=s=))')), a.split('#=w=#'))))
