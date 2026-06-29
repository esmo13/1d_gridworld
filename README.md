# 1d_gridworld
The simplest version of gridworld modeled in C++ with solution using bellman equation for Q-Learning


This project uses the Conda package manager for dependency resolution and build automation.

To build conda package use
```
conda create -n builder conda-build -c conda-forge -y
conda activate builder
conda build recipe/ -c conda-forge
```
To install run
```
conda install <path to .conda file> -c conda-forge
```
To install directly from Anaconda you can run
```
conda install esmo13::1d_gridworld
```