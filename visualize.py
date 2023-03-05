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


# *************** start potential ***************
Fre = importdata('Fre.txt')
pp(Fre)

# *************** end potential ***************



# *************** start scattering factor ***************

# def plot_elem(Z,elem):
#     x = importdata(str(Z)+".txt")
#     s1,s2 = x.shape
#     f = np.fft.fftfreq(s2, 1/4)
#     plt.plot(f[0:int(s2/2)],x[0, 0:int(s2/2)], label=elem)


# plot_elem(6, 'C')
# plot_elem(14, 'Si')
# plot_elem(29, 'Cu')
# plot_elem(79, 'Au')
# plot_elem(92, 'U')
# plt.legend()
# plt.xlabel('scattering angle k (1/Ang.)')
# plt.ylabel('scattering factor (in Ang.)')
# plt.title('Fig 5.8 of Kirkland')
# plt.savefig('Fig 5.8.jpg')
# plt.show()

# *************** end scattering factor ***************
