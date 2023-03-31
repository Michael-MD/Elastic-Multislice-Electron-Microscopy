# Electron-Microscopy-in-C
Simulation of elastic scattering in electron microscopy using the multislice algorithm. Simulations include various STEM and TEM techniques such as ADFSTEM, BFSTEM, ABFSTEM and CoM.

This code base simulates various techniques from electron microscopy. 
The code is written with readability in mind rather for ease of understanding rather than speed.

## Theory
The theory introduced here summarizes the key results of elastic scattering in electron microscopy. Further details can be found in 
Advanced computing in electron microscopy by Earl J. Kirkland which has become the go-to for an introduction to the field.

In electron microscopy, information about the strucutre and constituants of a specimen is inferred by observing the scattering and diffraction of
electrons. Although the incident electrons have energies on the order of 10keV-100keV, the Schrödinger equation is employed with a relativistically 
corrected mass, wavelength and energy.
Given a specimen with potential V(r), the Schrodinger equation reads

$$  -\frac{\hbar^2}{2m} \nabla^2 \Psi - e V(r) \Psi = i\hbar \frac{\partial \Psi}{\partial t} $$

where $m=\gamma m_0$. If we consider energy eigentates with a time-independent hamiltonian, then we obtain the Helmholtz equation

$$ [\nabla^2 + 4 \pi k^2 + 4 \pi U ] \Psi = 0 $$

where $k^2 = \frac{2m e}{h^2}E$ and $U = \frac{2m e}{h^2}V$. Assuming a solution of the form $\Psi = \exp(i 2\pi k z) \psi$ and applying the paraxial approximation this simplifies to

$$ \frac{d\psi}{dz} = \frac{i}{4\pi k} [\nabla_\perp^2 + 4\pi^2 U] \psi  $$

with formal operator solution given by

$$ \psi(r_\perp, \Delta z) = e^{\mathcal{Q} z} \psi(r_\perp, 0)  $$ 

where $\mathcal{Q} = \frac{i}{4\pi k} [\nabla_\perp^2 + 4\pi^2 U_c]$ if $\Delta z$ is small. Here 

$$  U_c(r_\perp) = \int_0^{\Delta z} dz U(r_\perp,z) $$

and is refered to as the projected potential.
Since $\Delta z$ is taken to be small, 

$$ e^{\mathcal Q \Delta z} = e^{(\mathcal T + \mathcal U) \Delta z} = e^{\mathcal T \Delta z} e^{\mathcal U \Delta z} + \mathcal{O}(\Delta z ^2) $$

Now if $\mathcal U = 0$, then the angular spectrum formulation applies to our problem and we may identify the $e^{\mathcal T \Delta z}$ as  the free-space propagotor. So we may propagate the wave function through the specimen through repeted applicaiton of these operators until the wave function is at the exit of the specimen. Mathematically, this may be written as 

$$ \psi(r_\perp, z) = \prod \mathcal F^{-1} \{ P(k_\perp, \Delta z) \mathcal F\{ e^{\mathcal U \Delta z} \psi(r_\perp, 0) \} \} $$

where $P(k_\perp, \Delta z)$ is the free-space propagator in reciprical space. The approach is referred to as the multislice approach and is the method used here.

The techniques of electron microscopy can be catigoriezed into two primary modes. HR-TEM (High-Resolution Transmission Electron Microscopy) which uses incident place waves and STEM (Scanning Transmission Electron Mircsocopy) which uses
a converged probe which scans across the specimenn surface.

In STEM, for each probe position, a diffraction pattern is obtained, the detector which measures the intensity pattern 
consitiues the various STEM techniques. The recorded signal at a given probe position is given by

$$ g(k) = \int dk |I(k)|^2 D(k) $$

where $D(k)$ is the detector geometry. For instance, ADFSTEM (Annular-Dark-Field STEM) collects electrons which scatter at high
angles.

## Usage
To image a particular material, a .xyz file containing the crystal atomic species and locations for a single unit cell and placed in the structure directory.
This can then be loaded into the program by specifying the file name in the constructor of the technique of interest. The available techqnies have the following headers:
```
ADFSTEM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float alpha_min_D, float alpha_max_D)
    
ABFSTEM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float alpha_min_D, float alpha_max_D)
    
BFSTEM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, float alpha_max_D)
    
CSTEM(float E, int px, int py, int px_p, int py_p, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max)
    
HRTEM(float E, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
			float Cs, float deltaf, float alpha_max)
      
CoM(float E, int px_p, int py_p, int px, int py, int tx, int ty, int tz, string filename, vector<float> &s,
		float Cs, float deltaf, float alpha_max, bool CoM_dir_x)
```

New techniqes can be included by making a new class with the multislice class as parent and specifying the function which determines the detector. You may look at the wiki for details or simply look at one of the techniqes as a template.
