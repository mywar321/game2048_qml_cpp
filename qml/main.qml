import QtQuick 2.9
import QtQuick.Window 2.2
import com.game2048.GameController 1.0


Window {
    visible: true
    width: 550
    height: 740
    title: qsTr("Hello World")

    color: helper.myColors.bglight

    property int tileWidth : 425/4;


    GameController {
        id: controller


        onGameIsOver: {

        }
        onGenerateNewTile: {
            tileGrid.display_tile(i,j,value);
        }

        onMoveAndMerge: {
            tileGrid.animation_move(from, to);
            tileGrid.erase(from);
            tileGrid.display_tile(Math.floor(to/4),to%4,value);
        }
    }

    Rectangle {
        id: board
        y: 170
        width: 500
        height: 500
        color: helper.myColors.bgdark
        radius: 6
        focus: true
        Keys.onPressed: {
            switch(event.key) {
            case Qt.Key_Left:
                controller.moveLeft();
                break;
            case Qt.Key_Right:
                controller.moveRight();
                break;
            case Qt.Key_Up:
                controller.moveUp();
                break;
            case Qt.Key_Down:
                controller.moveDown();
                break;  
            }
        }
        Grid {
            id: tileGrid
            x: 15;
            y: 15;
            rows: 4; columns: 4; spacing: 15

            function erase(i) {
                cells.itemAt(i).tileText = "";
                cells.itemAt(i).color = helper.myColors.bggray;
            }
            function display_tile(i, j, value) {
                cells.itemAt(i*4+j).tileText = Math.pow(2,value).toString();
                cells.itemAt(i*4+j).color = helper.tileColors[value-1];
            }
            function animation_move(from, to) {
                var tileComponent = Qt.createComponent("Tile.qml");
                var aniTile = tileComponent.createObject(tileGrid,{
                                                             "x": from%4 * (15+tileWidth),
                                                             "y": Math.floor(from/4) * (15+tileWidth),
                                                             "color": helper.myColors.bggray,
                                                             "tileText": "32"
                                                         });
                aniTile.x = to%4 * (15+tileWidth);
                aniTile.y = Math.floor(to/4) * (15+tileWidth);
                aniTile.tileText = "4";
                aniTile.destroyFlag = true;
            }

            function animation_merge(from, to) {

            }

            Repeater {
                id: cells
                model: 16
                Tile {
                    width: tileWidth; height: tileWidth  //Rectangle.width - 5 * 15 / 4
                    radius: 3
                    color: helper.myColors.bggray
                    tileText: ""
                }


            }


//            Repeater {
//                id: tiles

//                model: 16

//                Tile {
//                    width: tileWidth; height: tileWidth  //Rectangle.width - 5 * 15 / 4
//                    radius: 3
//                    color: helper.myColors.bggray

//                    x: controller.tileList[index].y * (15+tileWidth)
//                    y: controller.tileList[index].x * (15+tileWidth)
//                    tileText: Math.pow(2,controller.tileList[index].value)


//                }
//            }
        }




    }





    Item {
        id: helper
        focus: false
        property var myColors: {"bglight": "#FAF8EF",
                                "bggray": Qt.rgba(238/255, 228/255, 218/255, 0.35),
                                "bgdark": "#BBADA0",
                                "fglight": "#EEE4DA",
                                "fgdark": "#776E62",
                                "bgbutton": "#8F7A66", // Background color for the "New Game" button
                                "fgbutton": "#F9F6F2" // Foreground color for the "New Game" button
                                }
        property var tileColors: ["#EEE4DA",
            "#EDE0C8", "#F2B179", "#F59563", "#F67C5F",
            "#F65E3B", "#EDCF72", "#EDCC61", "#EDC850",
            "#EDC53F", "#EDC22E", "#3C3A32"]


    }


    Component.onCompleted: {
        controller.gameStart();
    }
}
