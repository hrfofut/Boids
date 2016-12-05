R"zzz(
#version 330 core
uniform mat4 projection;
uniform mat4 view;
uniform vec4 light_position;
uniform vec3 camera_position;
uniform mat4 translate;
uniform float scalar;
uniform float radius;
in vec4 vertex_position;
void main() {
	vec4 pos = vec4(radius * cos(vertex_position.x),
					radius * sin(vertex_position.x),
					scalar * vertex_position.y, 1);
	gl_Position = projection * view * translate * pos;
}
)zzz"