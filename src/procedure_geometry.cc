#include "procedure_geometry.h"
#include "config.h"

void create_boid_shape(std::vector<glm::vec4>& boid_shape_vertices, std::vector<glm::uvec3>& boid_shape_faces)
{
	boid_shape_vertices.push_back(glm::vec4(0, 0, 0, 1));
    boid_shape_vertices.push_back(glm::vec4(1, -1, 0, 1));
    boid_shape_vertices.push_back(glm::vec4(0, 2, 0, 1));
    boid_shape_vertices.push_back(glm::vec4(-1, -1, 0, 1));
    boid_shape_faces.push_back(glm::uvec3(0,1,2));
    boid_shape_faces.push_back(glm::uvec3(0,2,3));
}