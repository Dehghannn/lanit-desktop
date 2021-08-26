import QtQuick 2.0

Item {
    id: userDelegate
    width: 150
    height: 50
    property bool isOnline: true
    property alias text: userDelegateText.text
    Rectangle{
        id: userDelegateRect
        radius: 5
        border.width: 3
        border.color: "#0e4775"

        gradient: Gradient {
            GradientStop {
                position: 0
                color: {
                    if(userDelegateMouseArea.pressed)
                        return "#307A94"; //"#14e3aa";
                    else if(userDelegateMouseArea.containsMouse){
                        return "#26d4dd"
                    }
                    else{
                        return "#37e5ee";
                    }
                }
            }

            GradientStop {
                position: 1
                color: {
                    if(userDelegateMouseArea.pressed)
                        return "#5191b0";
                    else if(userDelegateMouseArea.containsMouse){
                        return "#62a2d0"
                    }
                    else{
                        return "#73b3d0";
                    }
                }

            }
        }


        anchors.fill: parent
        MouseArea{
            id: userDelegateMouseArea
            anchors.fill: parent
            hoverEnabled: true
        }
        Text {
            id: userDelegateText
            height: parent.height
            width: parent.width - 40
            text: qsTr("Ali Dehghanzade")
            font.pointSize: 9
            verticalAlignment: Text.AlignVCenter
            color: "#173c3e"
            horizontalAlignment: Text.AlignLeft
            anchors.left: parent.left
            anchors.leftMargin: 10
            elide: Text.ElideRight

        }
        Rectangle{
            id: statusCircle
            height: 16
            width: 16
            radius: 100
            color: isOnline ? "green" : "gray"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.right
            anchors.horizontalCenterOffset: -20
        }

    }
}
