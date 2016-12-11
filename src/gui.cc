#include "gui.h"
#include "config.h"
#include <jpegio.h>
#include <iostream>
#include <debuggl.h>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

GUI::GUI(GLFWwindow* window)
	:window_(window)
{
	glfwSetWindowUserPointer(window_, this);
	glfwSetKeyCallback(window_, KeyCallback);
	glfwSetCursorPosCallback(window_, MousePosCallback);
	glfwSetMouseButtonCallback(window_, MouseButtonCallback);

	glfwGetWindowSize(window_, &window_width_, &window_height_);
	float aspect_ = static_cast<float>(window_width_) / window_height_;
	projection_matrix_ = glm::perspective((float)(kFov * (M_PI / 180.0f)), aspect_, kNear, kFar);
}

GUI::~GUI()
{
}

void GUI::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window_, GL_TRUE);
		return ;
	}
	if (key == GLFW_KEY_J && action == GLFW_RELEASE) {
        unsigned char* buffer = new unsigned char[window_width_ * window_height_*3];
        glReadPixels(0, 0, window_width_, window_height_, GL_RGB, GL_UNSIGNED_BYTE, buffer);
        SaveJPEG("screenshot.jpg", window_width_, window_height_, buffer);
        delete[] buffer;
	}

	if (captureWASDUPDOWN(key, action))
		return ;

	else if (key == GLFW_KEY_C && action != GLFW_RELEASE) {
		fps_mode_ = !fps_mode_;
	}
    if (key == GLFW_KEY_F && action != GLFW_RELEASE) {
        follow_mode_ = !follow_mode_;
    }
    if (key == GLFW_KEY_SPACE && action != GLFW_RELEASE )
    {
        paused = !paused;
    }
    if (key == GLFW_KEY_Y && action != GLFW_RELEASE )
    {
        smooth_cin_ = !smooth_cin_;
    }
    if (key == GLFW_KEY_Q && action != GLFW_RELEASE )
    {
        obstacleOn = (obstacleOn + numObstacles) % (numObstacles + 1);
        make_inside = !(numObstacles == obstacleOn);
    }
    else if (key == GLFW_KEY_E && action != GLFW_RELEASE )
    {
        obstacleOn = (obstacleOn + 1) % (numObstacles + 1);
        make_inside = !(numObstacles == obstacleOn);
    }
    if (key == GLFW_KEY_0 && action != GLFW_RELEASE )
    {
        numFood = 0;
    }
    else if (key == GLFW_KEY_1 && action != GLFW_RELEASE )
    {
        numFood = 1;
    }
    else if (key == GLFW_KEY_2 && action != GLFW_RELEASE )
    {
        numFood = 2;
    }
    else if (key == GLFW_KEY_3 && action != GLFW_RELEASE )
    {
        numFood = 3;
    }
    else if (key == GLFW_KEY_4 && action != GLFW_RELEASE )
    {
        numFood = 4;
    }
    if (key == GLFW_KEY_T && action != GLFW_RELEASE )
    {
        cinematic_mode = !cinematic_mode;
        change = true;
        if(cinematic_mode)
        {
            saved_look_ = look_;
            saved_tangent_ = tangent_;
            saved_up_ = up_;
        }
        else
        {
            look_ = saved_look_;
            tangent_ = saved_tangent_;
            up_ = saved_up_;
            camera_distance_ = camera_default;
        }

    }
    if (key == GLFW_KEY_RIGHT_BRACKET && action != GLFW_RELEASE )
    {
        boidOn++;
        boidOn%=boidSize;
        change = true;
    }
    else if (key == GLFW_KEY_LEFT_BRACKET && action != GLFW_RELEASE )
    {
        boidOn+=(boidSize-1);
        boidOn%=boidSize;
        change = true;
    }
    if (key == GLFW_KEY_COMMA && action != GLFW_RELEASE )
    {
        if(speed <32)
            speed *= 2;
        printf("1 / %d speed\n", speed);
    }
    if (key == GLFW_KEY_PERIOD && action != GLFW_RELEASE )
    {
        if(speed != 1)
            speed /= 2;
        if(speed > 1)
            printf("1 / %d speed\n", speed);
        else
            printf("realtime\n", speed);
    }
}

void GUI::mousePosCallback(double mouse_x, double mouse_y)
{
	last_x_ = current_x_;
	last_y_ = current_y_;
	current_x_ = mouse_x;
	current_y_ = window_height_ - mouse_y;
	float delta_x = current_x_ - last_x_;
	float delta_y = current_y_ - last_y_;
	if (sqrt(delta_x * delta_x + delta_y * delta_y) < 1e-15)
		return;
	glm::vec3 mouse_direction = glm::normalize(glm::vec3(delta_x, delta_y, 0.0f));
	glm::vec2 mouse_start = glm::vec2(last_x_, last_y_);
	glm::vec2 mouse_end = glm::vec2(current_x_, current_y_);
	glm::uvec4 viewport = glm::uvec4(0, 0, window_width_, window_height_);

	bool drag_camera = drag_state_ && current_button_ == GLFW_MOUSE_BUTTON_RIGHT;

	if (drag_camera) {
		glm::vec3 axis = glm::normalize(
				orientation_ *
				glm::vec3(mouse_direction.y, -mouse_direction.x, 0.0f)
				);
		orientation_ =
			glm::mat3(glm::rotate(rotation_speed_, axis) * glm::mat4(orientation_));
		tangent_ = glm::column(orientation_, 0);
		up_ = glm::column(orientation_, 1);
		look_ = glm::column(orientation_, 2);
	}
}

void GUI::mouseButtonCallback(int button, int action, int mods)
{
	drag_state_ = (action == GLFW_PRESS);
	current_button_ = button;
}

void GUI::updateMatrices()
{
	// Compute our view, and projection matrices.
	if (fps_mode_)
		center_ = eye_ + camera_distance_ * look_;
	else
		eye_ = center_ - camera_distance_ * look_;

	view_matrix_ = glm::lookAt(eye_, center_, up_);
	light_position_ = glm::vec4(eye_, 1.0f);

	aspect_ = static_cast<float>(window_width_) / window_height_;
	projection_matrix_ =
		glm::perspective((float)(kFov * (M_PI / 180.0f)), aspect_, kNear, kFar);
	model_matrix_ = glm::mat4(1.0f);
}

MatrixPointers GUI::getMatrixPointers() const
{
	MatrixPointers ret;
	ret.projection = &projection_matrix_[0][0];
	ret.model= &model_matrix_[0][0];
	ret.view = &view_matrix_[0][0];
	return ret;
}
void GUI::cameraFollow(glm::vec4 center, glm::vec4 vel, glm::mat4 rot)
{
    if(!paused)
    {
        if(cinematic_mode) {
            glm::vec4 boid_velocity = vel;
            glm::vec4 up = glm::vec4(0, 0, 1, 0);
            if (glm::length(boid_velocity) == 0)
            {
                eye_ = glm::vec3(center);
                center_ = glm::vec3(center + glm::vec4(1,0,0,0));
                up_ = glm::vec3(0,1,0);

            }
            else {
                boid_velocity = glm::normalize(boid_velocity);
                glm::mat4 transform = rot;
                glm::vec3 axis = glm::vec3(transform * up);
//                axis = glm::vec3(up);
                up_ =  glm::vec3(axis);
//                up_ = glm::vec3(transform * up);
                if(change || !smooth_cin_)
                {
                    look_ = glm::vec3(boid_velocity);
                    saved_vel_ = boid_velocity;
                    change = false;
                }
                else if(glm::distance(saved_vel_, boid_velocity) > .01)
                {
//                    printf("asd\n");
                    saved_vel_ = saved_vel_ + 0.25f * (boid_velocity - saved_vel_);
                    look_ = glm::vec3(saved_vel_);
                }
                else {
//                    printf("asfd\n");
                    look_ = glm::vec3(boid_velocity);
                    saved_vel_ = boid_velocity;
                }

                //Change this to make it pretty! :)
                eye_ = glm::vec3(center - (4.0f * saved_vel_) ) + 0.1f * axis;
                center_ = glm::vec3(center + (5.0f * saved_vel_)) + 0.1f * axis;
                camera_distance_ = 9.0f;
            }

        }
        else if(follow_mode_)
        {
            center_ = glm::vec3(center);
            eye_ = center_ - camera_distance_ * look_;
    //        eye_.z = camera_distance_;
        }
    }
  return;
}

bool GUI::captureWASDUPDOWN(int key, int action)
{
	if (key == GLFW_KEY_W) {
		if (fps_mode_)
			eye_ += zoom_speed_ * look_;
		else
			camera_distance_ -= zoom_speed_;
		return true;
	} else if (key == GLFW_KEY_S) {
		if (fps_mode_)
			eye_ -= zoom_speed_ * look_;
		else
			camera_distance_ += zoom_speed_;
		return true;
	} else if (key == GLFW_KEY_A) {
		if (fps_mode_)
			eye_ -= pan_speed_ * tangent_;
		else
			center_ -= pan_speed_ * tangent_;
		return true;
	} else if (key == GLFW_KEY_D) {
		if (fps_mode_)
			eye_ += pan_speed_ * tangent_;
		else
			center_ += pan_speed_ * tangent_;
		return true;
	} else if (key == GLFW_KEY_DOWN) {
		if (fps_mode_)
			eye_ -= pan_speed_ * up_;
		else
			center_ -= pan_speed_ * up_;
		return true;
	} else if (key == GLFW_KEY_UP) {
		if (fps_mode_)
			eye_ += pan_speed_ * up_;
		else
			center_ += pan_speed_ * up_;
		return true;
	}
	return false;
}



// Delegrate to the actual GUI object.
void GUI::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GUI* gui = (GUI*)glfwGetWindowUserPointer(window);
	gui->keyCallback(key, scancode, action, mods);
}

void GUI::MousePosCallback(GLFWwindow* window, double mouse_x, double mouse_y)
{
	GUI* gui = (GUI*)glfwGetWindowUserPointer(window);
	gui->mousePosCallback(mouse_x, mouse_y);
}

void GUI::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	GUI* gui = (GUI*)glfwGetWindowUserPointer(window);
	gui->mouseButtonCallback(button, action, mods);
}

GLuint loadCubemap(std::vector<const GLchar*> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);

    int width,height;
//    unsigned char* image;

    Image image;
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < faces.size(); i++)
    {
//        image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
//        bool LoadJPEG(const std::string& file_name, Image* image);
        if(!LoadJPEG(faces[i], &image))
        {
            printf("Couldn't load the jpegs\n");
        }

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
            GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &(image.bytes[0])
        );
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
}