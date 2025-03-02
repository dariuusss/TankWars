#version 330

// Input
// TODO(student): Get vertex attributes from each location

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texture;
layout(location = 3) in vec3 vertex_color;


//layout(location = 3) in vec3 vertex_normal; ex 6
//layout(location = 1) in vec3 vertex_color; ex 6

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_color;

void main()
{
    // TODO(student): Send output to fragment shader
    frag_color = vertex_color;

    //frag_color = vertex_normal;   asta e exercitiul 5

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(vertex_position, 1.0);
}
