import numpy as np
import matplotlib.pyplot as plt
s=50
def importdata(filename, a=0, b=0):
    with open(filename) as f:
        lines = f.readlines()
        x = np.array(([line.split() for line in lines]))
        
    x = np.array(x.astype(float))

    # fs = 512/50
    # s1,s2 = x.shape
    # kx = np.fft.fftfreq(s1, 1/fs)
    # ky = np.fft.fftfreq(s2, 1/fs)
    # kx, ky = np.meshgrid(kx, ky)
    # x = x * np.exp(1j*(kx * a + ky * b)*2*np.pi)
    # x = np.fft.fft2(x)

    return x

def pp(d):
    print(d)
    plt.figure()
    plt.imshow(d)
    plt.colorbar()
    plt.show()


def bw_limit(x):
    s1,s2 = x.shape
    fs = min(512/50,512/s)
    kx = np.fft.fftfreq(s1, 1/fs)
    ky = np.fft.fftfreq(s2, 1/fs)
    kx, ky = np.meshgrid(kx, ky)
    k = np.sqrt(kx**2 + ky**2)
    mask = k > (1/3)*(fs)
    x = np.fft.fft2(x)
    x[mask] = 0
    x = np.fft.ifft2(x)
    return x


psi = importdata('psi_re.txt') + 1j * importdata('psi_im.txt')
intensity = np.abs(psi)**2 / (512*2)**2
print(sum(sum(intensity)))
plt.imshow(psi.astype(float),'gray')
plt.colorbar()
plt.show()

"""
# transmission function test as calculated from c++ program to produce fig 5.11 of kirkland
t_re_u = importdata('t_re_u.txt')
t_im_u = importdata('t_im_u.txt')
tre_line = (t_re_u)[int(512/2),:]
tim_line = (t_im_u)[int(512/2),:]
r = np.linspace(0,50,512)
plt.subplot(2,1,1)
plt.title('Fig. 5.11 of Kirkland')
plt.plot(r,(tre_line))
plt.ylabel('Real Part')
plt.subplot(2,1,2)
plt.ylim([0,1.2])
plt.plot(r,(tim_line))
plt.ylabel('Imag. Part')
plt.xlabel('position x (in Ang.)')
plt.ylim([0,1])
plt.show()

# *************** start transmission function ***************

c = importdata('c.txt', 25, 5)
si = importdata('si.txt', 25, 15)
cu = importdata('cu.txt', 25, 25)
au = importdata('au.txt', 25, 35)
u = importdata('u.txt', 25, 45)
v = c+si+cu+au+u
lam = 1/39.87345849884623
gamma = 1.39139023969897
v= np.real(v)*lam* gamma / (50*50)
t = np.exp(1j * v)
# t = importdata('t_re_u.txt') + 1j*importdata('t_im_u.txt')
t = bw_limit(t)
# pp(np.real(t))
t = t[int(512/2),:]
tre_line = (np.real(t))
tim_line = (np.imag(t))
r = np.linspace(0,50,512)
plt.subplot(2,1,1)
plt.title('Fig. 5.11 of Kirkland')
plt.plot(r,(tre_line))
plt.ylabel('Real Part')
plt.subplot(2,1,2)
plt.ylim([0,1.2])
plt.plot(r,(tim_line))
plt.ylabel('Imag. Part')
plt.xlabel('position x (in Ang.)')
plt.ylim([0,1])
# plt.savefig('Fig 5.11.jpg')
plt.show()



# *************** end transmission function ***************



# *************** start scattering factor ***************

def plot_elem(Z,elem):
    x = importdata(str(Z)+".txt")
    s1,s2 = x.shape
    f = np.fft.fftfreq(s2, 1/4)
    plt.plot(f[0:int(s2/2)],x[0, 0:int(s2/2)], label=elem)


plot_elem(6, 'C')
plot_elem(14, 'Si')
plot_elem(29, 'Cu')
plot_elem(79, 'Au')
plot_elem(92, 'U')
plt.legend()
plt.xlabel('scattering angle k (1/Ang.)')
plt.ylabel('scattering factor (in Ang.)')
plt.title('Fig 5.8 of Kirkland')
# plt.savefig('Fig 5.8.jpg')
plt.show()

# *************** end scattering factor ***************
"""