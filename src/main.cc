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

const char* sphere_vertex_shader =
#include "shaders/sphere.vert"
;

const char* cubemap_vertex_shader =
#include "shaders/cubemap.vert"
;

const char* fragment_shader =
#include "shaders/default.frag"
;

const char* object_shader =
#include "shaders/object.frag"
;

const char* cubemap_fragment_shader =
#include "shaders/cubemap.frag"
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

    std::vector<glm::vec4> food_shape_vertices;
    std::vector<glm::uvec3> food_shape_faces;
    create_food_shape(food_shape_vertices, food_shape_faces);

    std::vector<glm::vec4> cylinder_vertices;
    std::vector<glm::uvec2> cylinder_faces;
    create_cylinder(cylinder_vertices, cylinder_faces);

    std::vector<glm::vec4> sphere_vertices;
    std::vector<glm::uvec2> sphere_faces;
    create_sphere(sphere_vertices, sphere_faces);

    glm::mat4 T = glm::mat4(1);
    glm::mat4 R = glm::mat4(1);
    glm::vec3 color;
    float scale = 0;
    float radius = kRadius;

    glm::vec4 light_position = glm::vec4(0.0f, 100.0f, 0.0f, 1.0f);
	MatrixPointers mats; // Define MatrixPointers here for lambda to capture

    Flock flock;
    World world;
    flock.world = &world;
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
    auto std_translate_data = [&T]() -> const void* {
        return &T[0][0];
    };
    auto std_rotate_data = [&R]() -> const void* {
        return &R[0][0];
    };
    auto std_color_data = [&color]() -> const void* {
        return &color;
    };
    auto std_scalar_data = [&scale]() -> const void* {
        return &scale;
    };
    auto std_radius_data = [&radius]() -> const void* {
        return &radius;
    };

	ShaderUniform std_model = { "model", matrix_binder, std_model_data };
	ShaderUniform std_view = { "view", matrix_binder, std_view_data };
	ShaderUniform std_camera = { "camera_position", vector3_binder, std_camera_data };
	ShaderUniform std_proj = { "projection", matrix_binder, std_proj_data };
	ShaderUniform std_light = { "light_position", vector_binder, std_light_data };
    ShaderUniform std_translate = { "translate", matrix_binder, std_translate_data};
    ShaderUniform std_rotate = { "rotate", matrix_binder, std_rotate_data};
    ShaderUniform std_color = { "color", vector3_binder, std_color_data};
    ShaderUniform std_scalar = { "scalar", float_binder, std_scalar_data};
    ShaderUniform std_radius = { "radius", float_binder, std_radius_data};


    RenderDataInput boid_shape_pass_input;
	boid_shape_pass_input.assign(0, "vertex_position", boid_shape_vertices.data(), boid_shape_vertices.size(), 4, GL_FLOAT);
	boid_shape_pass_input.assign_index(boid_shape_faces.data(), boid_shape_faces.size(), 3);
	RenderPass boid_shape_pass(-1,
			boid_shape_pass_input,
			{ boid_vertex_shader, nullptr, object_shader},
			{ std_model, std_view, std_proj, std_light,
              std_translate, std_rotate, std_color},
			{ "fragment_color" }
			);

    RenderDataInput food_shape_pass_input;
    food_shape_pass_input.assign(0, "vertex_position", food_shape_vertices.data(), food_shape_vertices.size(), 4, GL_FLOAT);
    food_shape_pass_input.assign_index(food_shape_faces.data(), food_shape_faces.size(), 3);
    RenderPass food_shape_pass(-1,
                               food_shape_pass_input,
                               { food_vertex_shader, nullptr, object_shader},
                               { std_model, std_view, std_proj, std_light,
                                 std_translate, std_color},
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
                                 object_shader
                             },
                             { std_model, std_view, std_proj,
                               std_light, std_camera,
                               std_translate, std_rotate, std_color, std_scalar, std_radius },
                             { "fragment_color" }
    );

    RenderDataInput sphere_pass_input;
    sphere_pass_input.assign(0, "vertex_position", sphere_vertices.data(), sphere_vertices.size(), 4, GL_FLOAT);
    sphere_pass_input.assign_index(sphere_faces.data(), sphere_faces.size(), 2);
    RenderPass sphere_pass(-1,
                             sphere_pass_input,
                             {
                                 sphere_vertex_shader,
                                 nullptr,
                                 object_shader
                             },
                             { std_model, std_view, std_proj,
                               std_light, std_camera,
                               std_translate, std_rotate, std_color, std_scalar, std_radius },
                             { "fragment_color" }
    );

    flock.generate_cylinders(cylinder_pass, cylinder_faces, numCylinders);
    flock.generate_spheres(sphere_pass, sphere_faces, numSpheres);
    flock.generate_boids();
    for (auto food_it = flock.food.begin(); food_it != flock.food.end(); ++food_it) {
        for (auto it = flock.obstacles.begin();
             it != flock.obstacles.end(); ++it) {

            while ((*it)->inside(food_it->pos)) {
                food_it->reposition();
                it = flock.obstacles.begin();
            }
        }
    }
    
    float aspect = 0.0f;
    bool draw_boids = true;
    bool draw_obstacle = false;
    int frameCount = 0;
    bool is_inside = false;
    int ob_inside = -1;

    GLfloat skyboxVertices[] = {
        // Positions
        -400.0f,  400.0f, -400.0f,
        -400.0f, -400.0f, -400.0f,
        400.0f, -400.0f, -400.0f,
        400.0f, -400.0f, -400.0f,
        400.0f,  400.0f, -400.0f,
        -400.0f,  400.0f, -400.0f,

        -400.0f, -400.0f,  400.0f,
        -400.0f, -400.0f, -400.0f,
        -400.0f,  400.0f, -400.0f,
        -400.0f,  400.0f, -400.0f,
        -400.0f,  400.0f,  400.0f,
        -400.0f, -400.0f,  400.0f,

        400.0f, -400.0f, -400.0f,
        400.0f, -400.0f,  400.0f,
        400.0f,  400.0f,  400.0f,
        400.0f,  400.0f,  400.0f,
        400.0f,  400.0f, -400.0f,
        400.0f, -400.0f, -400.0f,

        -400.0f, -400.0f,  400.0f,
        -400.0f,  400.0f,  400.0f,
        400.0f,  400.0f,  400.0f,
        400.0f,  400.0f,  400.0f,
        400.0f, -400.0f,  400.0f,
        -400.0f, -400.0f,  400.0f,

        -400.0f,  400.0f, -400.0f,
        400.0f,  400.0f, -400.0f,
        400.0f,  400.0f,  400.0f,
        400.0f,  400.0f,  400.0f,
        -400.0f,  400.0f,  400.0f,
        -400.0f,  400.0f, -400.0f,

        -400.0f, -400.0f, -400.0f,
        -400.0f, -400.0f,  400.0f,
        400.0f, -400.0f, -400.0f,
        400.0f, -400.0f, -400.0f,
        -400.0f, -400.0f,  400.0f,
        400.0f, -400.0f,  400.0f
    };

    GLuint skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

    // Setup vertex shader.
    GLuint vertex_shader_id = 0;
    const char* vertex_source_pointer = cubemap_vertex_shader;
    CHECK_GL_ERROR(vertex_shader_id = glCreateShader(GL_VERTEX_SHADER));
    CHECK_GL_ERROR(glShaderSource(vertex_shader_id, 1, &vertex_source_pointer, nullptr));
    glCompileShader(vertex_shader_id);
    CHECK_GL_SHADER_ERROR(vertex_shader_id);

    // Setup fragment shader.
    GLuint fragment_shader_id = 0;
    const char* fragment_source_pointer = cubemap_fragment_shader;
    CHECK_GL_ERROR(fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER));
    CHECK_GL_ERROR(glShaderSource(fragment_shader_id, 1, &fragment_source_pointer, nullptr));
    glCompileShader(fragment_shader_id);
    CHECK_GL_SHADER_ERROR(fragment_shader_id);

    // Let's create our program.
    GLuint program_id = 0;
    CHECK_GL_ERROR(program_id = glCreateProgram());
    CHECK_GL_ERROR(glAttachShader(program_id, vertex_shader_id));
    CHECK_GL_ERROR(glAttachShader(program_id, fragment_shader_id));

    // Bind attributes.
    CHECK_GL_ERROR(glBindAttribLocation(program_id, 0, "vertex_position"));

    glLinkProgram(program_id);
    CHECK_GL_PROGRAM_ERROR(program_id);

    // Get the uniform locations.
    GLint projection_matrix_location = 0;
    CHECK_GL_ERROR(projection_matrix_location =
                       glGetUniformLocation(program_id, "projection"));
    GLint view_matrix_location = 0;
    CHECK_GL_ERROR(view_matrix_location =
                       glGetUniformLocation(program_id, "view"));

    std::vector<const GLchar*> faces;
    faces.push_back("../assets/right.jpg");
    faces.push_back("../assets/left.jpg");
    faces.push_back("../assets/top.jpg");
    faces.push_back("../assets/bottom.jpg");
    faces.push_back("../assets/back.jpg");
    faces.push_back("../assets/front.jpg");
    GLuint cubemapTexture = loadCubemap(faces);

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

        if(!(frameCount %= gui.speed))
        {
            if(gui.make_inside && (!is_inside || ob_inside != gui.obstacleOn ) )
            {
                ob_inside = gui.obstacleOn;
                for (auto food_it = flock.food.begin(); food_it != flock.food.end(); ++food_it) {
                    while(!flock.obstacles[ob_inside]->inside(food_it->pos))
                        {
                                food_it->reposition();
                        }
                    }
                is_inside = true;
            }
            else if(!gui.make_inside && is_inside)
            {

                for (auto food_it = flock.food.begin(); food_it != flock.food.end(); ++food_it) {
                    for (auto it = flock.obstacles.begin();
                         it != flock.obstacles.end(); ++it) {
                        while ((*it)->inside(food_it->pos)) {
                            food_it->reposition();
                            it = flock.obstacles.begin();
                        }
                    }
                }
                is_inside = false;
            }

            if (flock.food.size() != gui.numFood && gui.numFood > flock.food.size())
                flock.add_food(gui.numFood);
            else if (flock.food.size() != gui.numFood && gui.numFood < flock.food.size())
                flock.remove_food(gui.numFood);

            if(!gui.paused)
                flock.fly();
            gui.boidSize = flock.boids.size();
            if(gui.cinematic_mode)
            {
                unsigned int on = gui.boidOn;
                if(on < flock.boids.size())
                {
                    gui.cameraFollow(flock.boids[gui.boidOn].pos, flock.boids[gui.boidOn].vel, flock.boids[gui.boidOn].get_rotation());
                }
                else{
                    gui.cameraFollow(flock.n_center, flock.n_center,glm::mat4(1));
                }
            }
            else
                gui.cameraFollow(flock.n_center, flock.n_center,glm::mat4(1));
        }

        gui.updateMatrices();
        mats = gui.getMatrixPointers();

        if (gui.cubemapOn) {
            glDepthMask(GL_FALSE);
            // Use our program.
            CHECK_GL_ERROR(glUseProgram(program_id));

            // Pass uniforms in.
            CHECK_GL_ERROR(
                glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE,
                                   mats.projection));
            CHECK_GL_ERROR(glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE,
                                              mats.view));
            glBindVertexArray(skyboxVAO);
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
            glDepthMask(GL_TRUE);
        }


        for (auto it = flock.food.begin(); it != flock.food.end(); ++it) {
            T = it->get_translate();
            color = it->col;
            food_shape_pass.setup();
            CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, food_shape_faces.size() * 3, GL_UNSIGNED_INT, 0));

        }

        for (auto it = flock.obstacles.begin(); it != flock.obstacles.end(); ++it) {
            T = (*it)->get_translate();
            R = (*it)->get_rotation();
            color = (*it)->col;
            scale = (*it)->scale;
            radius = (*it)->radius;
            (*it)->render();
        }

        frameCount++;
        if (draw_boids) {
            for (auto it = flock.boids.begin(); it != flock.boids.end(); ++it) {
                T = it->get_translate();
                R = it->get_rotation();
                color = it->col;
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
