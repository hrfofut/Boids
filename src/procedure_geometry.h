#ifndef PROCEDURE_GEOMETRY_H
#define PROCEDURE_GEOMETRY_H

#include <vector>
#include <glm/glm.hpp>

class LineMesh;

void create_boid_shape(std::vector<glm::vec4>& boid_shape_vertices, std::vector<glm::uvec3>& boid_shape_faces);
void create_food_shape(std::vector<glm::vec4>& obj_vertices, std::vector<glm::uvec3>& obj_faces);
void create_cylinder(std::vector<glm::vec4>& cylinder_vertices, std::vector<glm::uvec2>& cylinder_faces);
void create_sphere(std::vector<glm::vec4>& sphere_vertices, std::vector<glm::uvec2>& sphere_faces);


#endif
