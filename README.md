# Getting Started

## Build

Building this project is Simple!
```
mkdir build
cd build
cmake ..
make -j8
```

## Execution

```
cd build
./bin/boids 
```

To change the skybox replace the current jpgs within assets with your own corresponding jpgs, using the same naming scheme.

## Notes about the boid code

There are many variables stored in config.h which, when altered, change everything from the sizes of the obstacles, to how boids flock together. Experimentation with different values will yield interesting results.

In particular, changing the various Factor floats will change how boids react to nearby boids.

## Controls

There are numerous keyboard controls that will allow you to alter the simulation at runtime.



# Acknowledgement 

This boid code is based on the skinning project written by
Randall Smith for 2015 Spring Graphics Course.