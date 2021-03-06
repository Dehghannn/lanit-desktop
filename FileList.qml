import QtQuick 2.12
import QtQuick.Controls 2.12
import Qt.labs.qmlmodels 1.0


Item {
    id: root
    width: 800
    height: 600
    property alias model: fileListview.model
    Rectangle{
        id: backGround
        anchors.fill: parent
        color: "#00000000"
        ListView{
            id: fileListview
            anchors.fill: parent
            delegate: DelegateChooser{
                role: "State"                
                DelegateChoice{
                    roleValue: 0
                    FileRequestItemDelegate{
                        width: backGround.width
                        height: 80
                        fileName: model.FileName
                        fileSize: model.FileSize
                        isOwn: model.isOwn
                        time: model.TimeStamp
                        state: model.State
                        onAccepted: ChatHandler.activeFileList.acceptFile(index)
                        onRejected: ChatHandler.activeFileList.rejectFile(index)
                    }
                }
                DelegateChoice{
                    roleValue: 1
                    FileItemDelegate{
                        width: backGround.width
                        height: 80
                        fileName: model.FileName
                        fileSize: model.FileSize
                        isOwn: model.isOwn
                        state: model.State
                        progress: model.Progress
                        time: model.TimeStamp
                    }
                }
                DelegateChoice{
                    roleValue: 2
                    FileItemDelegate{
                        width: backGround.width
                        height: 80
                        fileName: model.FileName
                        fileSize: model.FileSize
                        isOwn: model.isOwn
                        state: model.State
                        progress: model.Progress
                        time: model.TimeStamp
                    }
                }
                DelegateChoice{
                    roleValue: 3
                    FileItemDelegate{
                        width: backGround.width
                        height: 80
                        fileName: model.FileName
                        fileSize: model.FileSize
                        isOwn: model.isOwn
                        state: model.State
                        progress: model.Progress
                        time: model.TimeStamp
                    }
                }
                DelegateChoice{
                    roleValue: 4
                    FileItemDelegate{
                        width: backGround.width
                        height: 80
                        fileName: model.FileName
                        fileSize: model.FileSize
                        isOwn: model.isOwn
                        state: model.State
                        progress: model.Progress
                        time: model.TimeStamp          
                    }
                }
            }
            model: ChatHandler.activeFileList
        }
    }
}
