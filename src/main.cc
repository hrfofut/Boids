#include <GL/glew.h>

#include "procedure_geometry.h"
#include "render_pass.h"
#include "gui.h"
#include "Flock.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <debuggl.h>

int window_width = 800, window_height = 600;
const std::string window_title = "Boids!";

const char* vertex_shader =
#include "shaders/default.vert"
;

const char* boid_vertex_shader =
#include "shaders/boid.vert"
;

const char* food_vertex_shader =
#include "shaders/food.vert"
;

const char* cylinder_vertex_shader =
#include "shaders/cylinder.vert"
;

const char* fragment_shader =
#include "shaders/default.frag"
;

const char* boid_fragment_shader =
#include "shaders/boid.frag"
;

const char* food_fragment_shader =
#include "shaders/food.frag"
;

const char* cylinder_fragment_shader =
#include "shaders/cylinder.frag"
;

void ErrorCallback(int error, const char* description) {
	std::cerr << "GLFW Error: " << description << "\n";
}

GLFWwindow* init_glefw()
{
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwSetErrorCallback(ErrorCallback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	auto ret = glfwCreateWindow(window_width, window_height, window_title.data(), nullptr, nullptr);
	CHECK_SUCCESS(ret != nullptr);
	glfwMakeContextCurrent(ret);
	glewExperimental = GL_TRUE;
	CHECK_SUCCESS(glewInit() == GLEW_OK);
	glGetError();  // clear GLEW's error for it
	glfwSwapInterval(1);
	const GLubyte* renderer = glGetString(GL_RENDERER);  // get renderer string
	const GLubyte* version = glGetString(GL_VERSION);    // version as a string
	std::cout << "Renderer: " << renderer << "\n";
	std::cout << "OpenGL version supported:" << version << "\n";

	return ret;
}

int main(int argc, char* argv[])
{
	GLFWwindow *window = init_glefw();
	GUI gui(window);

	std::vector<glm::vec4> boid_shape_vertices;
	std::vector<glm::uvec3> boid_shape_faces;
	create_boid_shape(boid_shape_vertices, boid_shape_faces);
    glm::mat4 boid_translate;
    glm::mat4 boid_rotate;
    glm::vec3 boid_color;

    std::vector<glm::vec4> food_shape_vertices;
    std::vector<glm::uvec3> food_shape_faces;
    create_food_shape(food_shape_vertices, food_shape_faces);
    glm::mat4 food_translate = glm::mat4(1);
    glm::vec3 food_color;

    std::vector<glm::vec4> cylinder_vertices;
    std::vector<glm::uvec2> cylinder_faces;
    create_cylinder(cylinder_vertices, cylinder_faces);
    glm::mat4 t = glm::mat4(1);
    glm::mat4 r = glm::mat4(1);
    float s = 10;
    float radius = kCylinderRadius;

    glm::vec4 light_position = glm::vec4(0.0f, 100.0f, 0.0f, 1.0f);
	MatrixPointers mats; // Define MatrixPointers here for lambda to capture

    Flock flock;
    World world;
    flock.world = &world;
    flock.generate_boids();
	/*
	 * In the following we are going to define several lambda functions to bind Uniforms.
	 * 
	 * Introduction about lambda functions:
	 *      http://en.cppreference.com/w/cpp/language/lambda
	 *      http://www.stroustrup.com/C++11FAQ.html#lambda
	 */
	auto matrix_binder = [](int loc, const void* data) {
		glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat*)data);
	};
	auto vector_binder = [](int loc, const void* data) {
		glUniform4fv(loc, 1, (const GLfloat*)data);
	};
	auto vector3_binder = [](int loc, const void* data) {
		glUniform3fv(loc, 1, (const GLfloat*)data);
	};
	auto float_binder = [](int loc, const void* data) {
		glUniform1fv(loc, 1, (const GLfloat*)data);
	};
	/*
	 * These lambda functions below are used to retrieve data
	 */
	auto std_model_data = [&mats]() -> const void* {

		return mats.model;
	}; // This returns point to model matrix
	glm::mat4 boid_shape_model_matrix = glm::mat4(1.0f);
	auto boid_shape_model_data = [&boid_shape_model_matrix]() -> const void* {
		return &boid_shape_model_matrix[0][0];
	}; // This return model matrix for the floor.
	auto std_view_data = [&mats]() -> const void* {
		return mats.view;
	};
	auto std_camera_data  = [&gui]() -> const void* {
		return &gui.getCamera()[0];
	};
	auto std_proj_data = [&mats]() -> const void* {
		return mats.projection;
	};
	auto std_light_data = [&light_position]() -> const void* {
		return &light_position[0];
	};
    auto std_boid_translate_data = [&boid_translate]() -> const void* {
        return &boid_translate[0][0];
    };
    auto std_boid_rotate_data = [&boid_rotate]() -> const void* {
        return &boid_rotate[0][0];
    };
    auto std_boid_color_data = [&boid_color]() -> const void* {
        return &boid_color;
    };
    auto std_food_translate_data = [&food_translate]() -> const void* {
        return &food_translate[0][0];
    };
    auto std_food_color_data = [&food_color]() -> const void* {
        return &food_color;
    };
    auto std_translate_data = [&t]() -> const void* {
        return &t[0][0];
    };
    auto std_rotate_data = [&r]() -> const void* {
        return &r[0][0];
    };
    auto std_scalar_data = [&s]() -> const void* {
        return &s;
    };
    auto std_radius_data = [&radius]() -> const void* {
        return &radius;
    };

	ShaderUniform std_model = { "model", matrix_binder, std_model_data };
	ShaderUniform std_view = { "view", matrix_binder, std_view_data };
	ShaderUniform std_camera = { "camera_position", vector3_binder, std_camera_data };
	ShaderUniform std_proj = { "projection", matrix_binder, std_proj_data };
	ShaderUniform std_light = { "light_position", vector_binder, std_light_data };
    ShaderUniform std_boid_translate = { "boid_translate", matrix_binder, std_boid_translate_data};
    ShaderUniform std_boid_rotate = { "boid_rotate", matrix_binder, std_boid_rotate_data};
    ShaderUniform std_boid_color = { "boid_color", vector3_binder, std_boid_color_data};
    ShaderUniform std_food_translate = { "food_translate", matrix_binder, std_food_translate_data};
    ShaderUniform std_food_color = { "food_color", vector3_binder, std_food_color_data};
    ShaderUniform std_translate = { "translate", matrix_binder, std_translate_data};
    ShaderUniform std_rotate = { "rotate", matrix_binder, std_rotate_data};
    ShaderUniform std_scalar = { "scalar", float_binder, std_scalar_data};
    ShaderUniform std_radius = { "radius", float_binder, std_radius_data};

    RenderDataInput boid_shape_pass_input;
	boid_shape_pass_input.assign(0, "vertex_position", boid_shape_vertices.data(), boid_shape_vertices.size(), 4, GL_FLOAT);
	boid_shape_pass_input.assign_index(boid_shape_faces.data(), boid_shape_faces.size(), 3);
	RenderPass boid_shape_pass(-1,
			boid_shape_pass_input,
			{ boid_vertex_shader, nullptr, boid_fragment_shader},
			{ std_model, std_view, std_proj, std_light,
              std_boid_translate, std_boid_rotate, std_boid_color},
			{ "fragment_color" }
			);

    RenderDataInput food_shape_pass_input;
    food_shape_pass_input.assign(0, "vertex_position", food_shape_vertices.data(), food_shape_vertices.size(), 4, GL_FLOAT);
    food_shape_pass_input.assign_index(food_shape_faces.data(), food_shape_faces.size(), 3);
    RenderPass food_shape_pass(-1,
                               food_shape_pass_input,
                               { food_vertex_shader, nullptr, food_fragment_shader},
                               { std_model, std_view, std_proj, std_light,
                                 std_food_translate, std_food_color},
                               { "fragment_color" }
    );

    RenderDataInput cylinder_pass_input;
    cylinder_pass_input.assign(0, "vertex_position", cylinder_vertices.data(), cylinder_vertices.size(), 4, GL_FLOAT);
    cylinder_pass_input.assign_index(cylinder_faces.data(), cylinder_faces.size(), 2);
    RenderPass cylinder_pass(-1,
                             cylinder_pass_input,
                             {
                                 cylinder_vertex_shader,
                                 nullptr,
                                 cylinder_fragment_shader
                             },
                             { std_model, std_view, std_proj,
                               std_light, std_camera,
                               std_translate, std_rotate, std_scalar, std_radius },
                             { "fragment_color" }
    );

    float aspect = 0.0f;
    bool draw_boids = true;
    bool draw_obstacle = false;
    int frameCount = 0;
	while (!glfwWindowShouldClose(window)) {
		// Setup some basic window stuff.
		glfwGetFramebufferSize(window, &window_width, &window_height);
		glViewport(0, 0, window_width, window_height);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);
		glEnable(GL_CULL_FACE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LESS);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glCullFace(GL_BACK);

        if(!(frameCount %= 2))
        {
            if(!gui.paused)
                flock.fly();
            gui.cameraFollow(flock.n_center);
        }
        gui.updateMatrices();
        mats = gui.getMatrixPointers();

        food_translate = flock.food.get_translate();
        food_color = flock.food.col;
        food_shape_pass.setup();
        CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, food_shape_faces.size() * 3, GL_UNSIGNED_INT, 0));

        for (auto it = flock.obstacles.begin(); it != flock.obstacles.end(); ++it) {
            t = (*it)->get_translate();
            r = (*it)->get_rotation();
            s = (*it)->radius;
            cylinder_pass.setup();
            CHECK_GL_ERROR(
                glDrawElements(GL_LINES, cylinder_faces.size() * 2, GL_UNSIGNED_INT, 0));
        }

        frameCount++;
        if (draw_boids) {
            for (auto it = flock.boids.begin(); it != flock.boids.end(); ++it) {
                boid_translate = it->get_translate();
                boid_rotate = it->get_rotation();
                boid_color = it->col;
                boid_shape_pass.setup();
                CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, boid_shape_faces.size() * 3, GL_UNSIGNED_INT, 0));

            }
        }

        // Poll and swap.
        glfwPollEvents();
        glfwSwapBuffers(window);

	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
