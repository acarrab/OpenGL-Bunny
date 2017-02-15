// ................................................................
// phongEC.vert

// To do the lighting in eye coordinates, apply gl_ModelViewMatrix to
// gl_Vertex and apply gl_NormalMatrix to gl_Normal. gl_NormalMatrix is
// the inverse transpose of the upper 3x3 corner of gl_ModelViewMatrix,
// which is what's required to rotate the normal into correct (ec) position.
// If the light positions are specified (in .c code) after the view volume
// transformation, then they will be stored in eye coordinates too, and
// you can access them directly as gl_LightSource[0].position, etc.

// Varying vectors will be interpolated as they're passed to the fragment
// shader.

varying vec3 ec_vnormal, ec_vposition;

void main()
{
ec_vnormal = gl_NormalMatrix*gl_Normal;
ec_vposition = gl_ModelViewMatrix*gl_Vertex;
gl_Position = gl_ProjectionMatrix*gl_ModelViewMatrix*gl_Vertex;
}
