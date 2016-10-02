import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras.Private 1.0

Flickable{
    id: flick
    contentHeight: pane.implicitHeight
    property alias statusIndicatorCommunication: statusIndicatorCommunication
    property alias delayButtonSystemShutdown: delayButtonSystemShutdown
    property alias spinBoxD: spinBoxD
    property alias spinBoxI: spinBoxI
    property alias spinBoxP: spinBoxP
    property alias switchAutoConnect: switchAutoConnect
    property alias buttonDisconnect: buttonDisconnect
    property alias buttonConnect: buttonConnect
    property alias comboBoxBaud: comboBoxBaud
    property alias comboBoxPort: comboBoxPort
    property alias buttonSavePid: buttonSavePid

    Pane {
        id: pane
        anchors.fill: parent
        width: 800
        height: 480

        GridLayout {
            anchors.fill: parent
            rows: 2
            columns: 2

            GroupBox {
                id: groupBoxArduinoCom
                spacing: 1
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                bottomPadding: 8
                rightPadding: 8
                leftPadding: 8
                topPadding: 35
                Layout.fillHeight: true
                Layout.fillWidth: true
                title: qsTr("Arduino Communication")

                GridLayout {
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 0
                    columnSpacing: 2
                    rowSpacing: 0
                    anchors.fill: parent
                    rows: 6
                    columns: 6

                    Item {
                        id: spacer5
                        Layout.preferredWidth: 14
                        Layout.columnSpan: 3
                        Layout.preferredHeight: 14
                    }

                    ComboBox {
                        id: comboBoxPort
                        Layout.rowSpan: 2
                        Layout.columnSpan: 3
                    }

                    Label {
                        id: label1
                        text: qsTr("Serial Port")
                    }

                    Item {
                        id: spacer9
                        Layout.preferredWidth: 14
                        Layout.columnSpan: 3
                        Layout.preferredHeight: 14
                    }

                    ComboBox {
                        id: comboBoxBaud
                        Layout.columnSpan: 3
                        Layout.rowSpan: 2
                    }

                    Label {
                        id: label2
                        text: qsTr("Baud Rate")
                    }

                    Item {
                        id: spacer11
                        Layout.preferredWidth: 14
                        Layout.columnSpan: 2
                        Layout.preferredHeight: 14
                    }

                    Button {
                        id: buttonConnect
                        text: qsTr("Connect")
                        Layout.fillWidth: false
                        Layout.columnSpan: 2
                        Layout.preferredWidth: 120
                    }

                    Item {
                        id: spacer16
                        Layout.preferredWidth: 14
                        Layout.preferredHeight: 14
                    }

                    Button {
                        id: buttonDisconnect
                        text: qsTr("Disconnect")
                        Layout.columnSpan: 3
                        Layout.preferredWidth: 120
                    }

                    Switch {
                        id: switchAutoConnect
                        text: qsTr("Auto Connect")
                        Layout.columnSpan: 4
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: 207
                    }

                    Item {
                        id: spacer17
                        Layout.preferredWidth: 14
                        Layout.preferredHeight: 14
                    }

                    StatusIndicator {
                        id: statusIndicatorCommunication
                        color: "green"
                    }
                }
            }

            GroupBox {
                id: groupBoxPid
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 238
                Layout.preferredWidth: 322
                title: qsTr("Motor PID")

                GridLayout {
                    rowSpacing: 2
                    anchors.top: parent.top
                    anchors.topMargin: 2
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 2
                    anchors.left: parent.left
                    anchors.leftMargin: 2
                    anchors.right: parent.right
                    anchors.rightMargin: 2
                    rows: 5
                    columns: 3

                    Label {
                        id: label3
                        text: qsTr("P:")
                    }

                    Item {
                        id: spacer3
                        Layout.fillWidth: true
                        Layout.preferredWidth: 14
                        Layout.preferredHeight: 14
                    }

                    SpinBox {
                        id: spinBoxP
                        Layout.fillWidth: true
                        from: 0
                        value: 110
                        to: 100 * 100
                        stepSize: 1
                    }

                    Label {
                        id: label4
                        text: qsTr("I:")
                    }

                    Item {
                        id: spacer4
                        Layout.preferredWidth: 14
                        Layout.preferredHeight: 14
                    }

                    SpinBox {
                        id: spinBoxI
                        Layout.fillWidth: true
                        from: 0
                        value: 1100
                        to: 1000 * 1000
                        stepSize: 1
                    }

                    Item {
                        id: spacer1
                        Layout.preferredWidth: 14
                        Layout.preferredHeight: 14
                        Layout.columnSpan: 2
                    }

                    SpinBox {
                        id: spinBoxD
                        Layout.fillWidth: true
                        Layout.rowSpan: 2
                        from: 0
                        value: 110
                        to: 100 * 100
                        stepSize: 1
                    }

                    Label {
                        id: label5
                        text: qsTr("D:")
                        verticalAlignment: Text.AlignVCenter
                        Layout.columnSpan: 2
                        Layout.preferredHeight: 14
                        Layout.preferredWidth: 33
                    }

                    Item {
                        id: spacer2
                        Layout.preferredWidth: 14
                        Layout.preferredHeight: 14
                        Layout.columnSpan: 2
                    }

                    Button {
                        id: buttonSavePid
                        text: qsTr("Save")
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: 146
                    }
                }
            }

            GroupBox {
                id: groupBoxSystem
                Layout.columnSpan: 2
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 168
                Layout.preferredWidth: 601
                title: qsTr("System ")

                DelayButton {
                    id: delayButtonSystemShutdown
                    text: qsTr("Shut Down")
                    delay: 1500
                    anchors.fill: parent
                }
            }
        }
    }
    ScrollIndicator.vertical: ScrollIndicator { }
}
