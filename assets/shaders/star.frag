#version 330 core

uniform vec3 color;
uniform vec3 cameraPosition;

in vec3 normal;
in vec3 worldPosition;

out vec4 FragColor;

void main(){
    vec3 N = normalize(normal);

    vec3 viewDirection = normalize(cameraPosition - worldPosition);
    float facing = max(dot(N, viewDirection), 0.0);

    float centerGlow = pow(facing, 0.55);
    float rim = pow(1.0 - facing, 2.0);
    float emission = 1.8;

    vec3 finalColor = color * (emission * (0.65 + 0.35 * centerGlow) + 1.5 * rim);

    FragColor = vec4(finalColor, 1.0);
}