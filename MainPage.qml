import QtQuick 2.9
import QtQuick.Controls 2.13
import QtPositioning 5.14

Page {
    id: loginPage
    width: 800
    height: 600
    Rectangle{
        id: rectangle
        color: "#72b1cd"
        anchors.fill: parent

        Rectangle {
            id: usersHolderRect
            width: 148
            color: "#24467d"
            radius: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 44
            anchors.left: parent.left
            anchors.leftMargin: 32
            anchors.top: parent.top
            anchors.topMargin: 43
            clip: true
            z: 2
            Rectangle{
                id: headerRect
                z: 1
                height: 40
                clip: true
                radius: 5
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#edfc4b"
                    }

                    GradientStop {
                        position: 1
                        color: "#d7dbac"
                    }
                }
                width: parent.width
                Text {

                    anchors.centerIn: parent
                    id: header
                    color: "#24467d"
                    text: qsTr("Users")
                    styleColor: "#91badc"
                    z: 3
                }
                Rectangle{
                    y : parent.y + parent.height - 10
                    height: 10
                    width: parent.width
                    color: "#d7dbac"
                }
            }
            ListView{
                id: userListView
                width: parent.width
                height: parent.height - headerRect.height
                y : parent.y - headerRect.y
                spacing: 1
                clip: true

                model: appCpp.userList
                delegate: UserDelegate{
                    width: userListView.width
                    height: 50
                    text: model.modelData.nickName
                    isOnline: model.modelData.isOnline

                }

            }
        }

        Rectangle {
            id: chatHolderRect
            color: "#ffffff"
            radius: 10
            anchors.left: usersHolderRect.right
            anchors.leftMargin: 22
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 44
            anchors.top: parent.top
            anchors.topMargin: 43
            anchors.right: parent.right
            anchors.rightMargin: 42
        }


    }
}

/*##^##
Designer {
    D{i:5;anchors_height:513;anchors_y:43}D{i:3;anchors_height:513;anchors_y:43}D{i:2;anchors_height:513;anchors_x:32;anchors_y:43}
D{i:10;anchors_width:556;anchors_x:202}
}
##^##*/
