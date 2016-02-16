#version 330

uniform sampler2D tex;

layout (location = 0) out vec4 FragColour;

in DATA {
	vec3 position;
	vec2 uv;
} inData;

void main() {
	vec4 diffuse = texture(tex, inData.uv);
	FragColour = vec4(0.4, 0.3, 1.0, 1.0);
}