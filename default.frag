#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;

// gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;

// lights
uniform vec3 lightPos;
uniform vec4 lightColor;

uniform vec3 lightPos2;
uniform vec4 lightColor2;

uniform vec3 lightPos3;
uniform vec4 lightColor3;

uniform vec3 dirLightDirection;
uniform vec4 dirLightColor;

// gets the position of the camera from the main function
uniform vec3 camPos;

vec4 directionalLight(vec3 dir, vec4 color)
{
    // Adjust ambient light intensity
    float ambient = 0.3f;

    // Normalize the normal vector
    vec3 normal = normalize(Normal);
    
    // Normalize the light direction
    vec3 lightDirection = normalize(-dir); // Directional light direction is constant
    
    // Calculate diffuse component
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    // Adjust the intensity based on the angle between the normal and light direction
    float intensity = max(0.0, dot(normal, lightDirection));
    
    // Scale the diffuse component based on the intensity
    diffuse *= intensity;

    // Increase specular intensity
    float specularLight = 2.0f;

    // Calculate view direction and reflection direction for specular component
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    // Calculate specular component
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
    float specular = specAmount * specularLight;

    // Calculate final color
    vec4 finalColor = (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * color;

    return finalColor;
}

void main()
{
    FragColor = directionalLight(dirLightDirection, dirLightColor);
}
