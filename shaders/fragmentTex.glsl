#version 330

in vec3 vPosition;
in vec4 vColor;
in vec2 vTexCoord;
in vec3 vNormal;

out vec4 gl_FragColor;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;

uniform vec3 lightPositions[10];
uniform vec3 lightColors[10];
uniform int nLights;

uniform vec3 viewPosition;

const float PI = 3.14159265359;

float distributionGGX(vec3 N, vec3 H, float roughness) {
  float a2 = roughness * roughness * roughness * roughness;
  float NdotH = max(dot(N, H), 0.0);
  float denom = (NdotH * NdotH * (a2 - 1.0) + 1.0);
  return a2 / (PI * denom * denom);
}

float geometrySchlickGGX(float NdotV, float roughness) {
  float r = (roughness + 1.0);
  float k = (r * r) / 8.0;
  return NdotV / (NdotV * (1.0 - k) + k);
}

float geometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
  return geometrySchlickGGX(max(dot(N, L), 0.0), roughness) *
         geometrySchlickGGX(max(dot(N, V), 0.0), roughness);
}

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
  return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

void main() {
  vec3 albedo = pow(texture(albedoMap, vTexCoord).rgb, vec3(2.2f));
  // vec3 vNormal = texture(normalMap, vTexCoord).rgb;
  // vNormal = normalize(vNormal * 2.0 - 1.0);
  float metallic = texture(metallicMap, vTexCoord).r;
  float roughness = texture(roughnessMap, vTexCoord).r;
  float ao = texture(aoMap, vTexCoord).r;

  vec3 N = normalize(vNormal);
  vec3 V = normalize(viewPosition - vPosition);

  vec3 F0 = vec3(0.04f);
  F0 = mix(F0, albedo, metallic);

  vec3 Lo = vec3(0.0f);
  for (int i = 0; i < nLights; i++) {
    // radiance
    vec3 L = normalize(lightPositions[i] - vPosition);
    vec3 H = normalize(V + L);
    float distance = length(lightPositions[i] - vPosition);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = lightColors[i] * attenuation;

    // cook-torrance brdf
    float NDF = distributionGGX(N, H, roughness);
    float G = geometrySmith(N, V, L, roughness);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;

    vec3 numerator = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
    vec3 specular = numerator / max(denominator, 0.001);

    // add to outgoing radiance Lo
    float NdotL = max(dot(N, L), 0.0);
    Lo += (kD * albedo / PI + specular) * radiance * NdotL;
  }

  vec3 ambient = vec3(0.03f) * albedo * ao;
  vec3 color = ambient + Lo;

  color = color / (color + vec3(1.0f));
  color = pow(color, vec3(1.0f / 2.2f));

  gl_FragColor = vec4(color, 1.0f);
}