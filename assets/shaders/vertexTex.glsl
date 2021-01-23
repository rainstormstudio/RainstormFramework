#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec3 vPosition;
out vec2 vTexCoord;
out vec3 vNormal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0f);

  vPosition = vec3(model * vec4(position, 1.0f));
  vNormal = normalize(mat3(transpose(inverse(model))) * normal);
  vTexCoord = texCoord;
}