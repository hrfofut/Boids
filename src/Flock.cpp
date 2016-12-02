//
// Created by jfish7 on 11/28/16.
//
#include <stdio.h>
#include "Flock.h"
#include <ctime>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>


Boid::Boid(glm::vec4 position, glm::vec4 velocity, glm::vec3 color){
    pos = position;
    vel = glm::normalize(velocity);
    col = color;
    next = NULL; //The pointers should go to nothing
    prev = NULL;
    id = nextID++;
}

glm::mat4 Boid::get_translate() {
    glm::mat4 T = glm::mat4(1);
    T[3] = pos;
    return T;
}

glm::mat4 Boid::get_rotation() {
    glm::vec4 boid_velocity = vel;
    glm::vec4 up = glm::vec4(0, 1, 0, 0);
    if (glm::length(boid_velocity) == 0)
        return glm::mat4(1.0);
    else
    {
        boid_velocity = glm::normalize(boid_velocity);
//                    float angle = glm::angle( up , boid_velocity);
        float angle = acos(glm::dot(up, boid_velocity));
        glm::vec3 axis = glm::cross(glm::vec3(up), glm::vec3(boid_velocity));
        return glm::rotate(angle, axis);
        //glm::vec4 rotated = boid_rotate * up;
//                    printf("Rotating up by %f, across %f %f %f results to %f %f %f\n", angle, axis.x, axis.y, axis.z, rotated.x, rotated.y, rotated.z);
    }
}

Food::Food(glm::vec4 position, glm::vec3 color) {
    pos = position;
    col = color;
}

void Food::reposition() {
    //srand(time(NULL));
    pos = glm::vec4((rand()) / static_cast <float> (RAND_MAX)*100 - 50,
                    (rand()) / static_cast <float> (RAND_MAX)*75 - 37.5, 0, 1);
}

glm::mat4 Food::get_translate() {
    glm::mat4 T = glm::mat4(1);
    T[3] = pos;
    return T;
}

Flock::Flock() {
    srand(time(NULL));
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

//        printf("Boid #:%d\n", b.id);
//        printf("%f %f %f\n", b.pos.x, b.pos.y, b.pos.z);
//        printf("%f %f %f\n", b.vel.x, b.vel.y, b.vel.z);
    }
    center /= num_boids;
    center[3] = 1;
}

void Flock::add_boid() {
    srand(time(NULL));
    Boid b;
    boids.push_back(b);
}

/*
Add a function that iterates through the list of Boids in Flock, velocity to the position (if that new position is within world space,
Changes the subCube if it needs to be changed, then calculates new velocity.
To change the subCube, if prev is null, then we need to change the parent subCube's pointer to the current next.
We also need to change the current next's prev to null, since it will be the new first element.

 */

void Flock::fly() {
//    printf("%f %f %f\n", center.x, center.y, center.z );
    glm::vec4 new_center = glm::vec4(0,0,0,1);
    std::vector<glm::vec4> new_pos_vel;
    bool food_eaten = false;

    for (auto it = boids.begin(); it != boids.end(); ++it) {
        if (glm::distance(food.pos, it->pos) < eatingDistance)
            food_eaten = true;

        glm::vec4 v1 = seperation(*it);
//        printf("Vel: %f %f %f\n",v1.x,v1.y,v1.z);
        glm::vec4 v2 = alignment(*it);
//        printf("Vel: %f %f %f\n",v2.x,v2.y,v2.z);
        glm::vec4 v3 = cohesion(*it);
//        printf("Vel: %f %f %f\n",v3.x,v3.y,v3.z);
        glm::vec4 v4 = hungry(*it);

        glm::vec4 new_vel = it->vel + v1 + v2 + v3 + v4;
        new_vel[3] = 0;
//        printf("Vel: %f %f %f\n",it->vel.x,it->vel.y,it->vel.z);
        if(glm::length(new_vel) > vlimit )
            new_vel = glm::normalize(new_vel) * vlimit;
        glm::vec4 new_pos = it->pos + new_vel;
        new_pos_vel.push_back(new_pos);
        new_pos_vel.push_back(new_vel);
//        printf("Pos: %f %f %f\n",it->pos.x,it->pos.y,it->pos.z);
        new_center += new_pos;
    }
    for (unsigned int i = 0; i<boids.size(); ++i) {
        boids[i].pos = new_pos_vel[2*i];
        boids[i].vel = new_pos_vel[2*i + 1];
    }
    center = new_center / (float)boids.size();
    center[3] = 1;

    if (food_eaten) {
        food.reposition();
        add_boid();
    }
}

glm::vec4 Flock::seperation(Boid& boid) {
    glm::vec4 v = glm::vec4(0);
    int count = 0;
    for (auto it = boids.begin(); it != boids.end(); ++it) {
        if (boid.id != it->id && glm::distance(boid.pos, it->pos) < seperationDistance) {

            float sepScale = seperationDistance - glm::distance(it->pos, boid.pos);
            sepScale *= sepScale;
            v = v - sepScale * (it->pos - boid.pos);
            ++count;
        }
    }
    v[3] = 0;
    if(count) {
        v /= count;
        v = glm::normalize(v);
    }
    return v * seperationFactor;
}

glm::vec4 Flock::alignment(Boid& boid) {
    glm::vec4 v = glm::vec4(0);
    int count = 0;
    for (auto it = boids.begin(); it != boids.end(); ++it) {
        if (boid.id != it->id && glm::distance(boid.pos, it->pos) < boidVision) {
            v = v + (it->vel);
            ++count;
        }
    }
    v[3] = 0;
    if(count)
        v /= count;
    return v * alignmentFactor;
}

glm::vec4 Flock::cohesion(Boid& boid) {
    glm::vec4 v = glm::vec4(0);
    int count = 0;
    for (auto it = boids.begin(); it != boids.end(); ++it) {
        if (boid.id != it->id && glm::distance(boid.pos, it->pos) < boidVision) {
            v = v + (it->pos);
            ++count;
        }
    }
    if(count)
        v /= count;
//    glm::vec4 center_v = (center - boid.pos);
//    center_v[3] = 0;
//    if(glm::length(center_v) >= distanceLimit)
//        return center_v*cohesionFactor;
    if(count)
        v = (v - boid.pos) * cohesionFactor;
//    if (count)
//        v+= (center_v * cohesionFactor)/(float)count;
    v[3] = 0;
    return v;
}

glm::vec4 Flock::hungry(Boid& boid) {
    glm::vec4 v = glm::normalize(food.pos - boid.pos);
    if (glm::angle(boid.vel, v) < 0.1f)
        v = glm::vec4(0, 0, 0, 0);
    return v * hungryFactor;
}
