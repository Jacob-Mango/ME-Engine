#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

out DATA {
	vec3 position;
	vec2 uv;
} outData;

uniform mat4 proj = mat4(1.0);
uniform mat4 model = mat4(1.0);

void main() {
	gl_Position = proj * model * vec4(position, 1.0);

	outData.position = position;
	outData.uv = uv;
}