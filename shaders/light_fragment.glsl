#version 410

in vec4 vColor;

out vec4 gl_FragColor;

uniform vec3 lightColor;

void main() { gl_FragColor = vec4(lightColor, 1.0f); }