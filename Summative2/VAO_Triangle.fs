#version 430 core

in vec3 vertexColor;
in vec2 TexCoord;
out vec4 color;

uniform sampler2D Texture;
uniform sampler2D Texture2;
uniform float currentTime;

// Lighting variables
in vec3 FragPos;
in vec3 Normal;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightDir;
uniform vec3 cameraPos;

void main()
{
   // ambientStrength
    vec3 ambient = 0.5 * lightColor;
    color = texture(Texture, TexCoord);

    // lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectionDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectionDir), 0.0), 256);
    vec3 specular = spec * lightColor * 5.0;

    vec3 totalColor = (ambient + diffuse + specular) * vec3(1.0, 1.0, 1.0);
    color = vec4(totalColor, 1.0f) * texture(Texture, TexCoord);
}