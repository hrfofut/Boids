//
// Created by jfish7 on 11/28/16.
//
#include <stdio.h>
#include "Flock.h"
#include <ctime>

Boid::Boid(glm::vec4 position, glm::vec4 velocity, glm::vec3 color){
    pos = position;
    vel = glm::normalize(velocity);
    col = color;
}

void Flock::generate_boids(){
    srand(time(NULL));
    for(int i = 0; i < num_boids; ++i) {
        Boid b;
        boids.push_back(b);      //Randomly generate a boid
        center += boids[i].pos;
        printf("%f %f %f\n", b.pos.x, b.pos.y, b.pos.z);
        printf("%f %f %f\n", b.vel.x, b.vel.y, b.vel.z);
    }
    center /= num_boids;
}