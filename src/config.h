#ifndef CONFIG_H
#define CONFIG_H

/*
 * Global variables go here.
 */

const float kCylinderRadius = 10.0;
const float CylinderMeshLines = 100.0;
const float SphereMeshLines = 10.0;
/*
 * Extra credit: what would happen if you set kNear to 1e-5? How to solve it?
 */
const float kNear = 0.1f;
const float kFar = 1000.0f;
const float kFov = 45.0f;

// Floor info.
const float kFloorEps = 0.5 * (0.025 + 0.0175);
const float kFloorXMin = -100.0f;
const float kFloorXMax = 100.0f;
const float kFloorZMin = -100.0f;
const float kFloorZMax = 100.0f;
const float kFloorY = -0.75617 - kFloorEps;
//World Space info
const float worldSize = 100.0; //The length of the side of the space boids are allowed to go. This means max X, max Y, and max Z should be half of this

const float boidVision = 9.0; //distance the boids can look away.
const float seperationDistance = 4.0;

const float seperationFactor = 0.1;
const float alignmentFactor = 0.02;
const float cohesionFactor = 0.01;
const float avoidanceFactor = 0.1;

const float eatingDistance = 2.0;
const float eatingAngle = 0.1f;
const float hungryFactor = 0.15;

const float distanceLimit = 25.0;

const float vlimit = 1.25;
const float camera_default = 150.0;

static int nextID = 0;
const int start_boids = 3;
const int max_boids = 999;

const int numCylinders = 2;
const int numSpheres = 4;

const int startFood = 1;

static float randFlo(){
    return (rand() / static_cast <float> (RAND_MAX));
}
#endif
