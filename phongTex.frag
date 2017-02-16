// ...............................................
// phong_teatex.frag

// Phong lighting in eye coordinates with texture access.

// These are set by the .vert code, interpolated.
varying vec3 ec_vnormal, ec_vposition;

// This is set by the .c code.
uniform sampler2D mytexture;

void main()
{
    vec3 P, N, L, V, H;
    vec4 tcolor;
    vec4 diffuse_color = gl_FrontMaterial.diffuse;
    vec4 specular_color = gl_FrontMaterial.specular;
    float shininess = gl_FrontMaterial.shininess;

    P = ec_vposition;
    N = normalize(ec_vnormal);
    L = normalize(gl_LightSource[0].position - P);
    V = normalize(-P);
    H = normalize(L+V);

    tcolor = texture2D(mytexture,gl_TexCoord[0].st);
    diffuse_color = 0.1*diffuse_color + 0.9*tcolor;
    diffuse_color *= max(dot(N,L),0.0);
    specular_color *= pow(max(dot(H,N),0.0),shininess);
    gl_FragColor = diffuse_color + specular_color;
}