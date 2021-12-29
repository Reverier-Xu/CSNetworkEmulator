import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import "qrc:/components"

Rectangle {
    id: root
    color: display.colorStyle ? "#10000000" : "#10FFFFFF"
    Behavior on color {
        ColorAnimation {
            duration: 280
        }
    }

    TextLabel {
        id: lostLabel
        anchors.top: parent.top
        anchors.topMargin: 12
        anchors.left: parent.left
        height: 32
        showIcon: true
        icon: "qrc:/assets/filter.svg"
        text: "网络丢包率 :  " + (lostSlider.currentValue * 100).toFixed(0) + "%"
    }

    SliderBar {
        id: lostSlider
        anchors.right: parent.right
        anchors.left: lostLabel.right
        anchors.leftMargin: 15
        anchors.rightMargin: 25
        anchors.verticalCenter: lostLabel.verticalCenter
        currentValue: bridge.lostRate
        onEndDragging: {
            bridge.lostRate = finalValue
        }
    }

    TextLabel {
        id: senderLogTips
        anchors.left: parent.left
        anchors.top: lostLabel.bottom
        height: 44
        showIcon: true
        icon: "qrc:/assets/send.svg"
        text: "发送方日志"
    }

    Rectangle {
        id: senderLogWindow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: senderLogTips.bottom
        height: (parent.height - 132) / 2
        color: display.colorStyle?"#20000000":"#10808080"

        ListView {
            id: senderLogList
            clip: true
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            model: senderLogsModel
            ScrollBar.vertical: UXScrollBar { }

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
            delegate: LogsItem {
                width: ListView.view.width
                theId: index
                contentLog: logMessage
                contentLogColor: logColor
                timeLog: logTime
            }
        }
    }

    TextLabel {
        id: receiverLogTips
        anchors.top: senderLogWindow.bottom
        anchors.left: parent.left
        height: 44
        showIcon: true
        icon: "qrc:/assets/download.svg"
        text: "接收方日志"
    }

    Rectangle {
        id: receiverLogWindow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: receiverLogTips.bottom
        anchors.bottom: parent.bottom
        color: display.colorStyle?"#20000000":"#10808080"

        ListView {
            id: receiverLogList
            clip: true
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            model: receiverLogsModel
            ScrollBar.vertical: UXScrollBar { }

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
            delegate: LogsItem {
                width: ListView.view.width
                theId: index
                contentLog: logMessage
                contentLogColor: logColor
                timeLog: logTime
            }
        }
    }

    Rectangle {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.right
        width: 1
        color: "#30606060"
    }
}
