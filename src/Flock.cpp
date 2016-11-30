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
    next = NULL; //The pointers should go to nothing
    prev = NULL;
    
}

void Flock::generate_boids(){
    srand(time(NULL));
    for(int i = 0; i < num_boids; ++i) {
        Boid b;
	//Check if the world
	int x = (((int)b.pos.x)+50)/2; // The addition makes it range from 0 to 100, the division makes it from 0 to 50, so it will fit within the subdivision. TODO: Make it based on the constants in config.h
	int y = (((int)b.pos.y)+50)/2;
	int z = (((int)b.pos.z)+50)/2;
	if((*world).subCubes[x][y][z]) //The intent of this is to check if a pointer already exists.
	  {
	    b.next = (*world).subCubes[x][y][z]; //dont forget about the currently existing one
	    (*b.next).prev = &b; //make it point to new one
	    (*world).subCubes[x][y][z] = &b;
	  }
	else
	  (*world).subCubes[x][y][z] = &b; //If there isn't aready a pointer in the structure, we just need to assign the new one.
        boids.push_back(b);      //Randomly generate a boid
        center += boids[i].pos;
	
        printf("%f %f %f\n", b.pos.x, b.pos.y, b.pos.z);
        printf("%f %f %f\n", b.vel.x, b.vel.y, b.vel.z);
    }
    center /= num_boids;
}

/*
Add a function that iterates through the list of Boids in Flock, velocity to the position (if that new position is within world space,
Changes the subCube if it needs to be changed, then calculates new velocity.
To change the subCube, if prev is null, then we need to change the parent subCube's pointer to the current next.
We also need to change the current next's prev to null, since it will be the new first element.


 */
