#ifndef BOIDS_GUI_H
#define BOIDS_GUI_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include "config.h"

class Mesh;

/*
 * Hint: call glUniformMatrix4fv on thest pointers
 */
struct MatrixPointers {
	const float *projection, *model, *view;
};

class GUI {
public:
	GUI(GLFWwindow*);
	~GUI();

	void keyCallback(int key, int scancode, int action, int mods);
	void mousePosCallback(double mouse_x, double mouse_y);
	void mouseButtonCallback(int button, int action, int mods);
	void updateMatrices();
	MatrixPointers getMatrixPointers() const;

    void cameraFollow(glm::vec4 center, glm::vec4 vel, glm::mat4 rot);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MousePosCallback(GLFWwindow* window, double mouse_x, double mouse_y);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	glm::vec3 getCenter() const { return center_; }
	const glm::vec3& getCamera() const { return eye_; }
	const float* getLightPositionPtr() const { return &light_position_[0]; }

    bool paused = false;
    bool make_inside = false;
    int numFood = startFood;


    int obstacleOn = numCylinders + numSpheres;
    int boidOn = 0;
    int boidSize = start_boids;
    bool cinematic_mode = false;
private:
	GLFWwindow* window_;
	Mesh* mesh_;

	int window_width_, window_height_;
    int numObstacles = numCylinders + numSpheres;
	bool drag_state_ = false;
	bool fps_mode_ = false;
    bool follow_mode_ = true;
	int current_button_ = -1;
	float roll_speed_ = 0.1;
	float last_x_ = 0.0f, last_y_ = 0.0f, current_x_ = 0.0f, current_y_ = 0.0f;
	float camera_distance_ = camera_default;
	float pan_speed_ = 0.1f;
	float rotation_speed_ = .02f;
	float zoom_speed_ = 1.0f;
	float aspect_;
	glm::vec3 eye_ = glm::vec3(0.0f, 0.0f, camera_distance_);
	glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 look_ = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 tangent_ = glm::cross(look_, up_);
	glm::vec3 center_ = eye_ - camera_distance_ * look_;
	glm::mat3 orientation_ = glm::mat3(tangent_, up_, look_);
	glm::vec4 light_position_;

    glm::vec3 saved_look_ = look_;
    glm::vec3 saved_tangent_ = tangent_;
    glm::vec3 saved_up_ = up_;


	glm::mat4 view_matrix_ = glm::lookAt(eye_, center_, up_);
	glm::mat4 projection_matrix_;
	glm::mat4 model_matrix_ = glm::mat4(1.0f);

	bool captureWASDUPDOWN(int key, int action);

};

GLuint loadCubemap(std::vector<const GLchar*> faces);

#endif
