import QtQuick 2.15
import "qrc:/components"

Rectangle {
    id: root
    color: "transparent"

    Rectangle {
        anchors.top: senderStation.bottom
        anchors.left: parent.left
        anchors.leftMargin: 48
        anchors.right: parent.right
        anchors.rightMargin: 48
        height: 4
        radius: height / 2
        color: display.themeColor
    }

    Rectangle {
        anchors.bottom: receiverStation.top
        anchors.left: parent.left
        anchors.leftMargin: 48
        anchors.right: parent.right
        anchors.rightMargin: 48
        height: 4
        radius: height / 2
        color: display.themeColor
    }

    Rectangle {
        id: senderStation
        color: "transparent"
        anchors.top: parent.top
        height: root.height / 4
        anchors.left: parent.left
        anchors.right: parent.right

        TextLabel {
            id: senderTitle
            anchors.left: parent.left
            anchors.leftMargin: 48
            anchors.top: parent.top
            anchors.topMargin: 32
            height: 48
            fontSize: 24
            iconSize: 24
            showIcon: true
            icon: "qrc:/assets/send.svg"
            text: "设备 - 数据发送方"
        }

        InputBox {
            id: senderInputBox
            anchors.verticalCenter: senderTitle.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 48
            width: 320
            height: 32
            placeholder: "请输入要发送的数据，然后按下回车"

            onInputFinished: {
                sender.prepareData(input);
                receiver.clear();
            }
        }

        Rectangle {
            id: senderWindowWidget
            anchors.verticalCenter: senderFrameList.verticalCenter
            border.width: 2
            border.color: display.themeColor
            color: "transparent"
            radius: 3
            width: sender.bufferSize * 32
            height: 32
            x: sender.bufferPosition * 32 + 50
            Behavior on x {
                NumberAnimation {
                    duration: 300
                    easing.type: Easing.OutQuad
                }
            }
        }

        ListView {
            id: senderFrameList
            clip: true
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 12
            height: 32
            model: sender
            orientation: ListView.Horizontal
            add: Transition {
                NumberAnimation { properties: "x"; from: 100; duration: 300; easing.type: Easing.OutExpo; }
                NumberAnimation { properties: "opacity"; from: 0; to: 1; duration: 200; }
            }
            addDisplaced: Transition {
                NumberAnimation { properties: "y"; duration: 200; easing.type: Easing.OutExpo; }
            }
            removeDisplaced: Transition {
                PauseAnimation { duration: 300; }
                NumberAnimation { properties: "y"; duration: 200 }
            }
            remove: Transition {
                NumberAnimation { properties: "x"; to: 100; duration: 300; easing.type: Easing.OutExpo; }
                NumberAnimation { properties: "opacity"; from: 1; to: 0; duration: 300; easing.type: Easing.OutExpo; }
            }
            delegate: FrameObject {
                frameStatus: frameState
            }
        }
    }

    Rectangle {
        id: receiverStation
        color: "transparent"
        anchors.bottom: parent.bottom
        height: root.height / 4
        anchors.left: parent.left
        anchors.right: parent.right

        TextLabel {
            id: receiverTitle
            anchors.left: parent.left
            anchors.leftMargin: 48
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 32
            height: 48
            fontSize: 24
            iconSize: 24
            showIcon: true
            icon: "qrc:/assets/download.svg"
            text: "设备 - 数据接收方"
        }

        ListView {
            id: receiverFrameList
            clip: true
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.top: parent.top
            anchors.topMargin: 12
            height: 32
            model: receiver
            orientation: ListView.Horizontal
            add: Transition {
                NumberAnimation { properties: "x"; from: 100; duration: 300; easing.type: Easing.OutExpo; }
                NumberAnimation { properties: "opacity"; from: 0; to: 1; duration: 200; }
            }
            addDisplaced: Transition {
                NumberAnimation { properties: "y"; duration: 200; easing.type: Easing.OutExpo; }
            }
            removeDisplaced: Transition {
                PauseAnimation { duration: 300; }
                NumberAnimation { properties: "y"; duration: 200 }
            }
            remove: Transition {
                NumberAnimation { properties: "x"; to: 100; duration: 300; easing.type: Easing.OutExpo; }
                NumberAnimation { properties: "opacity"; from: 1; to: 0; duration: 300; easing.type: Easing.OutExpo; }
            }
            delegate: FrameObject {
                frameStatus: frameState
            }
        }
    }

    FrameObject {
        id: sendingWithSuccessFrame
        frameColor: "transparent"

        ParallelAnimation {
            id: toSenderAnimation
            
            NumberAnimation {
                target: sendingWithSuccessFrame
                properties: "y"
                from: receiverStation.y + receiverFrameList.y
                to: senderStation.y + senderFrameList.y
                duration: 800
                easing.type: Easing.OutQuad
            }
            SequentialAnimation {
                ColorAnimation {
                    target: sendingWithSuccessFrame
                    properties: "frameColor"
                    from: "#808080"
                    to: "#009900"
                    duration: 400
                }
                PauseAnimation {
                    duration: 400
                }
                ColorAnimation {
                    target: sendingWithSuccessFrame
                    properties: "frameColor"
                    to: "transparent"
                    duration: 10
                }
            }
        }

        ParallelAnimation {
            id: toReceiverAnimation
            
            NumberAnimation {
                target: sendingWithSuccessFrame
                properties: "y"
                from: senderStation.y + senderFrameList.y
                to: receiverStation.y + receiverFrameList.y
                duration: 800
                easing.type: Easing.OutQuad
            }
            SequentialAnimation {
                ColorAnimation {
                    target: sendingWithSuccessFrame
                    properties: "frameColor"
                    from: "#808080"
                    to: "#009900"
                    duration: 400
                }
                PauseAnimation {
                    duration: 400
                }
                ColorAnimation {
                    target: sendingWithSuccessFrame
                    properties: "frameColor"
                    to: "transparent"
                    duration: 10
                }
            }
        }

        Connections {
            target: bridge
            function onToReceiver(id, ok) {
                if (ok) {
                    sendingWithSuccessFrame.x = id * 32 + 50
                    toSenderAnimation.stop()
                    toReceiverAnimation.start()
                }
            }
            function onToSender(id, ok) {
                if (ok) {
                    sendingWithSuccessFrame.x = id * 32 + 50
                    toReceiverAnimation.stop()
                    toSenderAnimation.start()
                }
            }
        }
    }

    FrameObject {
        id: sendingWithFailureFrame
        frameColor: "transparent"

        ParallelAnimation {
            id: toSenderFailedAnimation
            
            NumberAnimation {
                target: sendingWithFailureFrame
                properties: "y"
                from: receiverStation.y + receiverFrameList.y
                to: senderStation.y + senderFrameList.y
                duration: 800
                easing.type: Easing.OutQuad
            }
            SequentialAnimation {
                ColorAnimation {
                    target: sendingWithFailureFrame
                    properties: "frameColor"
                    from: "#808080"
                    to: "#AA0000"
                    duration: 400
                }

                ColorAnimation {
                    target: sendingWithFailureFrame
                    properties: "frameColor"
                    to: "transparent"
                    duration: 400
                    easing.type: Easing.InQuad
                }
            }
        }

        ParallelAnimation {
            id: toReceiverFailedAnimation
            
            NumberAnimation {
                target: sendingWithFailureFrame
                properties: "y"
                from: senderStation.y + senderFrameList.y
                to: receiverStation.y + receiverFrameList.y
                duration: 800
                easing.type: Easing.OutQuad
            }
            SequentialAnimation {
                ColorAnimation {
                    target: sendingWithFailureFrame
                    properties: "frameColor"
                    from: "#808080"
                    to: "#AA0000"
                    duration: 400
                }

                ColorAnimation {
                    target: sendingWithFailureFrame
                    properties: "frameColor"
                    to: "transparent"
                    duration: 400
                    easing.type: Easing.InQuad
                }
            }
        }

        Connections {
            target: bridge
            function onToReceiver(id, ok) {
                if (!ok) {
                    sendingWithFailureFrame.x = id * 32 + 50
                    toSenderFailedAnimation.stop()
                    toReceiverFailedAnimation.start()
                }
            }
            function onToSender(id, ok) {
                if (!ok) {
                    sendingWithFailureFrame.x = id * 32 + 50
                    toReceiverFailedAnimation.stop()
                    toSenderFailedAnimation.start()
                }
            }
        }
    }
}
