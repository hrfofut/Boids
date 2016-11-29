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
const std::string window_title = "Skinning";

const char* vertex_shader =
#include "shaders/default.vert"
;

const char* boid_shader =
#include "shaders/boid.vert"
;

const char* fragment_shader =
#include "shaders/default.frag"
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

	glm::vec4 light_position = glm::vec4(0.0f, 100.0f, 0.0f, 1.0f);
	MatrixPointers mats; // Define MatrixPointers here for lambda to capture

    Flock flock;
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

	ShaderUniform std_model = { "model", matrix_binder, std_model_data };
	ShaderUniform std_view = { "view", matrix_binder, std_view_data };
	ShaderUniform std_camera = { "camera_position", vector3_binder, std_camera_data };
	ShaderUniform std_proj = { "projection", matrix_binder, std_proj_data };
	ShaderUniform std_light = { "light_position", vector_binder, std_light_data };
    ShaderUniform std_boid_translate = { "boid_translate", matrix_binder, std_boid_translate_data};
    ShaderUniform std_boid_rotate = { "boid_rotate", matrix_binder, std_boid_rotate_data};
    ShaderUniform std_boid_color = { "boid_color", vector3_binder, std_boid_color_data};
    
	RenderDataInput boid_shape_pass_input;
	boid_shape_pass_input.assign(0, "vertex_position", boid_shape_vertices.data(), boid_shape_vertices.size(), 4, GL_FLOAT);
	boid_shape_pass_input.assign_index(boid_shape_faces.data(), boid_shape_faces.size(), 3);
	RenderPass boid_shape_pass(-1,
			boid_shape_pass_input,
			{ boid_shader, nullptr, fragment_shader},
			{ std_model, std_view, std_proj, std_light,
              std_boid_translate, std_boid_rotate, std_boid_color},
			{ "fragment_color" }
			);
	float aspect = 0.0f;

	bool draw_boids = true;
    bool draw_obstacle = false;

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

		gui.updateMatrices();
		mats = gui.getMatrixPointers();

        if (draw_boids) {
            for (auto it = flock.boids.begin(); it != flock.boids.end(); ++it) {
                boid_translate = glm::mat4(1);
                boid_translate[3] = it->pos;
                glm::vec4 boid_velocity = it->vel;
                glm::vec4 up = glm::vec4(0, 1, 0, 0);
                if (glm::length(boid_velocity) == 0)
                    boid_rotate = glm::mat4(1.0);
                else
                {
                    boid_velocity = glm::normalize(boid_velocity);
                    boid_rotate = glm::rotate(glm::angle( up , boid_velocity), // TODO:: 3d change rotation axis
                                            glm::cross(glm::vec3(up), glm::vec3(boid_velocity)));
                }
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
#if 0
	for (size_t i = 0; i < images.size(); ++i)
		delete [] images[i].bytes;
#endif
	exit(EXIT_SUCCESS);
}
