//QT Matrices
uniform highp mat4 qt_ModelViewProjectionMatrix;
uniform highp mat4 qt_ModelViewMatrix;
uniform highp mat4 qt_ProjectionMatrix;
uniform highp mat4 qt_WorldMatrix;
uniform highp mat3 qt_NormalMatrix;

//QT Properties
attribute highp vec4 qt_MultiTexCoord0;
attribute highp vec4 qt_Vertex;
attribute highp vec4 qt_Normal;

//Shadow related stuff
uniform mat4 light0ShadowBiasMvp;
uniform mat4 light1ShadowBiasMvp;
uniform mat4 light2ShadowBiasMvp;
uniform mat4 light3ShadowBiasMvp;

uniform mediump mat4 lightPositions;
uniform mediump mat4 lightColors;
uniform bool useLightning;

//non-shadow stuff
uniform vec3 glow;
uniform mediump vec2 textureScaling;

//To fragment shader
varying highp vec4 texCoord;
varying highp vec4 normal;
varying vec2 texScale;

//for point and spot lights
varying vec4 light0shadowCoord;
varying vec4 light1shadowCoord;
varying vec4 light2shadowCoord;
varying vec4 light3shadowCoord;

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

bool epsEqual(float a, float b){
    if (abs(a-b) < 0.01){
        return true;
    } else {
        return false;
    }
}

float calcBrightnessMultiplicator(float lightType, float lightAttenuation, vec3 lightPosition, vec3 lightShadowCoord, vec3 normal, vec3 worldPosition){
    float brightnessMultiplicator = 0.0;    
    // 0 means disabled

    if (epsEqual(lightType,1.0) || epsEqual(lightType,4.0)){
        //distance light - normal lambert term, but with the direction saved as lightPosition
        brightnessMultiplicator = min(0.85,max(dot(normal.xyz, lightPosition.xyz*-1.0),0.0));
    } else if (epsEqual(lightType,2.0) || epsEqual(lightType,5.0)){
        //Spotlight lambert term + radial weakening
        brightnessMultiplicator = min(0.85,max(dot(normal.xyz, (lightPosition.xyz-worldPosition.xyz)),0.0));

        float distToCenter = abs(length(lightShadowCoord.xy - vec2(0.5,0.5)));
        distToCenter = clamp(distToCenter,0.0, 1.0);
        brightnessMultiplicator = brightnessMultiplicator * (1.0 - smoothstep(0.2, 0.6, distToCenter));
    } 

    //adjust for attenuation
    if (lightAttenuation > 0.5){
        float adjustedDistance = distance(lightPosition.xyz, worldPosition.xyz)*0.4;
        brightnessMultiplicator = brightnessMultiplicator * clamp(1.0/(adjustedDistance*adjustedDistance),0.0,1.0);             
    }

    //if shadows disabled, map light brightness to 0 --> -1 instead 0 --> 1
    if (lightType > 3.5){
        brightnessMultiplicator = clamp(-1.0*brightnessMultiplicator,-1.0,0.0);
    }

    return brightnessMultiplicator;
}

void main(void)
{
    //basic stuff
    texScale = textureScaling;
    texCoord = qt_MultiTexCoord0;
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    normal = vec4(normalize(qt_NormalMatrix * qt_Normal.xyz),0.0);  
    objectGlow = glow;

    vec3 light0Position = vec3(lightPositions[0][0], lightPositions[1][0], lightPositions[2][0]);
    vec3 light1Position = vec3(lightPositions[0][1], lightPositions[1][1], lightPositions[2][1]);
    vec3 light2Position = vec3(lightPositions[0][2], lightPositions[1][2], lightPositions[2][2]);
    vec3 light3Position = vec3(lightPositions[0][3], lightPositions[1][3], lightPositions[2][3]);

    light0Color = vec3(lightColors[0][0], lightColors[1][0], lightColors[2][0]);
    light1Color = vec3(lightColors[0][1], lightColors[1][1], lightColors[2][1]);
    light2Color = vec3(lightColors[0][2], lightColors[1][2], lightColors[2][2]);
    light3Color = vec3(lightColors[0][3], lightColors[1][3], lightColors[2][3]);

    float light0Type = lightPositions[3][0];
    float light1Type = lightPositions[3][1];
    float light2Type = lightPositions[3][2];
    float light3Type = lightPositions[3][3];
    
    vec4 worldPosition = qt_WorldMatrix * qt_Vertex;

    light0shadowCoord = light0ShadowBiasMvp * worldPosition;      
    light0shadowCoord = light0shadowCoord / light0shadowCoord.w;  

    light1shadowCoord = light1ShadowBiasMvp * worldPosition;
    light1shadowCoord = light1shadowCoord / light1shadowCoord.w;

    light2shadowCoord = light2ShadowBiasMvp * worldPosition;
    light2shadowCoord = light2shadowCoord / light2shadowCoord.w;

    light3shadowCoord = light3ShadowBiasMvp * worldPosition;  
    light3shadowCoord = light3shadowCoord / light3shadowCoord.w;

    light0BrightnessMultiplicator = calcBrightnessMultiplicator(light0Type, lightColors[3][0], light0Position, light0shadowCoord.xyz, normal.xyz, worldPosition.xyz);
    light1BrightnessMultiplicator = calcBrightnessMultiplicator(light1Type, lightColors[3][1], light1Position, light1shadowCoord.xyz, normal.xyz, worldPosition.xyz);
    light2BrightnessMultiplicator = calcBrightnessMultiplicator(light2Type, lightColors[3][2], light2Position, light2shadowCoord.xyz, normal.xyz, worldPosition.xyz);
    light3BrightnessMultiplicator = calcBrightnessMultiplicator(light3Type, lightColors[3][3], light3Position, light3shadowCoord.xyz, normal.xyz, worldPosition.xyz);        
}
