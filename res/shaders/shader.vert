#shader vertex
#version 330 core

layout(location = 0) in vec2 position;

uniform vec2 uScreenSize;

void main()
{
    vec2 ndc    = (position / uScreenSize) * 2.0 - 1.0;
    gl_Position = vec4(ndc.x, -ndc.y, 0.0, 1.0);
};

#shader fragment
#version 330 core

out vec4 color;

void main()
{
    color = vec4(25.0/255.0, 25.0/255.0, 25.0/255.0, 1.0);
};