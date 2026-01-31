#version 330 core
// Maneja la posición y recibe datos del Tessellator.
layout (location = 0) in vec3 aPos; // Coincide con Tessellator (location 0)
layout (location = 1) in vec4 aColor; // Coincide con Tessellator (location 1)
layout (location = 2) in vec2 aTex; // Coincide con Tessellator (location 2)

// Salida al Fragment Shader
out vec4 VertexColor; 
out vec2 TexCoord;

// Uniforms: Variables glovales que se enviaran desde c++
uniform mat4 u_ModelViewProjection;

void main(){

    gl_Position = vec4(aPos,1.0);
    VertexColor = aColor;
    TexCoord = aTex;
}
