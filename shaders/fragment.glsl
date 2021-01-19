#version 410

in vec4 vColor;
in vec2 vTexCoord;
in vec3 vNormal;

out vec4 gl_FragColor;

void main() { gl_FragColor = vColor; }