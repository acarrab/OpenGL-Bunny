//.....................................................................
// phong.vert

varying vec3 wc_normal, wc_position;

void main()
{
// Store original (world coordinate) normal and vertex values as "varying"
// so that they'll be interpolated and passed to fragment progam, where
// we can use them to compute lighting.
wc_normal = gl_Normal;
wc_position = gl_Vertex;
gl_Position = gl_ProjectionMatrix*gl_ModelViewMatrix*gl_Vertex;
}
