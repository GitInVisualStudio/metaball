#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aColor;

out vec2 Color;
out vec2 Pos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
    Color = aColor;
    Pos = aPos;
}  