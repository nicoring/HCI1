varying highp vec4 texCoord;
varying highp vec4 normal;
varying vec2 texScale;
uniform sampler2D qt_Texture0;
uniform sampler2D qt_Texture10;
uniform sampler2D qt_Texture11;
uniform sampler2D qt_Texture12;
uniform sampler2D qt_Texture13;
//uniform samplerCube qt_Texture12Cube;

//for point and spot lights
varying highp vec4 light0shadowCoord;
varying highp vec4 light1shadowCoord;
varying highp vec4 light2shadowCoord;
varying highp vec4 light3shadowCoord;

//general light
varying float light0BrightnessMultiplicator;
varying float light1BrightnessMultiplicator;
varying float light2BrightnessMultiplicator;
varying float light3BrightnessMultiplicator;
varying vec3 light0Color;
varying vec3 light1Color;
varying vec3 light2Color;
varying vec3 light3Color;
varying vec3 objectGlow;

void main(void)
{
    vec2 textCoord = texCoord.st;
    textCoord.x = texCoord.x * texScale.x;
    textCoord.y = texCoord.y * texScale.y;

    vec4 textureColor = texture2D(qt_Texture0, textCoord.st);

    //Discard fragment if texture is almost transparent
    if (textureColor.a < 0.01){
        discard;
    }

    //Shadow map reading
    float bias = 0.001;

    float l0shadowMult = 1.0;
    float l1shadowMult = 1.0;
    float l2shadowMult = 1.0;
    float l3shadowMult = 1.0;

    if (light0BrightnessMultiplicator > 0.0){
    if (texture2D(qt_Texture10, light1shadowCoord.xy).z < (light0shadowCoord.z - bias)){
         l0shadowMult = 0.2;
    }
    }

    if (light1BrightnessMultiplicator > 0.0){
    if (texture2D(qt_Texture11, light1shadowCoord.xy).z < (light1shadowCoord.z - bias)){
         l1shadowMult = 0.2;
    }
    }

    if (light2BrightnessMultiplicator > 0.0){
    if (texture2D(qt_Texture12, light2shadowCoord.xy).z < (light2shadowCoord.z - bias)){
         l2shadowMult = 0.2;
    }
    }

    if (light3BrightnessMultiplicator > 0.0){
    if (texture2D(qt_Texture13, light3shadowCoord.xy).z < (light3shadowCoord.z - bias)){
         l3shadowMult = 0.2;
    }
    }

    //calculating individual values
    vec3 light0final = textureColor.xyz * light0Color * abs(light0BrightnessMultiplicator) * l0shadowMult;
    light0final = clamp(light0final, vec3(0,0,0), vec3(1,1,1));

    vec3 light1final = textureColor.xyz * light1Color * abs(light1BrightnessMultiplicator) * l1shadowMult;
    light1final = clamp(light1final, vec3(0,0,0), vec3(1,1,1));

    vec3 light2final = textureColor.xyz * light2Color * abs(light2BrightnessMultiplicator) * l2shadowMult;
    light2final = clamp(light2final, vec3(0,0,0), vec3(1,1,1));

    vec3 light3final = textureColor.xyz * light3Color * abs(light3BrightnessMultiplicator) * l3shadowMult;
    light3final = clamp(light3final, vec3(0,0,0), vec3(1,1,1));   

    vec3 lightsFinal = light0final + light1final + light2final + light3final;

    //gl_FragColor = vec4(light0final + light1final + light2final + light3final,1.0); //<-- breaks the shadows of light2. find out WHY THE FUCK IT IS BROKEN (maybe unbound qt_Texture3?)
    gl_FragColor = vec4(lightsFinal + objectGlow,textureColor.a);
}
