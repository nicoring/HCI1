import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import mtq.qml3d 1.0
import QtQuick.Window 2.1
import "../framework"
import "../widgets"
import "../widgets/chordControl.js" as Control

HighResQuad {
    effect : LightShader {
        texture: "../transparent.png"
    }

    transform: [
        Scale3D {
            scale: Qt.vector3d(2.8,1.4,1)
        }
    ]

    // --- Contained Objects -------------------


    Chord {
        id: chord0
        rid: 0
        scale: 0
        position: Qt.vector3d(-0.4, 0.05, 0.2)
        effect : LightShader {
            texture: "../guitar chords/A.png"
        }
    }

    Chord {
        id: chord1
        rid: 1
        scale: 0.5
        position: Qt.vector3d(-0.3, 0.05, 0.2)
        effect : LightShader {
            texture: "../guitar chords/G.png"
        }
    }

    Chord {
        id: chord2
        rid: 2
        scale: 0.75
        position: Qt.vector3d(0.1, 0.05, 0.2)
        effect : LightShader {
            texture: "../guitar chords/Fism.png"
        }
    }

    // --- Actions ----------------------------

    function loadChords(c1, c2, c3) {
        Control.loadChordsImages(c1, c2, c3);
    }

    function doOneSlidingStep(nextNextChord) {
        // Determine the chords positions (-> current, next, hidden)
        var state = Control.getCurrentChordState();

        // Start animation for chord sliding
        Control.startSliding();

        // Rearrange animation targets for the next slide animation step
        Control.rearrangeAnimationTargets(state);

        // Preload chord which will show up on the left side in the next step
        Control.loadChordImage(state, nextNextChord);
    }

    ParallelAnimation {
        id: goToNextChordAnimation
        running: false;

        // Hide the current chord while sliding out of the frame
        // Afterwards put it back to the beginning where it will show up
        SequentialAnimation {
            ParallelAnimation {
                // Move to the right
                Vector3dAnimation {
                    id: moveCurrentAnimation
                    target: chord2
                    properties: "position"
                    duration: 500
                    to: Qt.vector3d(0.44, 0.05, 0.2)
                }
                // Hide
                NumberAnimation {
                    id: scaleCurrentAnimation
                    target: chord2
                    easing.type: Easing.InQuad // Quadratic changing
                    properties: "scale"
                    duration: 500
                    to: 0
                }
            }
            // Put it back to the beginning
            Vector3dAnimation {
                id: moveToStartAnimation
                target: chord2
                properties: "position"
                duration: 50
                to: Qt.vector3d(-0.4, 0.05, 0.2)
            }
        }

        // Highlight the left chord and center it
        ParallelAnimation {
            // Move to the middle of the frame
            Vector3dAnimation {
                id: moveNextAnimation
                target: chord1
                properties: "position"
                duration: 500
                to: Qt.vector3d(0.1, 0.05, 0.2)
            }
            // Enlarge for highlighting
            NumberAnimation {
                id: scaleNextAnimation
                target: chord1
                easing.type: Easing.InQuad // Quadratic changing
                properties: "scale"
                duration: 500
                to: 0.75
            }
        }

        // Let the next chord show up on the left side
        ParallelAnimation {
            // Slide in from the left
            Vector3dAnimation {
                id: moveForNextAnimation
                target: chord0
                properties: "position"
                duration: 500
                to: Qt.vector3d(-0.3, 0.05, 0.2)
            }
            // Make the chord visible
            NumberAnimation {
                id: scaleForNextAnimation
                target: chord0
                easing.type: Easing.InQuad // Quadratic changing
                properties: "scale"
                duration: 500
                to: 0.5
            }
        }
    }
}
