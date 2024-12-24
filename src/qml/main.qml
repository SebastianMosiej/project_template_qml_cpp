import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material

ApplicationWindow {
    visible: true
    width: 1200
    height: 600
    title: qsTr("Teco Studio Qt")

    RowLayout {
        anchors.fill: parent
        Rectangle {
            width: 32
            Layout.fillHeight: true
            color: Material.accent
        }
        ColumnLayout {
                Canvas {
                    id: gridCanvas
                    property int hexRadius: 20
                    width: 400
                    height: 400
                    onPaint: drawGrid()

                    function drawGrid() {
                        var context = getContext("2d");
                        var hexPoints = prepareHex(Qt.point(0,0), hexRadius)
                        context.clearRect(0, 0, gridCanvas.width, gridCanvas.height);
                        context.lineWidth = 0.5
                        context.strokeStyle = "black"
                        var widthStep = Math.sqrt(3)*hexRadius/2;
                        var heigthStep = 2*hexRadius*3/4


                        var startCenter = Qt.point(hexRadius/3,hexRadius/3);
                        var hexCenter = startCenter
                        for (var x=0;x<7;x++)
                        {
                            for(var y=0;y<7;y++)
                            {
                                drawHex1(context, hexCenter, hexPoints)
                                hexCenter = Qt.point(startCenter.x+widthStep*(y%2)+x*widthStep*2,startCenter.y+heigthStep*y+2);
                            }
                        }
                    }

                    function prepareHex(center, radius) {
                        var hexPoints = []
                        for(var i=0;i<=6;i++) {
                            var angle = 60 * i - 30
                            var angle_rad = Math.PI / 180 * angle
                            hexPoints.push(Qt.point(center.x+radius * Math.cos(angle_rad), center.y+radius*Math.sin(angle_rad)))
                        }
                        return hexPoints
                    }

                    function drawHex1(context, center, hexPoints) {
                        context.beginPath();
                        for(var i=0;i<=5;i++) {
                            context.moveTo(center.x+hexPoints[i].x, center.y+hexPoints[i].y)
                            context.lineTo(center.x+hexPoints[i+1].x, center.y+hexPoints[i+1].y)
                        }
                        context.closePath()
                        context.stroke()
                    }

                    MouseArea {
                        hoverEnabled: true
                        property int mouseX: -1
                        property int mouseY: -1
                        id: canvasMouseArea
                        anchors.fill: parent
                        onPositionChanged: {
                            mouseX = mouse.x
                            mouseY = mouse.y
                            // console.log("Position changed (", mouse.x, ",", mouse.y,")")
                            gridCanvas.drawGrid()
                        }
                        onExited: {
                            mouseX = -1
                            mouseY = -1
                            // console.log("Exited (", mouse.x, ",", mouse.y,")")
                            gridCanvas.drawGrid()
                        }
                    }
                }
        }
    }
}
