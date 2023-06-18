#version 330 core
out vec4 FragColor;

struct VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec3 Albedo;
} fs_in;

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
    fs_in.FragPos = texture(gPosition, TexCoords).rgb;
    fs_in.Normal = texture(gNormal, TexCoords).rgb;
    fs_in.Albedo = texture(gAlbedoSpec, TexCoords).rgb;

    vec3 lighting;
    vec3 color = fs_in.Albedo;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.3);
    // ambient
    //vec3 ambient = 0.3 * lightColor;
    vec3 ambient = vec3(0, 0, 0);

    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff_out = max(dot(lightDir, normal), 0.0);

    vec3 diffuse = diff_out * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = spec * lightColor;
    // calculate shadow
    float shadow = shadows ? ShadowCalculation(fs_in.FragPos) : 0.0;
    //float shadow = 0;
    //lighting = lightDir;
    lighting = ((ambient + (1.0 - shadow) * (diffuse + specular)) * color);
    //lighting = fs_in.Normal;

    const int count = 500;
    for (int i = 0;i < count; ++i) {
        vec3 dir = -normalize(lightPos - fs_in.FragPos);
        vec3 right = normalize(cross(dir, fs_in.Normal));
        vec3 up = normalize(cross(right, dir));
        float sigma1 = random(i);
        float sigma2 = rand(uint(i));
        /*uint x_temp = uint(floor(random(fs_in.FragPos.x)*1024));
        uint y_temp = uint(floor(random(fs_in.FragPos.y)*1024));
        float sigma1 = rand(x_temp);
        float sigma2 = rand(y_temp);*/

        float posX = 512*sigma1 * sin(sigma2 * 2 * 3.14);
        float posY = 512*sigma1 * cos(sigma2 * 2 * 3.14);

        vec3 sampleDir = normalize(up * posX + right * posY + dir);
        float sampleLightDepth = texture(depthMap, sampleDir).r;
        sampleLightDepth *= far_plane;
        vec3 sampleLightPos = (sampleLightDepth-0.05) * sampleDir + lightPos;

        vec3 color = fs_in.Albedo;
        vec3 normal = normalize(fs_in.Normal);
        vec3 lightColor = vec3(0.3);
        // ambient
        //vec3 ambient = 0.3 * lightColor;
        vec3 ambient = vec3(0, 0, 0);
        // diffuse
        vec3 lightDir = normalize(sampleLightPos - fs_in.FragPos);
        //float diff = max(dot(lightDir, normal), 0.0);
        float diff = max(dot(lightDir, normal), 0.0);//*max(dot(lightDir, normal), 0.0);
        vec3 diffuse = diff * lightColor;
        // specular
        vec3 viewDir = normalize(viewPos - fs_in.FragPos);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = 0.0;
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
        vec3 specular = spec * lightColor;
        // calculate shadow
        // float shadow = shadows ? ShadowCalculation(fs_in.FragPos) : 0.0;
        vec3 dir_shit= sampleLightPos-fs_in.FragPos;
        //float para = diff_out * diff_out/(dot(dir_shit, dir)*dot(dir_shit, dir));
        lighting += ((ambient + (diffuse + specular)) * color) * sigma1 * sigma1/count*10;
        //lighting =sampleLightPos ;
        //lighting = sampleDir - dir;
    }
    //FragColor = vec4(lighting, 1.0);
    FragColor = vec4(, 1);
}