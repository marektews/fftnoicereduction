import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("FFT Noice Reduction v1.0")

    AudioFileSourcer {
        id: audioFileSourcer
    }

    FileDialog {
        id: fileDialog
        fileMode: FileDialog.OpenFile
        nameFilters: ["*.wav files (*.wav)"]
        onSelectedFileChanged: console.log("File selected:", fileDialog.selectedFile)
        onAccepted: {
            console.log("File accepted:", fileDialog.selectedFile)
            audioFileSourcer.filename = fileDialog.selectedFile
        }
    }

    Frame {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.verticalCenter

        Button {
            id: loadButton
            z: 1
            text: "Open Audio File"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 0
            anchors.topMargin: 0
            onClicked: fileDialog.open()
        }

        WaveShapeView {
            id: waveShapeView
            audioRealBuffer: audioFileSourcer.audioRealBuffer
            anchors.fill: parent
            clip: true
        }
    }
}
