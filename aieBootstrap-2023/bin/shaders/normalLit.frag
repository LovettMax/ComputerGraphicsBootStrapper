// a phong shader
#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 FragColor;

uniform vec3 CameraPosition;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

// Model Data
uniform vec3 Ka; // The ambient material color
uniform vec3 Kd; // The diffuse material color
uniform vec3 Ks; // The specular material color
uniform float specularPower; // The specular power of Ks 

//uniform vec4 BaseColor;
// Light Data
uniform vec3 AmbientColor;
uniform vec3 LightColor;
uniform vec3 LightDirection;

void main()
{
    // Set the normal and light direction
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightDirection);

    vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
    vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;

    //  Calculate the negative light direction (Lambert Term)
    float lambertTerm = max(0, min(1, dot(N, -L)));

    // Calculate the view vector...
    vec3 V = normalize(CameraPosition - vPosition.xyz);
    // ...and the relflection vector
    vec3 R = reflect(L, N);

    // Calculate the specular term
    float specularTerm = pow(max(0, dot(R, V)), specularPower);


    // Calculate the properties of each color type
    vec3 ambient = AmbientColor * Ka * texDiffuse;
    vec3 diffuse = LightColor * Kd * texDiffuse * lambertTerm;
    vec3 specular = LightColor * Ks * texSpecular * specularTerm;

    FragColor = vec4(ambient + diffuse + specular, 1);
}