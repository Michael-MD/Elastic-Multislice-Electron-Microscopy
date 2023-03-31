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

$$ [\nambla^2 + 4 \pi k^2 + 4 \pi U ] \Psi = 0 $$
where $ k^2 = \frac{2m e}{h^2}E $ and $ U = \frac{2m e}{h^2}V $. Assuming a solution of the form $ \Psi = \exp(i 2\pi k z) \psi $ and applying the paraxial approximation this simplifies to

$$ \frac{d\psi}{dz} = \frac{i}{4\pi k} [\nabla_\perp^2 + 4\pi^2 U] \psi  $$
with formal operator solution is given by

$$ \psi(r_\perp, \delta z) = e^{\mathcal{Q} z} \psi(r_\perp, 0)  $$ if $ \delta z $ is small where $ \mathcal{Q} = \frac{i}{4\pi k} [\nabla_\perp^2 + 4\pi^2 U_c]  $. Here 

$$  U_c = \int_0^{\delta z} dz U $$
and is refered to as the projected potential.
Since $ \deltz z $ is taken to be small, 

$$ e^{\mathcal Q \deltz z} = e^{(\mathcal T + \mathcal U) \deltz z} = e^{\mathcal T \delta z} e^{\mathcal U \delta z} + \mathcal{O}(\delta z ^2) $$
Now if $ \mathcal U = 0 $, then the angular spectrum formulation applies to our problem and we may identify the $ e^{\mathcal T \delta z} $ as  the free-space propagotor. So we may propagate the wave function through the specimen through repeted applicaiton of these operators until the wave function is at the exit of the specimen. Mathematically, this may be written as 

$$ \psi(r_\perp, z) = \prod \mathcal F^{-1} \{ P(k_\perp, delta z) \mathcal F\{ e^{\mathcal U \delta z} \psi(r_\perp, 0) \} \} $$
where $ P(k_\perp, delta z) $ is the free-space propagator in reciprical space. The approach is referred to as the multislice approach and is the approach used here.
