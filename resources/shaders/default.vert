#version 330

in vec3 pos;
in vec2 texcoord;

out vec4 vertColor;
out vec2 texcoord_frag;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(pos, 1.0f);
    vertColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
    texcoord_frag = texcoord;
}
