import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.0
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
         labelStepSize: 35
      }
   }
   sliderSetPointRpm.onPressedChanged: controlDialog.newSliderSetpoint(sliderSetPointRpm.value.toFixed(0))
   switchSetCtrlLoop.onCheckedChanged: controlDialog.closedLoopSwitch(switchSetCtrlLoop.checked)
}
