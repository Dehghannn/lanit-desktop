import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Item {
    id: root
    width: 800
    height: 100
    property real progress: 60
    property alias fileName: fileName.text
    property bool isOwn: true
    property var  fileSize: 10000000
    Rectangle{
        id: backGround
        color: "#868f96"
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#e3fdf5"
            }

            GradientStop {
                position: 1
                color: "#ffe6fa"
            }
        }
        border.width: 0.1
        border.color: "#868f96"
        Row{
            id: textRow
            width: transferProgress.width
            height: parent.height * 3 / 5
            anchors.top: parent.top
            anchors.bottom: transferProgress.top
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Text {
                id: fileName
                text: qsTr("movie.mkv")
                font.pointSize: 20
                anchors.bottom: parent.bottom
                verticalAlignment: Text.AlignBottom
            }
            Text {
                id: fileSize
                anchors.bottom: parent.bottom
                text: getProperFileSize(root.fileSize)
                color: "gray"
                font.pointSize: 14
                verticalAlignment: Text.AlignBottom
            }
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
            visible: (value == 100)? false: true
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
