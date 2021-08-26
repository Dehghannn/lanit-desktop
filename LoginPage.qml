import QtQuick 2.9
import QtQuick.Controls 2.13
import QtPositioning 5.14

Page {
    id: loginPage
    width: 800
    height: 600
    signal loginButtonPressed()
    Rectangle{
        id: rectangle
        color: "#72b1cd"
        anchors.fill: parent
        FocusScope{
            id: focusScope
            anchors.centerIn: rectangle
            height: nicknameInputRect.height
            width: nicknameInputRect.width
            x: nicknameInputRect.x
            y: nicknameInputRect.y
            Rectangle{
                id: nicknameInputRect
                color: "white"
                width: 550
                height: 50
                anchors.centerIn: parent
                radius: 16
                anchors.verticalCenterOffset: 13
                TextField {
                    id: textInput
                    anchors.topMargin: 0
                    focus: true
                    anchors.fill: parent
                    font.pixelSize: 22
                    clip: true
                    verticalAlignment: TextInput.AlignVCenter
                    leftPadding: 10
                    maximumLength: 30
                    onAccepted: {
                        appCpp.startUDPservice();
                        appCpp.nickName = textInput.text;
                        loginPage.loginButtonPressed();
                    }
                    Component.onCompleted: textInput.forceActiveFocus()
                }

            }
        }

        Button {
            id: loginButton
            x: 350
            height: 60
            text: qsTr("Start")
            anchors.horizontalCenter: focusScope.horizontalCenter
            anchors.top: focusScope.bottom
            anchors.topMargin: 55
            focus: false
            onPressed: {
                appCpp.startUDPservice();
                appCpp.nickName = textInput.text;
                loginPage.loginButtonPressed();

            }
        }

        Image {
            id: image
            y: 148
            width: 351
            height: 108
            anchors.left: focusScope.right
            anchors.leftMargin: -450
            anchors.bottom: focusScope.top
            anchors.bottomMargin: 41
            //fillMode: Image.PreserveAspectFit
            source: "qrc:/../icons/LanitIcon.png"
        }


    }
}

/*##^##
Designer {
    D{i:4;anchors_x:350;anchors_y:336}D{i:6;anchors_x:225}
}
##^##*/
