#version 130

uniform vec3 lightPos = vec3(10, 10, 10);
uniform vec4 lightColor = vec4(1, 1, 1, 1);
uniform float brightness = 0.7;

uniform vec4 ambient = vec4(0.1, 0.1, 0.1, 1);

in vec3 pos;
in vec3 norm;
in vec4 color;

out vec4 osg_FragColor;

void main(void)
{
    vec3 lightDir = lightPos - pos;
    float lightDist = length(lightDir);
    lightDir /= lightDist;

    float diff = max(dot(norm, lightDir), 0);
    vec4 diffuse = min(diff * brightness, 1) * lightColor;

    osg_FragColor = (diffuse + ambient) * color;
}

