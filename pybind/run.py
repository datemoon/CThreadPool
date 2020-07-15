import example
import numpy as np


handle=example.Init(1,2)

print(example.Add(handle))
test_str='test print'
example.Print(test_str)
print(test_str)
example.Destory(handle)

nptest=np.array(range(10),dtype=np.float32).reshape(2,5)
print(nptest)
example.SetNumpyZero(nptest)
print(nptest)

def Print(str1):
    print(str1)
    str1='test ok'
    print(str1)

print('-----------')
Print(test_str)
print(test_str)
