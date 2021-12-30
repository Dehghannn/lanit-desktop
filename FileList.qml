import QtQuick 2.12
import QtQuick.Controls 2.12


Item {
    id: root
    width: 800
    height: 600
    property alias model: fileListview.model
    Rectangle{
        id: backGround
        anchors.fill: parent
        ListView{
            id: fileListview
            anchors.fill: parent
            delegate: FileItemDelegate{
                width: backGround.width
                height: 80
                fileName: model.FileName
                fileSize: model.FileSize
                isOwn: model.isOwn
                progress: model.Progress
            }
        }
    }


}
