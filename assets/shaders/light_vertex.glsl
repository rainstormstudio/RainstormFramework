#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec4 vColor;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0f);
  vColor = vec4(1.0);
}