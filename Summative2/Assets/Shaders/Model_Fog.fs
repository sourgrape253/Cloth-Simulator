#version 430 core

in vec3 vertexColor;
in vec2 TexCoord;
out vec4 color;

uniform sampler2D Texture;
uniform sampler2D Texture2;
uniform float currentTime;

// Lighting variables
in vec4 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightDir;
uniform vec3 cameraPos;

void main()
{
// NORMAL DIRECTIONAL LIGHT
   // ambientStrength
//    vec3 ambient = 0.5 * lightColor;
//    color = texture(Texture, TexCoord);
    // lighting
//    vec3 norm = normalize(Normal);
//    vec3 lightDir = normalize(lightPos - vec3(FragPos));
//    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = diff * lightColor;
//
//    vec3 viewDir = normalize(cameraPos - vec3(FragPos));
//    vec3 reflectionDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectionDir), 0.0), 256);
//    vec3 specular = spec * lightColor * 5.0;
//
//    vec3 totalColor = (ambient + diffuse + specular) * vec3(1.0, 1.0, 1.0);
//    color = vec4(totalColor, 1.0f) * texture(Texture, TexCoord);

    

    vec3 ambient = 0.5 * lightColor;
    color = texture(Texture, TexCoord);

    // fog
    float d = distance(FragPos.xyz, cameraPos);
    float lerp = (d - 5.0f)/250.0f;
    lerp = clamp(lerp, 0.0, 0.7);
    vec4 vFogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

    // Point Light
    float constant = 0.05f;
    float linear = 0.009f;
    float quadratic = 0.0032f;

    vec3 lightDir = normalize(lightPos - vec3(FragPos));
    // Diffuse shading
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    //Specular Shading
    vec3 viewDir = normalize(cameraPos - vec3(FragPos));
    vec3 reflectionDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectionDir), 0.0), 256);
    vec3 specular = spec * lightColor * 5.0;

    // Attenuation
    float distance = length(lightPos - vec3(FragPos));
    float attenuation = 1.0f / (constant + linear * distance +
                                quadratic * (distance*distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;


    vec3 totalColor = (ambient + diffuse + specular) * vec3(1.0, 1.0, 1.0);
    color = vec4(totalColor, 1.0f) * texture(Texture, TexCoord);

    color = mix(color,vFogColor, lerp);   
}