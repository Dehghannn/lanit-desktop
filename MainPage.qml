import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtPositioning 5.14
import QtQuick.Dialogs 1.2

Page {
    id: loginPage
    width: 800
    height: 600
    Rectangle{
        id: rectangle
        //color: Material.color(Material.Teal, Material.Shade400) //"#dee3e5"
        anchors.fill: parent
        Rectangle{
            id: topBar
            width: 149
            height: 50
            color: Material.color(Material.Teal, Material.Shade900)
            Button{
                id: hamburgerButton
                anchors.centerIn: parent
                width: 50
                height: 50
                display: AbstractButton.IconOnly
                flat: true
                icon.source: "qrc:/icons/menu.png"
                icon.color: "white"
                icon.width: 45
                icon.height: 45
            }

        }

        Rectangle {
            id: usersHolderRect
            width: 148
            color: "#ffffff"
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
                color: "#39796b"
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
                        chatListView.update();

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
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            Rectangle{
                id: chatTopBar
                height: 50
                width: parent.width
                anchors.right: parent.right
                anchors.bottom: chatArea.top
                z: 2
                color: Material.color(Material.Teal, Material.Shade900);
                Text {
                    id: connectionStatus
                    text: {
                        if(userListView.initState){
                            return "No Chat Selected"
                        }else{
                            return ChatHandler.activeChat.connectionState
                        }
                    }
                    font.pointSize: 8
                    color: Material.color(Material.Teal, Material.Shade100)
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                }

            }
            Rectangle{
                id: chatArea
                width: parent.width
                height: parent.height - typeArea.height - chatTopBar.height
                y: chatTopBar.height
                color: "#c8dcdb"
                ScrollView{
                    id: scrollView
                    contentWidth: -1
                    anchors.fill: parent

                    ListView{
                        id: chatListView
                        width: scrollView.width
                        height: scrollView.height
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.topMargin: 4
                        anchors.bottomMargin: 3
                        clip: true
                        spacing: 10
                        model: ChatHandler.activeChat
                        //flickableDirection: Flickable.AutoFlickIfNeeded
                        delegate: MessageDelegate{
                            width: chatListView.width
                            text: message
                            isOwn: ownership
                            timeStamp: time                                                  
                        }
                        onContentHeightChanged: positionViewAtEnd();
                        onModelChanged: positionViewAtEnd();
                        Component.onCompleted: positionViewAtEnd();
                    }
                    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                    //ScrollBar.horizontal.snapMode: ScrollBar.SnapOnRelease
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
                    height: contentHeight + 15
                    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                    TextArea {
                        id: textArea
                        x: 10
                        y: 0
                        clip: true
                        font.pointSize: 12
                        rightPadding: 10
                        width: typeArea.width -150
                        height:  contentHeight + 50 // 72
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        function _onEnterKeyPressed(event) {
                            if(!(event.modifiers & Qt.ShiftModifier)){
                                sendButton.clicked()
                            }else{
                                event.accepted = false;
                            }
                        }
                        Keys.onReturnPressed: _onEnterKeyPressed(event)
                        Keys.onEnterPressed: _onEnterKeyPressed(event)

                        /// @todo fix sending by pressing enter
                        placeholderText: qsTr("Write a message here...")
                        //onAccepted: sendButton.clicked()
                        //flickable: true
                    }
                }

                RoundButton {
                    id: sendButton                    
                    x: parent.width - width
                    y: 0
                    enabled: {
                        if(textArea.text === ""){
                            return false;
                        }else{
                            return true;
                        }
                    }
                    width: height
                    height: 66 //parent.height but not binded
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
                        var inputText = textArea.text.trim();
                        if(inputText !== ""){
                            ChatHandler.newOutgoingTextMessageChatHandler(inputText);
                            chatListView.update();
                            textArea.clear();
                        }
                    }
                }
                RoundButton {
                    id: attatchmentButton
                    x: parent.width - 2*width
                    y: 0
                    width: height
                    height: 66 //parent.height but not binded
                    text: qsTr("Button")
                    flat: true
                    anchors.bottom: parent.bottom
                    display: AbstractButton.IconOnly
                    icon.source: "qrc:/../icons/attatchmentIcon.png"
                    icon.width: height
                    icon.height: height
                    icon.color: Material.color(Material.Teal, Material.Shade800)
                    onClicked: {
                        appCpp.getAttachedFile();

                    }
                }
            }
        }


    }
    Connections{
        target: ChatHandler
        function onNewMessageNotification( IP,text) { /// @todo make notification look better
            if(!window.active){
                var nickname = appCpp.getNickNamebyIP(IP);
                sysTray.showMessage("New Message", nickname + " says: " + text);
            }
        }
    }
//    FileDialog{
//        id: fileDialog
//        folder: shortcuts.home

//        onAccepted: {
//            //handle file input here

//        }
//        title: "Choose a file"
//    }
}


