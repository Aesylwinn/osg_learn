#version 130

in vec4 color;
out vec4 osg_FragColor;

void main(void)
{
    osg_FragColor = color;
}

