#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textureCoordinates;

out vec2 vTextureCoordinates;

void main()
{
    gl_Position = position;
    vTextureCoordinates = textureCoordinates;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 vTextureCoordinates;

uniform sampler2D uTexture;

void main()
{
    vec4 textureColor = texture(uTexture, vTextureCoordinates);
    color = textureColor;
};