uniform sampler2D sceneTexture;
uniform vec2 resolution;

const int MAX_LIGHTS = 16;

uniform int numLights;
uniform vec2  lightPos[MAX_LIGHTS];
uniform float lightRadius[MAX_LIGHTS];
uniform vec3  lightColor[MAX_LIGHTS];

uniform float lightPixelSize;   // <<< ONLY FOR LIGHTS
uniform float lightSteps; 

void main()
{
    vec2 fragPos = gl_FragCoord.xy;
    vec2 uv = fragPos / resolution;

    // normal scene sampling (NOT pixelated)
    vec4 sceneColor = texture2D(sceneTexture, uv);

    vec2 fragPos = gl_FragCoord.xy;

    // pixelated position ONLY for lighting
    vec2 lightSamplePos =
        floor(fragPos / lightPixelSize) * lightPixelSize;

    vec3 accumulatedLight = vec3(0.0);

    for (int i = 0; i < numLights; i++)
    {
        float dist = length(lightSamplePos - lightPos[i]);

        // normal smooth brightness
        float brightness = 1.0 - dist / lightRadius[i];
        brightness = clamp(brightness, 0.0, 1.0);

        brightness = floor(brightness * lightSteps) / lightSteps;

        accumulatedLight += brightness * lightColor[i];
    }

    vec3 finalColor = sceneColor.rgb * (accumulatedLight + vec3(0.1));
    gl_FragColor = vec4(finalColor, sceneColor.a);
}
