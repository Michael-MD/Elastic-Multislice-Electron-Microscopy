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
