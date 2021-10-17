import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    id: root
    width: 600
    height: messageHolder.height
    property string text: "Hello"
    property bool isOwn: false
    property string timeStamp: "12:00"
    clip: true
    Rectangle{
        id: messageHolder
        height: messageBubble.height
        width: parent.width
        color: "#00000000"
        Rectangle{
            id: messageBubble
            radius: 3
            height: rowLayout.height//messageText.height + 20 + timeText.height
            color: root.isOwn ? "#82ada9" : "#b2dfdb"
            //width: messageText.width + 10
            //width: messageText.contentWidth + 30
            implicitWidth: rowLayout.width //Math.min( messageText.implicitWidth , messageHolder.width/2) + 30
            anchors.verticalCenter: messageHolder.verticalCenter
            anchors.left: isOwn? undefined : parent.left
            anchors.leftMargin: isOwn? undefined : 10
            anchors.right: isOwn? parent.right: undefined
            anchors.rightMargin: isOwn? 10 : undefined
            RowLayout{
                id: rowLayout
                height: messageText.height + timeText.height
            Text {
                //anchors.top: parent.top
                //anchors.topMargin: 5
                //anchors.verticalCenter: parent.verticalCenter
                //anchors.left: parent.left
                //anchors.leftMargin: 15
                //anchors.right: timeText.left
                color:  "black"
                height: contentHeight
                width: parent.width - 30
                clip: true
                id: messageText
                text: root.text
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                Layout.leftMargin: 15
                Layout.maximumWidth: messageHolder.width / 2 - 20
                Layout.fillWidth: true
                font.pointSize: 11


            }
            Text {
                //anchors.right: parent.right
                //anchors.bottom: parent.bottom
                id: timeText
                color: isOwn ? "#00695c" : "#10a2a1"
                text: timeStamp
                font.pointSize: 8
                Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                Layout.rightMargin: 3


            }
            }
        }
    }
}
