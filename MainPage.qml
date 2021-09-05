import QtQuick 2.9
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.3
import QtPositioning 5.14

Page {
    id: loginPage
    width: 800
    height: 600
    Rectangle{
        id: rectangle
        color: "#dee3e5"
        anchors.fill: parent

        Rectangle {
            id: usersHolderRect
            width: 148
            color: "#ffffff"
            //radius: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 50
            clip: true
            z: 2
            Rectangle{
                id: headerRect
                z: 1
                height: 40
                clip: true
                radius: 0
                width: parent.width
                color: "#00695c"
                Text {

                    anchors.centerIn: parent
                    id: header
                    color: "#f1f5fd"
                    text: qsTr("Users")
                    styleColor: "#91badc"
                    z: 3
                }
            }
            ListView{
                id: userListView
                width: parent.width
                height: parent.height - headerRect.height
                property bool initState: true
                y : headerRect.height
                spacing: 0
                clip: true
                currentIndex: -1
                populate: Transition {
                        NumberAnimation { properties: "x,y"; duration: 1000 }
                    }
                onModelChanged: {
                    if(initState)
                    {
                        currentIndex = -1;
                    }
                }
                model: appCpp.userList
                delegate: UserDelegate{
                    width: userListView.width
                    height: 50
                    text: model.modelData.nickName
                    isOnline: model.modelData.isOnline
                    highlighted: (userListView.currentIndex === index) ? true : false
                    onPressed: {
                        userListView.currentIndex = index;
                        userListView.initState = false;                        
                        ChatHandler.startNewChat(model.modelData.userIP);

                    }

                }

            }
        }

        Rectangle {
            id: chatHolderRect
            color: "#ffffff"
            anchors.left: usersHolderRect.right
            anchors.leftMargin: 1
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.right: parent.right
            anchors.rightMargin: 0
            Rectangle{
                id: chatArea
                width: parent.width
                height: parent.height - typeArea.height
                color: "#80cbc4"
                ListView{
                    id: chatListView
                    anchors.fill: parent
                    clip: true
                    spacing: 10
                    snapMode: ListView.NoSnap
                    model: ChatHandler.activeChat
                    flickableDirection: Flickable.AutoFlickIfNeeded
                    delegate: MessageDelegate{
                        width: parent.width
                        text: display
                        isOwn: decoration
                      //  timeStamp: statusTip
                        ScrollBar {
                                 id: vbar
                                 hoverEnabled: true
                                 active: hovered || pressed
                                 orientation: Qt.Vertical
                                 size: chatListView.height //frame.height / content.height
                                 anchors.top: parent.top
                                 anchors.right: parent.right
                                 anchors.bottom: parent.bottom
                                 /// @todo fix scrollbar
                             }
                    }
                    onModelChanged: positionViewAtEnd();
                    Component.onCompleted: positionViewAtEnd();
                }
            }

            Rectangle {
                property int maxHeight: 200
                id: typeArea
                width: parent.width
                y: parent.height - height
                height: textArea.height
                color: "#f1f5fd"
                ScrollView{
                    x: 10
                    y: 0
                    clip: true
                    width: parent.width - 150
                    height: textArea.height
                    TextArea {
                        id: textArea
                        x: 10
                        y: 0
                        clip: true
                        font.pointSize: 10
                        rightPadding: 10
                        width: parent.width
                        height:  contentHeight + 50 // 72
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        placeholderText: qsTr("Type here")
                        //flickable: true
                    }
                }

                RoundButton {
                    id: sendButton
                    x: parent.width - width
                    y: 0
                    width: height
                    height: 66 //parent.height but not binded
                    Component.onCompleted: console.log(height)
                    text: qsTr("Button")
                    flat: true
                    anchors.bottom: parent.bottom
                    display: AbstractButton.IconOnly
                    icon.source: "qrc:/../icons/sendIcon.png"
                    icon.width: height
                    icon.height: height
                    icon.color: Material.color(Material.Teal, Material.Shade800)
                    onClicked: {
                        /// new outgoing message here
                        ChatHandler.newOutgoingTextMessageChatHandler(textArea.text);
                        textArea.text = "";
                    }
                }
                RoundButton {
                    id: attatchmentButton
                    x: parent.width - 2*width
                    y: 0
                    width: height
                    height: 66 //parent.height but not binded
                    Component.onCompleted: console.log(height)
                    text: qsTr("Button")
                    flat: true
                    anchors.bottom: parent.bottom
                    display: AbstractButton.IconOnly
                    icon.source: "qrc:/../icons/attatchmentIcon.png"
                    icon.width: height
                    icon.height: height
                    icon.color: Material.color(Material.Teal, Material.Shade800)
                }
            }
        }


    }
}

/*##^##
Designer {
    D{i:3;anchors_height:513;anchors_y:43}D{i:5;anchors_height:513;anchors_y:43}D{i:2;anchors_height:513;anchors_x:32;anchors_y:43}
}
##^##*/
