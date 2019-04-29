import QtQuick 2.2

Rectangle {
    id: root



    property string tileText: "4"
    property int moveAnimTime: 100
    property bool newTileAnimFlag:false
    property bool destroyFlag: false
    width: 425/4
    height: 425/4
    radius: 3

    color: "#b9b2b2"  //默认背景色

    Text {
        id: tile_text
        text: qsTr(root.tileText)
        anchors.centerIn: parent
        font.pixelSize: 55
        color: "#776E62"
    }


    ParallelAnimation {
        running: newTileAnimFlag
        NumberAnimation {
            target: root
            property: "opacity"
            from: 0.0
            to: 1.0
            duration: 200
        }

        ScaleAnimator {
            target: root
            from: 0
            to: 1
            duration: 250
            easing.type: Easing.OutQuad
        }
    }

    Behavior on color {
        ColorAnimation {
            duration: moveAnimTime

        }
    }

    Behavior on y {
        NumberAnimation {
            duration: moveAnimTime
            onRunningChanged: {
                if (!running && destroyFlag){
                    root.destroy();

                }
            }
        }
    }

    Behavior on x {
        NumberAnimation {
            duration: moveAnimTime
            onRunningChanged: {
                if (!running && destroyFlag){
                    root.destroy();

                }
            }
        }
    }


}
