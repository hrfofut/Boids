R"zzz(
#version 330 core
in vec4 face_normal;
in vec4 vertex_normal;
in vec4 light_direction;
in vec4 camera_direction;
in vec2 uv_coords;
out vec4 fragment_color;

void main() {
    fragment_color = vec4(1, 0, 0, 1.0);
}
)zzz"