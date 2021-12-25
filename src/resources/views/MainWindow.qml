import QtQuick 2.15
import QtQuick.Window 2.15
import QtGraphicalEffects 1.15
import "qrc:/components"

FluentWindow {
    id: window
    objectName: "mainWindow"
    width: 1200
    minimumWidth: 1200
    height: 700
    minimumHeight: 700

    Rectangle {
        id: centralWidget
        anchors.fill: parent
        anchors.margins: window.visibility === Window.Windowed ? 10 : 0
        border.width: window.visibility === Window.Windowed ? 1 : 0
        border.color: "#40606060"
        color: display.colorStyle? "#e0e0e0" : "#151515"

        Behavior on color {
            ColorAnimation {
                duration: 280
            }
        }

        TitleBar {
            id: titleBar
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: window.visibility === Window.Windowed ? 1 : 0
            anchors.leftMargin: window.visibility === Window.Windowed ? 1 : 0
            anchors.rightMargin: window.visibility === Window.Windowed ? 1 : 0
        }

        // ControlBar {
        //     id: controlBar
        //     anchors.left: parent.left
        //     anchors.top: titleBar.bottom
        //     anchors.right: parent.right
        //     anchors.leftMargin: window.visibility === Window.Windowed ? 1 : 0
        //     anchors.rightMargin: window.visibility === Window.Windowed ? 1 : 0
        // }
    }
}
