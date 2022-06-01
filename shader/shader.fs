#version 330 core
out vec4 FragColor;
  
in vec3 Color;
in vec2 Pos;

#define MAX_BALL_LENGTH 32
uniform vec2 balls[MAX_BALL_LENGTH];
uniform float radius[MAX_BALL_LENGTH];
uniform float threshold;
uniform float scale;
uniform float ball_length;

/**
* returns the implicit function of all the balls
*/
float implicit(vec2 pos);

void main()
{
    float value = implicit(Pos);

    // difference to our wanted scale of the implicit function
    float dif = value - scale;
    /**
    * if the function at the current position is within a specified threshold we will draw the color
    * otherwise we just draw black
    */
    if (dif > 0) {
        if (dif > 1) {
            dif = 1/(dif*dif);
        }
        FragColor = vec4(Color * dif + Color * 0.3, 1.0);
    } else {
        FragColor = vec4(Color * 0.3, 1.0);
    }
}  


float implicit(vec2 pos) {
    float sum = 0;
    // just the sum of each implicit function of the ball
    for (int i = 0; i < ball_length; i++) {
        sum += radius[i] / length(pos - balls[i]);
    }
    return sum;
}