#version 330 core

#define MAX_LIGHTS 32

struct Light {
    vec3 position;
    float intensity;
};

uniform vec3 color;
uniform Light lights[MAX_LIGHTS];
uniform int lightCount;

in vec3 normal;
in vec3 worldPosition;

out vec4 FragColor;

void main(){
    vec3 N = normalize(normal);
    vec3 lighting = vec3(0.0);

    for (int i = 0; i < lightCount; ++i){
        vec3 toLight = lights[i].position - worldPosition;
        float distanceSquared = dot(toLight, toLight);
        vec3 lightDirection = normalize(toLight);
        float diffuse = max(dot(N, lightDirection), 0.0);
        diffuse = pow(diffuse, 0.75);
        float attenuation = lights[i].intensity / (distanceSquared + 0.001);
        lighting += diffuse * attenuation;
    }

    lighting += vec3(0.2);
    lighting = min(lighting, vec3(1.5));

    FragColor = vec4(color * lighting, 1.0);
}