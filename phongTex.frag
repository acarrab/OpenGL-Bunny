// Phong lighting in eye coordinates with texture access.

// These are set by the .vert code, interpolated.
varying vec3 ec_vnormal, ec_vposition;
varying vec2 textureCoords;

// This is set by the .c code.
uniform sampler2D mytexture;

void main()
{
    vec3 P, N, L, V, H;

    vec4 diffuse[3], specular[3];

    diffuse[0] = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
    diffuse[1] = gl_FrontMaterial.diffuse * gl_LightSource[1].diffuse;
    diffuse[2] = gl_FrontMaterial.diffuse * gl_LightSource[2].diffuse;

    specular[0] = gl_FrontMaterial.specular * gl_LightSource[0].specular;
    specular[1] = gl_FrontMaterial.specular * gl_LightSource[1].specular;
    specular[2] = gl_FrontMaterial.specular * gl_LightSource[2].specular;
    float shininess = gl_FrontMaterial.shininess;

    P = ec_vposition;
    N = normalize(ec_vnormal);
    L = normalize(gl_LightSource[0].position - P);
    V = normalize(-P);
    H = normalize(L+V);

    vec4 tcolor;
    tcolor = texture2D(mytexture, textureCoords) * 0.2;

    diffuse[0] *= max(dot(N,L),0.1);
    specular[0] *= pow(max(dot(H,N),0.0),shininess);

    L = normalize(gl_LightSource[1].position - P);
    V = normalize(-P);
    H = normalize(L+V);

    diffuse[1] *= max(dot(N,L),0.1);
    specular[1] *= pow(max(dot(H,N),0.0),shininess);

    L = normalize(gl_LightSource[2].position - P);
    V = normalize(-P);
    H = normalize(L+V);

    diffuse[2] *= max(dot(N,L),0.1);
    specular[2] *= pow(max(dot(H,N),0.0),shininess);

    vec4 overall_diffuse = (diffuse[0] * 0.5 + diffuse[1] * 0.4 + diffuse[2] * 0.1);
    vec4 overall_specular = (specular[0] + specular[1] + specular[2]) / 3;

    gl_FragColor = vec4(((overall_diffuse + tcolor) + overall_specular).xyz, 1.0);
}
