#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float u_time;

out vec3 vColor;

void main() {
    vec3 pos = aPos;
    pos.y += sin(pos.x * 0.1 + u_time) * cos(pos.z * 0.1 + u_time) * 1.5;
    gl_Position = projection * view * model * vec4(pos, 1.0);
    vColor = aColor;
}
