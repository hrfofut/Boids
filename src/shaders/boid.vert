R"zzz(
#version 330 core
uniform mat4 projection;
uniform mat4 view;
uniform vec4 light_position;
uniform vec3 camera_position;
uniform mat4 translate;
uniform mat4 rotate;
in vec4 vertex_position;
void main() {
	gl_Position = projection * view * translate * rotate * vertex_position;
}
)zzz"