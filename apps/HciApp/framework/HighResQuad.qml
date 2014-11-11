import QtQuick 2.0
import Qt3D 2.0

Item3D {
    id: quad
    mesh: Mesh { source: "qrc:/models/framework/HighResQuad.3ds" }

    function mtqContactDown(id, position){
        if (parent.mtqContactDown)
            parent.mtqContactDown(id,position)
    }

    function mtqContactUp(id, position){
        if (parent.mtqContactUp)
            parent.mtqContactUp(id, position)
    }
}
