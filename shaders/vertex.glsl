#version 410

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec4 vColor;
out vec2 vTexCoord;
out vec3 vNormal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0f);

  vTexCoord = 1.0 - texCoord;
  vNormal = normalize(mat3(transpose(inverse(model))) * normal);
  vColor = vec4(clamp(vNormal, 0.0f, 1.0f), 1.0f);
  // vColor = vec4(position, 1.0);
}