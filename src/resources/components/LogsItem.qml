import QtQuick 2.15
import QtGraphicalEffects 1.15

PushArea {
    id: root
    property int theId: 0
    property color contentLogColor: display.contentColor
    property string contentLog: ""
    property string timeLog: ""
    flat: true

    height: 36

    Rectangle {
        anchors.fill: parent
        color: theId % 2 == 0 ? "#20808080" : "transparent"
    }

    Text {
        id: idLabel
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 15
        color: "#808080"
        text: (root.theId + 1).toString().padStart(3, '0')
        font.pixelSize: 16
    }

    Text {
        id: durationLabel
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.verticalCenter: parent.verticalCenter
        color: "#808080"
        font.pixelSize: 16
        text: timeLog
    }

    TextMetrics {
        id: titleMetrics
        elide: Text.ElideRight
        font.pixelSize: 16
        text: root.contentLog
        elideWidth: titleLabel.width
    }

    Text {
        id: titleLabel
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: idLabel.right
        anchors.right: durationLabel.left
        anchors.leftMargin: 15
        anchors.rightMargin: 25
        font.pixelSize: 16
        color: root.contentLogColor
        text: titleMetrics.elidedText
    }
}
