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

void create_cylinder(std::vector<glm::vec4>& cylinder_vertices, std::vector<glm::uvec2>& cylinder_faces) {
    int i = 0;
    // Create vertical lines.
    for (float j = 0; j < M_PI * 2; j += (M_PI * 2)/12.0) {
        // Create horizontal lines
        for (float k = -0.5; k <= 0.5; k += 1/CylinderMeshLines) {
            cylinder_vertices.push_back(glm::vec4(j, k, 0.0f, 1.0f));
            cylinder_vertices.push_back(glm::vec4(j + ((M_PI * 2)/12.0), k, 0.0f, 1.0f));
            cylinder_faces.push_back(glm::uvec2(i, i+1)); i+=2;
        }
        cylinder_vertices.push_back(glm::vec4(j, -0.5f, 0.0f, 1.0f));
        cylinder_vertices.push_back(glm::vec4(j, 0.5f, 0.0f, 1.0f));
        cylinder_faces.push_back(glm::uvec2(i, i+1)); i+=2;
    }
}

void create_sphere(std::vector<glm::vec4>& sphere_vertices, std::vector<glm::uvec2>& sphere_faces) {
    int i = 0;
    // Create vertical lines.
    for (float j = 0; j < M_PI * 2; j += (M_PI * 2)/10.0) {
        // Create horizontal lines
        for (float k = -M_PI; k < M_PI; k += (M_PI * 2)/10.0) {
            sphere_vertices.push_back(glm::vec4(j, k, 0.0f, 1.0f));
            sphere_vertices.push_back(glm::vec4(j + ((M_PI * 2)/10.0), k, 0.0f, 1.0f));
            sphere_faces.push_back(glm::uvec2(i, i+1)); i+=2;
        }
        sphere_vertices.push_back(glm::vec4(j, 0.0f, 0.0f, 1.0f));
        sphere_vertices.push_back(glm::vec4(j, 1.0f, 0.0f, 1.0f));
        sphere_faces.push_back(glm::uvec2(i, i+1)); i+=2;
    }
}