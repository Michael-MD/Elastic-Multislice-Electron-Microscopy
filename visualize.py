import numpy as np
import matplotlib.pyplot as plt
s=50
def importdata(filename, a=0, b=0):
    with open(filename) as f:
        lines = f.readlines()
        x = np.array(([line.split() for line in lines]))
        
    x = np.array(x.astype(float))

    # fs = dim/50
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
    fs = min(dim/50,dim/s)
    kx = np.fft.fftfreq(s1, 1/fs)
    ky = np.fft.fftfreq(s2, 1/fs)
    kx, ky = np.meshgrid(kx, ky)
    k = np.sqrt(kx**2 + ky**2)
    mask = k > (1/3)*(fs)
    x = np.fft.fft2(x)
    x[mask] = 0
    x = np.fft.ifft2(x)
    return x


psi = importdata('psi_re.txt') + 1j*importdata('psi_im.txt')
H0 = importdata('H0_re.txt') + 1j*importdata('H0_im.txt')
# psi = np.fft.fft2( np.fft.ifft2(psi) * H0 )
# psi = np.abs(psi)**2
print(np.min(np.abs(psi)**2), np.max(np.abs(psi)**2))
plt.imshow(np.abs(psi)**2,'gray')
plt.colorbar()
plt.show()
chi =importdata('chi.txt') 

dim = 512


# ****pass through lens****
s1,s2 = psi.shape
kx = np.fft.fftfreq(s1, 1/(dim/50))
ky = np.fft.fftfreq(s2, 1/(dim/50))
print(max(kx), max(ky))
kx, ky = np.meshgrid(kx, ky)
k2 = kx**2 + ky**2

alphamax = 10.37 * 1e-3 # rad
deltaf =  700 # Ang
Cs = 1.3 * 1e7    # Ang


lam = 1/39.87345849884623
gamma = 1.39139023969897

A = np.zeros(psi.shape)
mask = lam * np.sqrt(k2) < alphamax
A[mask] = 1
# chi = np.pi * lam * k2 * (.5 * Cs * lam**2 * k2 - deltaf)
# H0 = (np.cos(-chi) - 1j*np.sin(chi))* A


psi = np.fft.fft2( np.fft.ifft2(psi) * H0 )
print(np.min(np.abs(psi)**2), np.max(np.abs(psi)**2))
print(sum(sum(intensity:=np.abs(psi)**2)/(dim**2)))
plt.imshow(intensity, 'gray')
plt.colorbar()
plt.show()



# plt.imshow(np.real(np.fft.fftshift(H0)).astype(float),'gray')
# plt.colorbar()
# plt.show()

# # fig 5.12
# intensity = np.abs(psi)**2
# print(sum(sum(intensity)) / (dim)**2)
# plt.imshow(intensity.astype(float),'gray')
# plt.colorbar()
# plt.savefig('Fig 5.12.jpg')
# # plt.show()

"""
# transmission function test as calculated from c++ program to produce fig 5.11 of kirkland
t_re_u = importdata('t_re.txt')
t_im_u = importdata('t_im.txt')
tre_line = (t_re_u)[int(dim/2),:]
tim_line = (t_im_u)[int(dim/2),:]
r = np.linspace(0,50,dim)
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
"""
# *************** start transmission function ***************

# c = importdata('c.txt', 25, 5)
# si = importdata('si.txt', 25, 15)
# cu = importdata('cu.txt', 25, 25)
# au = importdata('au.txt', 25, 35)
# u = importdata('u.txt', 25, 45)
# v = c+si+cu+au+u
# lam = 1/39.87345849884623
# gamma = 1.39139023969897
# v= np.real(v)*lam* gamma / (50*50)
# t = np.exp(1j * v)
# # t = importdata('t_re_u.txt') + 1j*importdata('t_im_u.txt')
# t = bw_limit(t)
# # pp(np.real(t))
# t = t[int(dim/2),:]
# tre_line = (np.real(t))
# tim_line = (np.imag(t))
# r = np.linspace(0,50,dim)
# plt.subplot(2,1,1)
# plt.title('Fig. 5.11 of Kirkland')
# plt.plot(r,(tre_line))
# plt.ylabel('Real Part')
# plt.subplot(2,1,2)
# plt.ylim([0,1.2])
# plt.plot(r,(tim_line))
# plt.ylabel('Imag. Part')
# plt.xlabel('position x (in Ang.)')
# plt.ylim([0,1])
# # plt.savefig('Fig 5.11.jpg')
# plt.show()


"""
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