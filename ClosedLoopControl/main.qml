import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.0

ApplicationWindow {
   visible: true
   width: 800
   height: 480
   title: qsTr("Closed Loop Control Demo")
   Material.theme: Material.Dark
   Material.accent: Material.Blue
   Material.primary: Material.Blue
   Material.foreground: Material.Blue

   Component.onCompleted: {
       settingsDialog.load()
       settingsForm.spinBoxP.value = settingsDialog.p * 100
       settingsForm.spinBoxI.value = settingsDialog.i * 1000
       settingsForm.spinBoxD.value = settingsDialog.d * 100
       settingsForm.switchAutoConnect.checked = settingsDialog.autoConnect
   }

   SwipeView {
      id: swipeView
      anchors.fill: parent
      currentIndex: tabBar.currentIndex

      WheelControl{
         id: controlForm
      }

      Settings{
          id: settingsForm
      }
   }

   footer: TabBar {
      id: tabBar
      currentIndex: swipeView.currentIndex
      TabButton {
         text: qsTr("Control")
      }

      TabButton{
         text: qsTr("Settings")
      }
   }
}
