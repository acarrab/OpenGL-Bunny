// .................................................................
// basic.vert

void main()
{
vec2 my_displaced_vertex;

my_displaced_vertex = 0.25*gl_Vertex.xy + vec2(0.5,0.5);
gl_Position = vec4(my_displaced_vertex,0.0,1.0);
gl_FrontColor = vec4(0.0,1.0,0.0,1.0);
}
