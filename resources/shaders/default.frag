#version 330

in vec4 vertColor;
in vec2 texcoord_frag;

out vec4 color;

uniform sampler2D tex;

void main(){
    //color = vertColor;
    color = texture(tex, texcoord_frag);
}
