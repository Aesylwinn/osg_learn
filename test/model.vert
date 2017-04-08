#version 130

uniform mat4 osg_ModelViewProjectionMatrix;

uniform vec4 lightPos;
uniform float brightness;
const vec4 lightColor = vec4(1, 1, 1, 1);
const vec4 ambient = vec4(0.1, 0.1, 0.1, 1);

in vec4 osg_Vertex;
in vec4 osg_Normal;
in vec4 osg_Color;

out vec4 color;

void main(void)
{
    vec4 position = osg_ModelViewProjectionMatrix * osg_Vertex;
    vec4 lightDir = lightPos - gl_Position;

    float dist = length(lightDir);
    lightDir /= dist;

    float diff = max(dot(osg_Normal, lightDir) * (10 / dist), 0);
    vec4 diffuse = diff * brightness * lightColor;

    gl_Position = position;
    color = (diffuse + ambient) * osg_Color;
}

