#version 330 core
out vec4 FragColor;
  
in vec2 Color;
in vec2 Pos;

uniform sampler2D screenTexture;


#define MAX_BALL_LENGTH 32
uniform vec2 balls[MAX_BALL_LENGTH];
uniform float radius[MAX_BALL_LENGTH];
uniform float threshold;
uniform float scale;
uniform float ball_length;

float implicit(vec2 pos);

void main()
{
    float value = implicit(Pos);
    float dif = value - scale;
    if (sqrt(dif * dif) < threshold) {
        FragColor = vec4(Color, 0.0, 1.0);
    } else {
        FragColor = vec4(0, 0, 0, 1.0);
    }
}  


float implicit(vec2 pos) {
    float sum = 0;
    for (int i = 0; i < ball_length; i++) {
        sum += radius[i] / length(pos - balls[i]);
    }
    return sum;
}