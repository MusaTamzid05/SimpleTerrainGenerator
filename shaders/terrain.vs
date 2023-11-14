#version 330 core

layout (location=0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 Color;

void main() {
    float height_value = position.y * 10;

    if(height_value <= 0.2)
        Color = vec4(0.0, 0.3, 0.7, 1.0);

    else if(height_value >=  0.2 && height_value <= 0.3)
        Color = vec4(0.545, 0.270, 0.074, 1.0);
    else
        Color = vec4(0.0, height_value, 0.0, 1.0);

    gl_Position = projection * view * model * vec4(position, 1.0);
}
