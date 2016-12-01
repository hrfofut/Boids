R"zzz(
#version 330 core
uniform mat4 projection;
uniform mat4 view;
uniform vec4 light_position;
uniform vec3 camera_position;
uniform mat4 food_translate;
in vec4 vertex_position;
void main() {
	gl_Position = projection * view * food_translate * vertex_position;
}
)zzz"