import QtQuick
import QtQuick.Controls

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
}
