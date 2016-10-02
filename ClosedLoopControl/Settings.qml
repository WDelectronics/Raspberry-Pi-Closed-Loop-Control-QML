import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras.Private 1.0
import QtQml 2.2

SettingsForm {
    comboBoxBaud.onCurrentTextChanged: settingsDialog.setBaudIndex(comboBoxBaud.currentIndex)
    comboBoxPort.onCurrentTextChanged: settingsDialog.setPortIndex(comboBoxPort.currentIndex)
    switchAutoConnect.onClicked: settingsDialog.setAutoConnect(switchAutoConnect.checked)
    statusIndicatorCommunication.active: settingsDialog.connectionStatus
    comboBoxBaud.model: settingsDialog.getBaudInfo()
    comboBoxPort.model: settingsDialog.getPortInfo()
    comboBoxPort.currentIndex: settingsDialog.portIndex
    comboBoxBaud.currentIndex: settingsDialog.baudIndex
    buttonConnect.onPressed: settingsDialog.serialConnect(comboBoxPort.currentText, comboBoxBaud.currentText)
    buttonDisconnect.onPressed: settingsDialog.serialDisconnect()

    buttonSavePid.onPressed: settingsDialog.save()
    delayButtonSystemShutdown.onActivated: Qt.quit()

    spinBoxP.onValueChanged: settingsDialog.setP(spinBoxP.value / 100)
    spinBoxI.onValueChanged: settingsDialog.setI(spinBoxI.value / 1000)
    spinBoxD.onValueChanged: settingsDialog.setD(spinBoxD.value / 100)

    spinBoxP {
        editable: true
        validator: DoubleValidator {
            bottom: Math.min(spinBoxP.from, spinBoxP.to)
            top:  Math.max(spinBoxP.from, spinBoxP.to)
        }

        textFromValue: function( value, locale) {
            return Number(value / 100).toLocaleString( 'f', 2)
        }

        valueFromText: function(text, locale) {
            return Number.fromLocaleString(locale, text) * 100
        }
    }

    spinBoxI{
        editable: true
        validator: DoubleValidator {
            bottom: Math.min(spinBoxI.from, spinBoxI.to)
            top:  Math.max(spinBoxI.from, spinBoxI.to)
        }

        textFromValue: function( value, locale) {
            return Number(value / 1000).toLocaleString( 'f', 3)
        }

        valueFromText: function(text, locale) {
            return Number.fromLocaleString(locale, text) * 1000
        }
    }

    spinBoxD{
        editable: true
        validator: DoubleValidator {
            bottom: Math.min(spinBoxD.from, spinBoxD.to)
            top:  Math.max(spinBoxD.from, spinBoxD.to)
        }

        textFromValue: function( value, locale) {
            return Number(value / 100).toLocaleString( 'f', 2)
        }

        valueFromText: function(text, locale) {
            return Number.fromLocaleString(locale, text) * 100
        }
    }
}
