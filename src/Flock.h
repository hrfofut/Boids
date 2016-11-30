//
// Created by jfish7 on 11/28/16.
//

#ifndef GLSL_FLOCK_H
#define GLSL_FLOCK_H

#endif //GLSL_FLOCK_H
#include <vector>
#include "gui.h"
struct Boid {
    Boid(glm::vec4 position = glm::vec4((rand()) / static_cast <float> (RAND_MAX)*100 - 50,
                                        (rand()) / static_cast <float> (RAND_MAX)*75 - 37.5, 0, 1),
         glm::vec4 velocity = glm::vec4(((rand()) / static_cast <float> (RAND_MAX))*2 - 1.0 ,
                                        ((rand()) / static_cast <float> (RAND_MAX))*2 - 1.0, 0, 0),
         glm::vec3 color = glm::vec3((rand()) / static_cast <float> (RAND_MAX),
                                     (rand()) / static_cast <float> (RAND_MAX),
                                     (rand()) / static_cast <float> (RAND_MAX)));
    glm::vec4 pos;      //Position Vec
    glm::vec4 vel;      //Velocity Vec
    glm::vec3 col;      //Color of individual boid

    Boid* prev; //in the list structure, the previous one. null if it's the first element
    Boid* next; //null if this is the last in list

};

struct Flock {
    glm::vec4 center;   //Center of Mass for all Boids in Flock
    std::vector<Boid> boids; //Vector contianing all boids
    void generate_boids();
    World* world;
    private:
    int num_boids = 10;
};

struct World {
  Boid* subCubes[50][50][50] // later, replace 50 with worldSize / boidRadius, cast to an int. 
};
