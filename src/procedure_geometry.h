#ifndef PROCEDURE_GEOMETRY_H
#define PROCEDURE_GEOMETRY_H

#include <vector>
#include <glm/glm.hpp>

class LineMesh;

void create_boid_shape(std::vector<glm::vec4>& boid_shape_vertices, std::vector<glm::uvec3>& boid_shape_faces);
// FIXME: Add functions to generate the bone mesh.

#endif
