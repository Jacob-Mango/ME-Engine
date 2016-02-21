#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out DATA {
	vec3 position;
	vec2 uv;
	vec3 normal;
} outData;

uniform mat4 proj = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 model = mat4(1.0);

void main() {
	gl_Position = proj * view * model * vec4(position, 1.0);

	outData.position = (model * vec4(position, 1.0)).xyz;
	outData.uv = uv;
	outData.normal = normalize(vec3(model * vec4(normal, 0.0)));
}