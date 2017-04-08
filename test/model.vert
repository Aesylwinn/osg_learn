#version 130

uniform mat4 osg_ModelViewProjectionMatrix;
uniform mat4 osg_ModelViewMatrix;
uniform mat4 osg_ViewMatrixInverse;

in vec3 osg_Vertex;
in vec3 osg_Normal;
in vec4 osg_Color;

out vec3 pos;
out vec3 norm;
out vec4 color;

void main(void)
{
    pos = (osg_ViewMatrixInverse * osg_ModelViewMatrix * vec4(osg_Vertex, 1)).xyz;
    norm = osg_Normal;
    color = osg_Color;

    gl_Position = osg_ModelViewProjectionMatrix * vec4(osg_Vertex, 1);
}

