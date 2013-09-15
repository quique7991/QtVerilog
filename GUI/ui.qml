import CustomComponents 1.0
import Qt 4.7

Rectangle {
    property bool evenClick : false

    anchors.fill: parent; color: "lightsteelblue"

    line {
        id: diagonalLine

        Behavior on x1 { NumberAnimation { duration: 1000 } }
        Behavior on y1 { NumberAnimation { duration: 1000 } }
        Behavior on x2 { NumberAnimation { duration: 1000 } }
        Behavior on y2 { NumberAnimation { duration: 1000 } }

        x1: parent.x + 20; y1: parent.height / 2
        x2: parent.width - 20; y2: parent.height / 2
        color: "tomato"; penWidth: 3; smooth: true
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(evenClick) { diagonalLine.x1 = mouseX; diagonalLine.y1 = mouseY }
            else { diagonalLine.x2 = mouseX; diagonalLine.y2 = mouseY }
            evenClick = !evenClick
        }
    }

    Text {
        id: textX1Y1
        anchors.left: parent.left; anchors.top: parent.top
        text: "x1: " + diagonalLine.x1 + " y1: " + diagonalLine.y1
    }

    Text {
        anchors.left: parent.left; anchors.top: textX1Y1.bottom; anchors.topMargin: 10
        text: "x2: " + diagonalLine.x2 + " y2: " + diagonalLine.y2
    }
}
