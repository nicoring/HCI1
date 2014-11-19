import QtQuick 2.0

Item{
    property bool enabled: false

    //the light position sent to the shader (-> calculateReadOutPosition)
    property vector3d positionReadOut: Qt.vector3d(0,0,0);

    //values to be modified by your QML application
    property vector3d position: Qt.vector3d(0.0,0.0,0.0)
    property vector3d center: Qt.vector3d(0.0,0.0,0.0)
    property vector3d color: Qt.vector3d(1.0,1.0,1.0)
    property bool attenuation: false

    //if spotlight: the size of the light cone in ° (FOV of the camera)
    property real spotAngle: 90.0

    //1: directional, 2: spot light,
    property int type: 1

    property bool createsShadows: true

    property variant biasedMvpMatrix : [
                            1,0,0,0,
                            0,1,0,0,
                            0,0,1,0,
                            0,0,0,1
                        ]

    signal propertyChanged

    onPositionChanged: {
        calculateReadOutPosition();
        propertyChanged();
    }

    onSpotAngleChanged: {
        propertyChanged();
    }

    onCenterChanged: {
        calculateReadOutPosition();
        propertyChanged();
    }

    onColorChanged: {
        propertyChanged();
    }

    onAttenuationChanged: {
        propertyChanged();
    }

    onTypeChanged: {
        propertyChanged();
    }

    onBiasedMvpMatrixChanged: {
        propertyChanged();
    }

    onCreatesShadowsChanged: {
        propertyChanged();
    }

    onEnabledChanged: {
        propertyChanged();
    }

    function calculateReadOutPosition(){
        if (type == 1){
            //For directional lights, the shader only needs the direction of the light
            positionReadOut = center.minus(position).normalized();
        } else {
            //for point/spot lights, the shader needs the position
            positionReadOut = position;
        }
    }
}
