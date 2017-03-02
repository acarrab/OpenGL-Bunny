varying vec3 ec_vnormal, ec_vposition;

void main()
{
    // TEMPORARY
    vec4 dif1 = vec4(0, 0.4, 0.8, 1.0);
    vec4 dif2 = vec4(0.0, 0.8, 0.0, 1.0);
    vec4 spec1 = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 spec2 = vec4(0.0, 0.0, 1.0, 1.0);
    // END TEMPORARY

    vec3 P, N, L, V, H;

    // TEMPORARY
    vec4 diffuse1 = gl_FrontMaterial.diffuse * dif1;
    vec4 diffuse2 = gl_FrontMaterial.diffuse * dif2;
    vec4 specular1 = gl_FrontMaterial.specular * spec1;
    vec4 specular2 = gl_FrontMaterial.specular * spec2;
    // END TEMPORARY
    float shininess = gl_FrontMaterial.shininess;
    float pi = 3.14159265;

    P = ec_vposition;
    N = normalize(ec_vnormal);
    L = normalize(gl_LightSource[0].position - P);
    V = normalize(-P);				// eye position is (0,0,0)!
    H = normalize(L+V);

    diffuse1 *= max(dot(N,L),0.0);
    specular1 *= ((shininess+2.0)/(8.0*pi))*pow(max(dot(H,N),0.0),shininess);

    L = normalize(gl_LightSource[1].position - P);
    V = normalize(-P);
    H = normalize(L+V);

    diffuse2 *= max(dot(N,L), 0.0);
    specular2 *= ((shininess+2.0)/(8.0*pi))*pow(max(dot(H,N),0.0),shininess);
    gl_FragColor = ((diffuse1 + diffuse2)/2 + (specular1 + specular2)/2);
}
