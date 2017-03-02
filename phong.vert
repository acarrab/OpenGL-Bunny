// ..............................................
// phong_teatex.vert

varying vec3 ec_vnormal, ec_vposition;
varying vec2 textureCoords;

void main()
{
    ec_vnormal = gl_NormalMatrix*gl_Normal;
    ec_vposition = gl_ModelViewMatrix*gl_Vertex;
    gl_Position = gl_ProjectionMatrix*gl_ModelViewMatrix*gl_Vertex;
    vec3 flat_normal = gl_Normal;
    // flat_normal allows a static texture
    //textureCoords = vec2(asin(flat_normal.x)/3.14 + 0.5, -asin(flat_normal.y)/3.14 + 0.5);
    // ec_vnormal allows a texture that changes with transformations
    textureCoords = vec2(asin(ec_vnormal.x)/3.14 + 0.5, -asin(ec_vnormal.y)/3.14 + 0.5);
}
