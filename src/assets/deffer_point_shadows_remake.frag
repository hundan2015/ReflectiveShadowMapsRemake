#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform samplerCube depthMap;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float far_plane;
uniform bool shadows;

float ShadowCalculation(vec3 fragPos)
{

    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPos;
    // ise the fragment to light vector to sample from the depth map
    float closestDepth = texture(depthMap, fragToLight).r;
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
    closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // test for shadows
    float bias = 0.05;// we use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    // display closestDepth as debug (to visualize depth cubemap)
    // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);

    return shadow;
}

float random(float x)
{
    float y = fract(sin(x) * 100000.0);
    return y;
}


uint whash(uint seed)
{
    seed = (seed ^ uint(61)) ^ (seed >> uint(16));
    seed *= uint(9);
    seed = seed ^ (seed >> uint(4));
    seed *= uint(0x27d4eb2d);
    seed = seed ^ (seed >> uint(15));
    return seed;
}

float randcore4(uint wseed)
{
    wseed = whash(wseed);

    return float(wseed) * (1.0 / 4294967296.0);
}


float rand(uint wseed)
{
    return randcore4(wseed);
}

void main()
{
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;

    vec3 lighting;
    vec3 color = Albedo;
    vec3 normal = normalize(Normal);
    vec3 lightColor = vec3(0.3);

    vec3 fragToLight = normalize(lightPos - FragPos);
    float diff = max(dot(normal, fragToLight), 0.0);
    vec3 diffuse = diff * lightColor;
    float shadow = ShadowCalculation(FragPos);
    lighting = diffuse * (1 - shadow);

    vec3 up = normalize(cross(fragToLight, normal));
    vec3 right = normalize(cross(up, fragToLight));
    const int count = 1024;
    vec3 temp = vec3(0);
    for (int i = 0;i < count; ++i) {
        float sigma1 = random(i);
        float sigma2 = rand(uint(i));
        int r_max = 1024;
        float posX = r_max * sigma1 * sin(2 * 3.14 * sigma2);
        float posY = r_max * sigma1 * cos(2 * 3.14 * sigma2);
        vec3 sampleLightDirection = normalize(posX * up + posY * right - fragToLight);
        float sampleLightDepth = texture(depthMap, sampleLightDirection).r;
        vec3 sampleLightPos = lightPos + sampleLightDirection * sampleLightDepth;

        vec3 fragToSampleLight = normalize(sampleLightPos - FragPos);
        float sampleLightDiff = max(dot(normal, fragToSampleLight), 0.0);
        vec3 sample_diffuse = sampleLightDiff * lightColor;
        lighting += sample_diffuse / count;
    }


    FragColor = vec4(lighting, 1.0);
}