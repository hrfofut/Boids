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

void create_food_shape(std::vector<glm::vec4>& obj_vertices, std::vector<glm::uvec3>& obj_faces) {
    int v =0;

    // Front Face
    obj_vertices.push_back(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f));
    obj_vertices.push_back(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f));
    obj_vertices.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(v, v+1, v+2));

    obj_vertices.push_back(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(v, v+2, v+3)); v+=4;

    // Right Face
    obj_vertices.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f));
    obj_vertices.push_back(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f));
    obj_vertices.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(v, v+1, v+2));

    obj_vertices.push_back(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(v, v+2, v+3)); v+=4;

    // Top Face
    obj_vertices.push_back(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f));
    obj_vertices.push_back(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f));
    obj_vertices.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(v, v+1, v+2));

    obj_vertices.push_back(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(v, v+2, v+3)); v+=4;

    // Left Face
    obj_vertices.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));
    obj_vertices.push_back(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f));
    obj_vertices.push_back(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(v, v+1, v+2));

    obj_vertices.push_back(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(v, v+2, v+3)); v+=4;

    // Back Face
    obj_vertices.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));
    obj_vertices.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f));
    obj_vertices.push_back(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(v, v+1, v+2));

    obj_vertices.push_back(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(v, v+2, v+3)); v+=4;

    // Bottom Face
    obj_vertices.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));
    obj_vertices.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f));
    obj_vertices.push_back(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(v, v+1, v+2));

    obj_vertices.push_back(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f));
    obj_faces.push_back(glm::uvec3(v, v+2, v+3)); v+=4;
}