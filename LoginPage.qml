import QtQuick 2.9
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.3
import QtPositioning 5.14

Page {
    id: loginPage
    width: 800
    height: 600
    signal loginButtonPressed()
    Rectangle{
        id: rectangle
        color: "#ffffff"
//        anchors.rightMargin: 0
//        anchors.bottomMargin: 0
//        anchors.leftMargin: 0
//        anchors.topMargin: 0//"#72b1cd"
        anchors.fill: parent


        TextField {
            id: textInput
            width: 550
            height: 50
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 70
            font.pixelSize: 22
            clip: true
            verticalAlignment: TextInput.AlignVCenter
            maximumLength: 30
            validator: RegExpValidator{}
            onAccepted: {
                if(text != "")
                {
                    appCpp.startUDPservice();
                    appCpp.nickName = textInput.text;
                    loginPage.loginButtonPressed();
                }
            }
            Component.onCompleted: textInput.forceActiveFocus()
        }


        Button {
            id: loginButton
            x: 350
            height: 70
            width: 150
            text: qsTr("Start")
            flat: false
            anchors.horizontalCenter: textInput.horizontalCenter
            anchors.top: textInput.bottom
            anchors.topMargin: 33
            focus: false
            Material.background: Material.color(Material.Teal, Material.Shade800); // Material.LightBlue
            Material.foreground: "white"
            //flat: true
            //palette:
            onPressed: {
                if(textInput.text !=  "")
                {
                    appCpp.startUDPservice();
                    appCpp.nickName = textInput.text;
                    loginPage.loginButtonPressed();
                }

            }
        }

        Image {
            id: image
            y: 104
            width: 351
            height: 108
            anchors.left: textInput.right
            anchors.leftMargin: -450
            anchors.bottom: textInput.top
            anchors.bottomMargin: 110
            //fillMode: Image.PreserveAspectFit
            source: "qrc:/../icons/LanitIcon.png"
        }

        Label {
            id: label
            y: 267
            width: 160
            height: 29
            text: qsTr("Enter a nickname:")
            anchors.left: textInput.left
            anchors.leftMargin: 0
            anchors.bottom: textInput.top
            anchors.bottomMargin: 6
            font.pointSize: 9
        }


    }
}

/*##^##
Designer {
    D{i:4;anchors_x:350;anchors_y:336}D{i:5;anchors_x:125;anchors_y:336}D{i:6;anchors_x:125}
}
##^##*/
