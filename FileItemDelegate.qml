import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    width: 600
    height: 100
    property real progress: 60
    property alias fileName: fileName.text
    property bool isOwn: true
    property string  fileSize: "10 MB"
    property string time: "12:00"
    property int state: 0
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
            Text {
                id: fileName
                width: transferProgress.width - fileSize.width
                height: parent.height - transferProgress.height - 5
                anchors.left: transferProgress.left
                anchors.bottom: transferProgress.top
                text: qsTr("The_Red_Pill_2016_1080p_BrRip_YIFY_30NAMA.mkv")
                fontSizeMode: Text.HorizontalFit
                //font.pointSize: 10
                minimumPointSize: 8
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignBottom
            }
            Text {
                id: fileSize
                anchors.left: fileName.right
                anchors.leftMargin: 5
                anchors.bottom: fileName.bottom
                //anchors.right: transferProgress.right
//                height: fileName.height
                text: root.fileSize
                color: "gray"
                wrapMode: Text.WordWrap
                font.pointSize: 10
                verticalAlignment: Text.AlignBottom                
            }
        ProgressBar{
            id: transferProgress
            width: parent.width - 100
            height: parent.height *2 / 5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            from: 0
            to: 100
            value: root.progress
            visible: (root.state == 4)? false: true
        }
    }
}
