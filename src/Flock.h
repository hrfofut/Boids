//
// Created by jfish7 on 11/28/16.
//

#ifndef GLSL_FLOCK_H
#define GLSL_FLOCK_H

#endif //GLSL_FLOCK_H
#include "gui.h"
#include "config.h"
#include "render_pass.h"


struct Boid {
    Boid(glm::vec4 position = glm::vec4(randFlo()*100 - 50,
                                        randFlo()*75 - 37.5, 0, 1),
         glm::vec4 velocity = glm::vec4(randFlo()*2 - 1.0 ,
                                        (randFlo())*2 - 1.0, 0, 0),
         glm::vec3 color = glm::vec3(randFlo(),
                                     randFlo(),
                                     randFlo()));
    glm::mat4 get_translate();
    glm::mat4 get_rotation();

    glm::vec4 pos;      //Position Vec
    glm::vec4 vel;      //Velocity Vec
    glm::vec3 col;      //Color of individual boid

    //spatial structure info
//    Boid* prev; //in the list structure, the previous one. null if it's the first element
//    Boid* next; //null if this is the last in list

    int id;
};

struct Food {
    Food(glm::vec4 position = glm::vec4(randFlo()*100-50,
                                        randFlo()*100-50,
                                        randFlo()*100-50, 1),
         glm::vec3 color = glm::vec3(1, 0, 0));
    void reposition();

    glm::mat4 get_translate();
    glm::vec4 pos;
    glm::vec3 col;
    bool eaten = false;
};

struct Obstacle {
    virtual bool intersects(const Boid& boid, glm::vec4& vel_temp, bool &hit) = 0;
    virtual bool inside(const glm::vec4& position) = 0;
    void render();

    glm::mat4 get_transform();
    glm::mat4 get_translate();
    glm::mat4 get_rotation();
    glm::vec4 pos;
    glm::vec4 rot;
    glm::vec3 col = glm::vec3(randFlo(), randFlo(), randFlo());
    float radius = kCylinderRadius;
    float scale;
    RenderPass* renderPass;
    std::vector<glm::uvec2>* faces;
};

struct Cylinder : public Obstacle {
    Cylinder(glm::vec4 position = glm::vec4(randFlo()*100 - 50,
                                            randFlo()*75 - 37.5, 0, 1),
            glm::vec4 rotation = glm::vec4(randFlo(), randFlo(), randFlo(), 0));
    bool intersects(const Boid& boid, glm::vec4& vel_temp, bool &hit);
    bool inside(const glm::vec4& position);
    float length = 1000;
};

struct Sphere : public Obstacle {
    Sphere(glm::vec4 position = glm::vec4(randFlo()*100 - 50,
                                          randFlo()*75 - 37.5,
                                          randFlo()*75 - 37.5, 1),
           glm::vec4 rotation = glm::vec4(randFlo(), randFlo(), randFlo(), 0));
    bool intersects(const Boid& boid, glm::vec4& vel_temp, bool &hit);
    bool inside(const glm::vec4& position);
};

struct World {
    Boid* subCubes[50][50][50]; // later, replace 50 with worldSize / boidRadius, cast to an int.
};

struct Flock {
    Flock();
    glm::vec4 center;   //Center of Mass for all Boids in Flock
    glm::vec4 n_center;   //NEW! Center of Mass for all Boids in Flock
    std::vector<Boid> boids; //Vector contianing all boids
    void generate_cylinders(RenderPass& renderPass, std::vector<glm::uvec2>& faces, int num);
    void generate_spheres(RenderPass& renderPass, std::vector<glm::uvec2>& faces, int num);
    void generate_boids();
    void add_boid();
    void add_food(int numFood);
    void remove_food(int numFood);
    void fly();
    glm::vec4 seperation(Boid& boid);
    glm::vec4 alignment(Boid& boid);
    glm::vec4 cohesion(Boid& boid);
    glm::vec4 follow(Boid& boid);
    glm::vec4 hungry(Boid& boid);

    World* world;
    std::vector<Obstacle*> obstacles;
    std::vector<Food> food;
    private:
    int num_boids = start_boids;
};

