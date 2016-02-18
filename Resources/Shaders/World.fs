#version 330

uniform sampler2D tex;

layout (location = 0) out vec4 FragColour;

in DATA {
	vec3 position;
	vec2 uv;
	vec3 normal;
} inData;

const vec3 lightPos = vec3(64.0f, 25.0f, 64.0f);
const float li = 128.0f;

void main() {
	vec4 diffuse = texture(tex, inData.uv);

	diffuse = vec4(0.2f, 0.8f, 0.4f, 1.0f);

	vec3 lightDir = normalize(lightPos - inData.position);
	float dif = max(dot(lightDir, inData.normal), 0.1) * li + 1.0f;
	float distance = length(lightPos - inData.position);
	vec4 diff = diffuse * min((dif / (distance * distance)), 1.5f);

	FragColour = vec4(diff.xyz, 1.0);
}