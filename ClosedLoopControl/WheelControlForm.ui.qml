import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras.Private 1.0

Pane {
    id: item1
    property alias valuePowerText: valuePowerText
    property alias valueRpmText: valueRpmText
    property alias labelRpm: labelRpm
    property alias switchSetCtrlLoop: switchSetCtrlLoop
    property alias circularGaugePower: circularGaugePower
    property alias circularGaugeRpm: circularGaugeRpm
    property alias sliderSetPointRpm: sliderSetPointRpm

    GridLayout {
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        rows: 4
        columns: 3

        CircularGauge {
            id: circularGaugeRpm
            Layout.preferredHeight: 208
            Layout.preferredWidth: 346
            Layout.columnSpan: 1
            antialiasing: true
            stepSize: 0
            minimumValue: -350
            maximumValue: 350

            Text {
                id: valueRpmText
                text: "RPM: " + circularGaugeRpm.value
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                color: "White"
                font.pointSize: 10
            }
        }

        Item {
            id: spacer2
            Layout.fillWidth: true
            Layout.preferredHeight: 14
            Layout.preferredWidth: 14
        }

        CircularGauge {
            id: circularGaugePower
            Layout.preferredHeight: 208
            Layout.preferredWidth: 335
            antialiasing: true

            Text {
                id: valuePowerText
                text: "Power: "
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                color: "White"
                font.pointSize: 10
            }
        }

        Item {
            id: spacer1
            Layout.preferredHeight: 14
            Layout.preferredWidth: 14
        }

        Label {
            id: labelRpm
            text: qsTr("RPM Set Value")
            Layout.preferredHeight: 13
            Layout.preferredWidth: 165
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
        }

        Item {
            id: spacer3
            Layout.preferredHeight: 14
            Layout.preferredWidth: 14
        }

        Slider {
            id: sliderSetPointRpm
            spacing: 10
            Layout.columnSpan: 3
            Layout.preferredHeight: 40
            Layout.preferredWidth: 762
            to: 350
            from: -350
            value: 0
            snapMode: Slider.SnapOnRelease
        }

        Switch {
            id: switchSetCtrlLoop
            text: "Closed loop"
            checked: true
            Layout.columnSpan: 3
            Layout.preferredHeight: 40
            Layout.preferredWidth: 762
            transformOrigin: Item.Center
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
    }
}
