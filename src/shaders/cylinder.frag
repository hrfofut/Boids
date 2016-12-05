R"zzz(
#version 330 core
out vec4 fragment_color;
void main() {
	vec3 color = vec3(0.223, 0.568, 0.952);
	fragment_color = vec4(color, 1.0);
}
)zzz"