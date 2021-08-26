import QtQuick 2.9

Item {
    id: root
    width: 150
    height: 100
    signal pressed()
    property alias text: buttonText.text
    Rectangle{
        id: buttonRect
        color: {
            if (buttonMouseArea.pressed)
                return "#b9bcc0"
            else if(buttonMouseArea.containsMouse)
                return "#dbdee0"
            else
                return "#eceff1"
        }
        anchors.fill: parent
        radius: 16
        property var bindedColor: buttonMouseArea.containsMouse ? "#dbdee0" : "#eceff1"
        MouseArea{
            id: buttonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onPressed: {
                root.pressed();
            }
        }

        Text {
            id: buttonText
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 22
            color:  "#54a8cd"
            text: qsTr("Start")
        }
    }
}
