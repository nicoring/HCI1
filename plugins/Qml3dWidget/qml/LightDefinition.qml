import QtQuick 2.0

Item {
    property list<LightDefinitionEntry> lightEntries: [
        LightDefinitionEntry {
            id: light0
            onPropertyChanged: {lightDefinitionChange()}
        },
        LightDefinitionEntry {
            id: light1
            onPropertyChanged: {lightDefinitionChange()}
        },
        LightDefinitionEntry {
            id: light2
            onPropertyChanged: {lightDefinitionChange()}
        },
        LightDefinitionEntry {
            id: light3
            onPropertyChanged: {lightDefinitionChange();}
        }
    ]

    signal lightDefinitionChange();

    function updateLightShader(shader){
        //Update Positions and types for all Lights
        var positionMatrix = Qt.matrix4x4(
                    lightEntries[0].positionReadOut.x, lightEntries[0].positionReadOut.y, lightEntries[0].positionReadOut.z, convertLightEntryType(lightEntries[0]),
                    lightEntries[1].positionReadOut.x, lightEntries[1].positionReadOut.y, lightEntries[1].positionReadOut.z, convertLightEntryType(lightEntries[1]),
                    lightEntries[2].positionReadOut.x, lightEntries[2].positionReadOut.y, lightEntries[2].positionReadOut.z, convertLightEntryType(lightEntries[2]),
                    lightEntries[3].positionReadOut.x, lightEntries[3].positionReadOut.y, lightEntries[3].positionReadOut.z, convertLightEntryType(lightEntries[3])
                    );
        shader.lightPositions = positionMatrix;

        //Update color and attenuation
        var attenuations = [0.0,0.0,0.0,0.0];
        for (var i=0; i<4;i++){
            if (lightEntries[i].attenuation == true){
                attenuations[i] = 1.0;                
            }
        }

        var colorMatrix = Qt.matrix4x4(
                    lightEntries[0].color.x, lightEntries[0].color.y, lightEntries[0].color.z, attenuations[0],
                    lightEntries[1].color.x, lightEntries[1].color.y, lightEntries[1].color.z, attenuations[1],
                    lightEntries[2].color.x, lightEntries[2].color.y, lightEntries[2].color.z, attenuations[2],
                    lightEntries[3].color.x, lightEntries[3].color.y, lightEntries[3].color.z, attenuations[3]
                    );
        shader.lightColors = colorMatrix;


        //set matrices for shadow mapping
        if (lightEntries[0].enabled){
            shader.light0ShadowBiasMvp = lightEntries[0].biasedMvpMatrix;
        }

        if (lightEntries[1].enabled){
            shader.light1ShadowBiasMvp = lightEntries[1].biasedMvpMatrix;
        }

        if (lightEntries[2].enabled){
            shader.light2ShadowBiasMvp = lightEntries[2].biasedMvpMatrix;
        }

        if (lightEntries[3].enabled){
            shader.light3ShadowBiasMvp = lightEntries[3].biasedMvpMatrix;
        }
    }

    function convertLightEntryType(lightEntry){
        if (!lightEntry.enabled)
            return 0;

        var r = lightEntry.type; //1,2 or 3
        if (!lightEntry.createsShadows){
            r = r + 3; //4,5,6
        }

        return r;
    }
}
