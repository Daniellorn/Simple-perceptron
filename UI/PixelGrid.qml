import QtQuick 2.15
import QtQuick.Layouts

Rectangle {
    id: pixelgrid
    color: "black"

    property var gridData: Array(36).fill(-1)

    function updateArray(index, filled)
    {
        var newArray = gridData.slice();
        newArray[index] = filled ? 1 : -1;
        gridData = newArray;
    }

    function reset()
    {
        gridData = Array(36).fill(-1);
    }

    GridLayout {
        anchors.fill: parent
        columns: 5
        rows: 7
        columnSpacing: 2
        rowSpacing: 2

        Repeater {
            model: 35
            Rectangle {
                id: cellRect
                color: isFilled ? "white" : "black"
                border.color: "white"
                border.width: 0.5

                property bool isFilled : pixelgrid.gridData[index] === 1

                Layout.fillWidth: true
                Layout.fillHeight: true

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var newState = (pixelgrid.gridData[index] !== 1);
                        pixelgrid.updateArray(index, newState);

                    }
                }
            }
        }
    }
}


