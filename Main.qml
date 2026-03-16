import QtQuick
import QtQuick.Layouts

import "UI"

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("NumberPerceptron")

    Rectangle {
        anchors.fill: parent
        color: "#1a2226"

        Item{
            id: container
            anchors.centerIn: parent
            width: Math.min(parent.width, parent.height * 16 / 9)
            height: width * 9 / 16

            RowLayout{
                anchors.fill: parent
                anchors.margins: 20
                spacing: 20

                PixelGrid{
                    id: pixelgrid
                    Layout.preferredWidth: parent.width * 0.6
                    Layout.fillHeight: true
                    //Layout.preferredHeight: 680

                    onRequestCheck:
                    {
                        var result = backend.check(pixelgrid.gridData)
                        rightpanel.updateResult(result);
                    }
                }

                RightPanel{
                    id: rightpanel
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
        }
    }
}
