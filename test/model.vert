#version 130

uniform mat4 osg_ModelViewProjectionMatrix;
in vec4 osg_Vertex;
in vec4 osg_Color;
in vec4 osg_Normal;

out vec4 color;

void main(void)
{
    color = osg_Color;
    gl_Position = osg_ModelViewProjectionMatrix * osg_Vertex;
}

