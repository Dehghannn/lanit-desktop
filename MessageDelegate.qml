import QtQuick 2.0

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
            height: messageText.height + 20
            color: root.isOwn ? "#40d4c2" : "#10a2a1"
            //width: messageText.width + 10
            width: messageText.contentWidth + 30
            anchors.verticalCenter: messageHolder.verticalCenter
            anchors.left: isOwn? undefined : parent.left
            anchors.leftMargin: isOwn? undefined : 10
            anchors.right: isOwn? parent.right: undefined
            anchors.rightMargin: isOwn? 10 : undefined
                Text {
                //anchors.top: parent.top
                //anchors.topMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 15
                //anchors.right: parent.right /// @todo fix this
                anchors.rightMargin: 5
                height: contentHeight
                width: contentWidth//messageHolder.width / 2

              //  width: contentWidth + 15
                clip: true
                id: messageText
                text: root.text
                wrapMode: Text.WordWrap

                font.pointSize: 12


            }
        }
    }
}
