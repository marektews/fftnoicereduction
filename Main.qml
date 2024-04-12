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

    Label {
        anchors.centerIn: parent
        text: "Fake text"
    }

    Button {
        id: loadButton
        text: "Open Audio File"
        onClicked: fileDialog.open()
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
}
