import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: root
    width: 800
    height: 100
    property alias fileName: fileName.text
    property bool isOwn: true
    property int  fileSize: 10000000
    property string time: "12:00"
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
                text: qsTr("movie.mkv")
                font.pointSize: 12
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                id: fileSize
                anchors.bottom: parent.bottom
                text: getProperFileSize(root.fileSize)
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
                text: qsTr("Accept")
                Material.foreground: Material.Green
                font.pointSize: 10
                onClicked: accepted()
            }
            Button{
                id: iRejectButton
                width: (parent.width - 5) / 3
                height: parent.height
                //anchors.verticalCenter: parent.verticalCenter
                flat: true
                text: qsTr("Reject")
                Material.foreground: Material.Red
                font.pointSize: 10
                onClicked: rejected()
            }
        }
    }
    function getProperFileSize(size){
        var prettySize;
        if(size < 990){
            return size + " Bytes";
        }else if(size >= 991 && size < 999900){
            prettySize = size / 1000;
            return prettySize + " KB";
        }else if(size >= 999901 && size < 999990000){ /// @todo complete this shit
                prettySize = size / 1000000
            return prettySize + " MB";
        }
    }
}
