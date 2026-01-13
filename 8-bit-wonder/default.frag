uniform sampler2D sceneTexture;
uniform vec2 resolution;
uniform float pixelSize;

uniform float lightPixelSize;
uniform float lightSteps;

const int MAX_LIGHTS = 16;
uniform int numLights;
uniform vec2 lightPos[MAX_LIGHTS];
uniform float lightRadius[MAX_LIGHTS];
uniform vec3 lightColor[MAX_LIGHTS];

void main()
{
    vec2 pixelCoord = floor(gl_FragCoord.xy / pixelSize) * pixelSize;
    vec2 uv = pixelCoord / resolution;
    vec4 sceneColor = texture2D(sceneTexture, uv);

    vec2 lightSamplePos =
        floor(gl_FragCoord.xy / lightPixelSize) * lightPixelSize;

    vec3 accumulatedLight = vec3(0.0);

    for (int i = 0; i < numLights; i++)
    {
        float dist = length(lightSamplePos - lightPos[i]);

        float brightness = 1.0 - dist / lightRadius[i];
        brightness = clamp(brightness, 0.0, .9);

        brightness = floor(brightness * lightSteps) / lightSteps;

        accumulatedLight += brightness * lightColor[i];
    }

    vec3 finalColor = sceneColor.rgb * (accumulatedLight + vec3(0.1));

    gl_FragColor = vec4(finalColor, sceneColor.a);
}