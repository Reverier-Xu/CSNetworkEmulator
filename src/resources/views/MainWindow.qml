import QtQuick 2.15
import QtQuick.Window 2.15
import QtGraphicalEffects 1.15
import "qrc:/components"

FluentWindow {
    id: window
    objectName: "mainWindow"
    width: 1500
    minimumWidth: 1500
    height: 900
    minimumHeight: 900

    Rectangle {
        id: centralWidget
        anchors.fill: parent
        anchors.margins: window.visibility === Window.Windowed ? 10 : 0
        border.width: window.visibility === Window.Windowed ? 1 : 0
        border.color: "#40606060"
        color: display.colorStyle? "white" : "black"

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

        ControlBar {
            id: controlBar
            anchors.left: parent.left
            anchors.top: titleBar.bottom
            anchors.right: parent.right
            anchors.leftMargin: window.visibility === Window.Windowed ? 1 : 0
            anchors.rightMargin: window.visibility === Window.Windowed ? 1 : 0
        }

        LogWindow {
            id: logWindow
            anchors.left: parent.left
            anchors.top: controlBar.bottom
            anchors.bottom: parent.bottom
            width: 600
            anchors.leftMargin: window.visibility === Window.Windowed ? 1 : 0
            anchors.bottomMargin: window.visibility === Window.Windowed ? 1 : 0
        }

        Player {
            id: player
            anchors.left: logWindow.right
            anchors.right: parent.right
            anchors.top: controlBar.bottom
            anchors.bottom: parent.bottom
            anchors.rightMargin: window.visibility === Window.Windowed ? 1 : 0
            anchors.bottomMargin: window.visibility === Window.Windowed ? 1 : 0
        }
    }
}
