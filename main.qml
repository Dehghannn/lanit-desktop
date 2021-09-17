import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.13
import QtPositioning 5.14
import QtQuick.Controls.Material 2.3
import Qt.labs.platform 1.1
Window {
    id: window
    visible: true
    width: 800
    height: 600
    minimumHeight: 600
    minimumWidth: 800
    onHeightChanged:  {
    console.log("height is " + window.height);
        console.log("width is " + window.width);
    }
    title: qsTr("Lanit")

    SystemTrayIcon{
        id: sysTray
        visible: true
        icon.source: "qrc:/icons/icons8-l-100.png"
        onActivated: {

            window.show()
            window.raise()
            window.requestActivate()
        }
    }

    StackView{
        id: stackView
        anchors.fill: parent

        initialItem:  LoginPage{
            id: loginPage
            anchors.fill : parent
            onLoginButtonPressed: {
                stackView.push(mainPage);
            }
        }
        MainPage{
            id: mainPage
            anchors.fill: parent

        }



    }

}
