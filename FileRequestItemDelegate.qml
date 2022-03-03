import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: root
    width: 800
    height: 100
    property alias fileName: fileName.text
    property bool isOwn: true
    property string  fileSize: "10 MB"
    property string time: "12:00"
    property int state: 0
    signal accepted()
    signal rejected()
    Pane{
        id: backGround
        //color: "#868f96"
        Material.background: Material.color(Material.Teal, Material.Shade50)
        Material.elevation: 1
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.rightMargin: 1
        anchors.leftMargin: 1
        anchors.topMargin: 1
        Column{
            id: iTextColumn
            width: parent.width *2 / 3
            height: parent.height
            anchors.top: parent.top
            anchors.left: parent.left
            spacing: 10
            Text {
                id: fileName
                width: ProgressBar.width - fileSize.width
                height: parent.height - ProgressBar.height - 5
                text: qsTr("movie.mkv")
                fontSizeMode: Text.Fit
                wrapMode: Text.WordWrap
                maximumLineCount: 2
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                id: fileSize
                //anchors.bottom: parent.bottom
                text: root.fileSize
                width: 40
                color: "gray"
                font.pointSize: 10
                verticalAlignment: Text.AlignVCenter
            }
        }
        Row{
            id: iButtonRow
            width: parent.width / 3
            height: parent.height
            spacing: 20
            anchors.left: iTextColumn.right
            leftPadding: (width - (2 *iAcceptButton.width) - spacing) / 2
            rightPadding: leftPadding
            Button{
                id: iAcceptButton
                width: (parent.width - 5 ) / 3
                height: parent.height
                //anchors.verticalCenter: parent.verticalCenter
                flat: true
                text: "\uf00c"
                font.family: "Font Awesome 6 Pro"
                Material.foreground: Material.Green
                font.pointSize: 20
                onClicked: accepted()
            }
            Button{
                id: iRejectButton
                width: (parent.width - 5) / 3
                height: parent.height
                //anchors.verticalCenter: parent.verticalCenter
                flat: true
                text: "\uf00d"
                font.family: "Font Awesome 6 Pro"
                Material.foreground: Material.Red
                font.pointSize: 20
                onClicked: rejected()
            }
        }
    }
}
