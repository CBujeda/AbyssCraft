#version 330 core
// Maneja el color final de cada píxel.
out vec4 FragColor;

in vec4 VertexColor;
in vec2 TexCoord;

void main(){
    FragColor = VertexColor;
}