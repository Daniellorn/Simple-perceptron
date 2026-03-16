import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls


ColumnLayout{

    function updateResult(value)
    {
        display.text = value.toString();
    }

    spacing: 40

    Rectangle{
        id: errorbox
        color: "black"
        border.width: 0.5

        Layout.preferredHeight: 180
        Layout.preferredWidth: 280
        Layout.alignment: Qt.AlignHCenter
        Layout.topMargin: 50

        Text{
            id: errorDisplay
            text: "Error: " + backend.getError().toString();
            color: "white"
            font.pixelSize: 40
            font.bold: true

            anchors.centerIn: parent
        }
    }

    Rectangle{
        id: resultbox
        color: "black"
        border.width: 0.5

        Layout.preferredHeight: 180
        Layout.preferredWidth: 180
        Layout.alignment: Qt.AlignHCenter
        Layout.topMargin: 50

        Text{
            id: display
            text: "?"
            color: "white"
            font.pixelSize: 140
            font.bold: true

            anchors.centerIn: parent
        }
    }

    RowLayout{
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignCenter
        spacing: 10

        Button {
            text: "Reset"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 50
            Layout.alignment: Qt.AlignHCenter

            onClicked:
            {
                pixelgrid.reset();
                display.text = "?";
            }
        }
        Button {
            text: "Check"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 50
            Layout.alignment: Qt.AlignHCenter

            onClicked:
            {
                var tempArray = pixelgrid.gridData;
                tempArray[35] = 0;
                pixelgrid.gridData = tempArray;
                display.text = backend.check(pixelgrid.gridData).toString();
            }
        }

        Button {
            text: "Save"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 50
            Layout.alignment: Qt.AlignHCenter

            onClicked: labelDialog.open()
        }

        Dialog{
            id: labelDialog
            title: "Number: "
            standardButtons: Dialog.Ok | Dialog.Cancel
            anchors.centerIn: parent

            TextField {
                id: labelInput
                placeholderText: "Drawed number: "
                inputMethodHints: Qt.ImhDigitsOnly
            }

            onAccepted: {
                var dataToSend = pixelgrid.gridData;

                dataToSend[35] = parseInt(labelInput.text);

                utils.saveInput(dataToSend);
                labelInput.clear();
                pixelgrid.reset();
            }
        }
    }
}
