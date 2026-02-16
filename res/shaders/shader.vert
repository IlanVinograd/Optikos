#shader vertex
#version 330 core

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform vec2 uScreenSize;

out vec2 v_TexCoord;
out vec4 fsColor;

void main()
{
    fsColor     = aColor;
    vec2 ndc    = (aPosition / uScreenSize) * 2.0 - 1.0;
    gl_Position = vec4(ndc.x, -ndc.y, 0.0, 1.0);

    v_TexCoord = aTexCoord;
};

#shader fragment
#version 330 core

uniform int uHasTexture;
uniform sampler2D uTexture;

in vec4  fsColor;
in vec2 v_TexCoord;

out vec4 color;

void main()
{
    if (uHasTexture == 1)
    {
        float sampledAlpha = texture(uTexture, v_TexCoord).r;
        color = vec4(fsColor.rgb, fsColor.a * sampledAlpha);
    }
    else
    {
        color = fsColor;
    }
};