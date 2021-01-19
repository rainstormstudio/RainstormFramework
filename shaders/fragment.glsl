#version 410

in vec4 vColor;
in vec2 vTexCoord;
in vec3 vNormal;

out vec4 gl_FragColor;

uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

void main() {
  vec3 F0 = vec3(0.04f);
  F0 = mix(F0, albedo, metallic);

  vec3 Lo = vec3(0.0f);
  Lo = albedo;

  vec3 ambient = vec3(0.03f) * albedo * ao;
  vec3 color = ambient + Lo;

  color = color / (color + vec3(1.0f));
  color = pow(color, vec3(1.0f / 2.2f));

  gl_FragColor = vec4(color, 1.0);
}