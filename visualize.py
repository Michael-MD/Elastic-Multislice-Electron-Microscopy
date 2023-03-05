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





def plot_elem(Z):
    x = importdata(str(Z)+".txt")
    s1,s2 = x.shape
    f = np.fft.fftfreq(s2, 1/2)
    plt.plot(f[0:int(s2/2)],x[0, 0:int(s2/2)])


plot_elem(6)
plot_elem(14)
plot_elem(29)
plot_elem(79)
plot_elem(92)
plt.show()

# psi_re = importdata('psi_re.txt')
# psi_im = importdata('psi_im.txt')
# psi = psi_re + 1j*psi_im
# i =  psi*np.conjugate(psi)
# print(i.shape)
# pp(np.real(i))
# print(np.sum(i)*0.06)
# v = importdata('i.txt')
# pp(v)


