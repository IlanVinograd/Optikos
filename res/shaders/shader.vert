#shader vertex

#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec4 aColor;

uniform vec2 uScreenSize;

out vec4 fsColor;

void main()
{
    fsColor = aColor / 255.0;
    vec2 ndc    = (position / uScreenSize) * 2.0 - 1.0;
    gl_Position = vec4(ndc.x, -ndc.y, 0.0, 1.0);
};

#shader fragment

#version 330 core

in vec4 fsColor;
out vec4 color;

void main()
{
    color = fsColor;
};