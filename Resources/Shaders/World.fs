#version 330

uniform sampler2D tex;

layout (location = 0) out vec4 FragColour;

in DATA {
	vec3 position;
	vec2 uv;
	vec3 normal;
} inData;

void main() {
	vec4 diffuse = texture(tex, inData.uv);
	FragColour = vec4(1.0, 0.3, 0.4, 1.0);

	FragColour *= vec4(inData.normal / 2 + 1, 1.0);
}