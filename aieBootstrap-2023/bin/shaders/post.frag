// a simple flat colour shader
#version 410

in vec2 vTexCoord;

uniform sampler2D colorTarget;
uniform int postProcessTarget;
uniform int windowWidth;
uniform int windowHeight;
uniform float iTime;


out vec4 FragColor;

vec4 Default(vec2 texCoord) {
    return texture(colorTarget, texCoord);
}

vec4 BoxBlur(vec2 texCoord) 
{
    vec2 texel = 1.0f / textureSize(colorTarget, 0);

    vec4 color = texture(colorTarget, texCoord);
    color += texture(colorTarget, texCoord + texel * vec2(-1, 1));
    color += texture(colorTarget, texCoord + texel * vec2(-1, 0));
    color += texture(colorTarget, texCoord + texel * vec2(-1, -1));

    color += texture(colorTarget, texCoord + texel * vec2(0, 1));
    color += texture(colorTarget, texCoord + texel * vec2(0, -1));

    color += texture(colorTarget, texCoord + texel * vec2(1, 1));
    color += texture(colorTarget, texCoord + texel * vec2(1, 0));
    color += texture(colorTarget, texCoord + texel * vec2(1, -1));

    return color / 9;
}

vec4 Distort(vec2 texCoord)
{
    vec2 mid = vec2(0.5f);
    float distanceFromTheCenter = distance(texCoord, mid);
    vec2 normalizeCoord = normalize(texCoord - mid);
    float bias = distanceFromTheCenter + sin(distanceFromTheCenter * 15) * 0.05f;
    vec2 newCoord = mid + bias * normalizeCoord;
    return texture(colorTarget, newCoord);
}

vec4 EdgeDetection(vec2 texCoord)
{
    float w = 1.0f / windowWidth;
    float h = 1.0f / windowHeight;

    vec4 k[9];

    k[0] = texture(colorTarget, texCoord + vec2(-w, -h));
    k[1] = texture(colorTarget, texCoord + vec2(0, -h));
    k[2] = texture(colorTarget, texCoord + vec2(w, -h));
    k[3] = texture(colorTarget, texCoord + vec2(-w, 0));
    k[4] = texture(colorTarget, texCoord);
    k[5] = texture(colorTarget, texCoord + vec2(w, 0));
    k[6] = texture(colorTarget, texCoord + vec2(-w, h));
    k[7] = texture(colorTarget, texCoord + vec2(0, h));
    k[8] = texture(colorTarget, texCoord + vec2(w, h));

    vec4 sobelEdgeH = k[2] + (2.0f * k[5]) + k[8] - (k[0] + (2.0f * k[3]) + k[6]); 
    vec4 sobelEdgeV = k[0] + (2.0f * k[1]) + k[2] - (k[6] + (2.0f * k[7]) + k[8]);

    vec4 sobel = sqrt((sobelEdgeH * sobelEdgeH) + (sobelEdgeV * sobelEdgeV));

    return vec4(1.0f - sobel.rgb, 1.0f);

}

vec4 Sepia(vec2 texCoord)
{
    vec4 color = texture(colorTarget, texCoord);

    float rr = .3;
    float rg = .769;
    float rb = .189;
    float ra = 0.0;
    
    float gr = .3;
    float gg = .686;
    float gb = .168;
    float ga = 0.0;
    
    float br = .272;
    float bg = .534;
    float bb = .131;
    float ba = 0.0;

    float r = (rr * color.r) + (rb * color.b) + (rg * color.g) + (ra * color.a);
    float g = (gr * color.r) + (gb * color.b) + (gg * color.g) + (ga * color.a);
    float b = (br * color.r) + (bb * color.b) + (bg * color.g) + (ba * color.a);

    return(vec4(r, g, b, 1.0f));
}

vec4 GreyScale(vec2 texCoord)
{
    vec4 color = texture(colorTarget, texCoord);

    float rr = 0.5f;
    float rg = 0.5f;
    float rb = 0.5f;
    float ra = 0.5f;
    
    float gr = 0.5f;
    float gg = 0.5f;
    float gb = 0.5f;
    float ga = 0.5f;
    
    float br = 0.5f;
    float bg = 0.5f;
    float bb = 0.5f;
    float ba = 0.5f;

    float r = (rr * color.r) + (rb * color.b) + (rg * color.g) + (ra * color.a);
    float g = (gr * color.r) + (gb * color.b) + (gg * color.g) + (ga * color.a);
    float b = (br * color.r) + (bb * color.b) + (bg * color.g) + (ba * color.a);

    return(vec4(r, g, b, 1.0f));
}

vec4 Invert(vec2 texCoord)
{
    vec4 color = texture(colorTarget, texCoord);

    float r = (1.0f - color.r);
    float g = (1.0f - color.g);
    float b = (1.0f - color.b);

    return(vec4(r, g, b, 1.0f));
}

float random (vec2 st)
{
    return fract(sin(dot(st.xy,
    vec2(12.9898, 78.233))) *
    43758.5453123);
}

vec4 Scanlines(vec2 texCoord)
{
    float density = 100.0f;
    float opacityScanline = .3;
    float opacityNoise = .5f;
    float flickering = 0.01f;


    vec4 color = texture(colorTarget, texCoord);
    
    float scaledY = (texCoord.y + iTime * 0.005f);

    float count = windowHeight * density;
    vec2 sl = vec2(sin(scaledY * count), cos(scaledY * count));
	vec3 scanlines = vec3(sl.x, sl.y, sl.x);

    color.rgb += color.rgb * scanlines * opacityScanline;
    color.rgb += color.rgb * vec3(random(texCoord * iTime)) * opacityNoise;
    color.rgb += color.rgb * sin(110.0f * iTime) * flickering;

    return vec4(color);
}

void main()
{
    // This will calculate the texel size
    vec2 texSize = textureSize(colorTarget, 0);
    vec2 texelSize = 1.0f / texSize;

    // Then we will adjust the coordnate
    vec2 scale = (texSize - texelSize) / texSize;
    vec2 texCoord = vTexCoord / scale + texelSize * 0.5f;

    switch(postProcessTarget)
    {
        default: // Default 
        {
            // Output post process effect here
             FragColor = Default(texCoord);
        }
        case 0: // BoxBlur
        {
            FragColor = BoxBlur(texCoord);
            break;
        }
        case 1: // Distort
        {
            FragColor = Distort(texCoord);
            break;
        }
        case 2: // Edge Detection
        {
            FragColor = EdgeDetection(texCoord);
            break;
        }
        case 3: // Sepia
        {
            FragColor = Sepia(texCoord);
            break;
        }
        case 4: // Scanlines
        {
            FragColor = Scanlines(texCoord);
            break;
        }
        case 5: // Grey Scale
        {
            FragColor = GreyScale(texCoord);
            break;
        }
        case 6: // Invert
        {
            FragColor = Invert(texCoord);
            break;
        }
        case 7: // Pixelizer
        {
            FragColor = Default(texCoord);
            break;
        }
        case 8: // Posterization
        {
            FragColor = Default(texCoord);
            break;
        }
         case 9: // Distance Fog
        {
            FragColor = Default(texCoord);
            break;
        }
         case 10: // Depth of Field
        {
            FragColor = Default(texCoord);
            break;
        }
    }
}