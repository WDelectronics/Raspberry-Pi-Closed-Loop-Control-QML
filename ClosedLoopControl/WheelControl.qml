import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras.Private 1.0

WheelControlForm {
    circularGaugePower.value: ((Math.abs(controlDialog.load) / 255.0) * 100.0)
    circularGaugePower {
        Behavior on value{
            NumberAnimation{
                easing.type: Easing.InQuad
                duration: 300
            }
        }
        onValueChanged: valuePowerText.text = "Power: " + circularGaugePower.value.toFixed(0) + "%"
    }

    circularGaugeRpm.value: controlDialog.rpm
    circularGaugeRpm{
        Behavior on value {
            NumberAnimation{
                easing.type: Easing.InQuad
                duration: 300
            }
        }

        onValueChanged: valueRpmText.text = "RPM: " + circularGaugeRpm.value.toFixed(0)

        style: CircularGaugeStyle {
            id: style
            labelStepSize: 50
        }
    }

    sliderSetPointRpm {
        background: Rectangle {
            x: sliderSetPointRpm.leftPadding
            y: sliderSetPointRpm.topPadding + sliderSetPointRpm.availableHeight / 2 - height / 2
            implicitWidth: 200
            implicitHeight: 4
            width: sliderSetPointRpm.availableWidth
            height: implicitHeight
            radius: 2
            color: "#bdbebf"

            Rectangle {
                x: parent.width/2
                width: (sliderSetPointRpm.visualPosition - 0.5)  * parent.width
                height: parent.height
                color: "#21be2b"
                radius: 2
            }

            Rectangle {
                x: parent.width/2
                width: ((sliderSetPointRpm.visualPosition - 0.5)  * -parent.width)
                height: parent.height
                color: "red"
                radius: 2

                transform: Scale{ origin.x: 0; origin.y: 0; xScale: -1}
            }
        }

        handle: Rectangle {
            x: sliderSetPointRpm.leftPadding + sliderSetPointRpm.visualPosition * (sliderSetPointRpm.availableWidth - width)
            y: sliderSetPointRpm.topPadding + sliderSetPointRpm.availableHeight / 2 - height / 2
            implicitWidth: 26
            implicitHeight: 26
            radius: 13
            color: sliderSetPointRpm.pressed ? "#f0f0f0" : "#f6f6f6"
            border.color: "#bdbebf"
        }

    }

    sliderSetPointRpm.onPositionChanged: {
        controlDialog.newSliderSetpoint(((sliderSetPointRpm.visualPosition-0.5)*700).toFixed(0))
        labelRpm.text = "RPM Set Value: " + ((sliderSetPointRpm.visualPosition-0.5)*700).toFixed(0)
    }
    switchSetCtrlLoop.onCheckedChanged: controlDialog.closedLoopSwitch(switchSetCtrlLoop.checked)

    labelRpm.visible: switchSetCtrlLoop.checked
}
