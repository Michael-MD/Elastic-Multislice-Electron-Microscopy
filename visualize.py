import numpy as np
import matplotlib.pyplot as plt

def importdata(filename):
    with open(filename) as f:
        lines = f.readlines()
        x = np.array(([line.split() for line in lines]))
        

    return np.array(x.astype(float))

def pp(d):
    print(d)
    plt.figure()
    plt.imshow(d)
    plt.colorbar()
    plt.show()

f_re = importdata("pot.txt")
pp(f_re)

# x = importdata('x.txt')
# P = importdata('P.txt')

# plt.plot(x,P)
# # plt.xscale('log')
# plt.show()

# psi_re = importdata('psi_re.txt')
# psi_im = importdata('psi_im.txt')
# psi = psi_re + 1j*psi_im
# i =  psi*np.conjugate(psi)
# print(i.shape)
# pp(np.real(i))
# print(np.sum(i)*0.06)
# v = importdata('i.txt')
# pp(v)


