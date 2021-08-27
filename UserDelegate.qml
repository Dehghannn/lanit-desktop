import QtQuick 2.9
import QtQuick.Controls 2.9
import QtQuick.Controls.Material 2.3

Item {
    id: userDelegate
    width: 150
    height: 50
    property bool isOnline: true
    property string text: ""
    property alias backgroundColor: bgRect.color
    property alias highlighted: delegate.highlighted
    signal pressed()

    ItemDelegate{
        anchors.fill: parent
        id: delegate
        text: userDelegate.text
        Material.background: Material.color(Material.LightBlue, Material.Shade100)
        Material.elevation: 6
        onPressed:{ userDelegate.pressed()}

        contentItem: Rectangle{
            id : bgRect
            //color: "#00000000"
            color: "#E0F2F1"
            z: -1
            clip: true
            anchors.fill: parent
            Text {
                height: parent.height
                width: parent.width - 45
                elide: Text.ElideRight
                id: text
                text: userDelegate.text
                font.pixelSize: 15
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                leftPadding: 10
            }
            Rectangle{
                width: 15
                height: 15
                radius: 100
                border.width: 1                
                border.color: "black"
                x: parent.x + parent.width - 30
                anchors.verticalCenter:  parent.verticalCenter
                color: isOnline ? "#72E24C" : "gray"

            }

        }


    }
}
