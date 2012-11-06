import QtQuick 1.0

Rectangle {
    signal loadStarted(url address)

    id: main
    width: 800
    height: 600
    color: "steelblue"

    ServiceHeader {
        id: facebook_header
        width: 800
        text: "facebook"
        opacity: 0
    }

    FacebookAuthWeb {
        id: webcontent

        opacity: 0
        anchors.top: parent.top; anchors.left: facebook_header.left
        preferredWidth: main.width
        preferredHeight: main.height
        onLoadStarted: main.loadStarted(address)
    }

    FacebookStatusUpdatesView {
        id: statusview

        anchors.topMargin: 10
        anchors.top: main.bottom
        anchors.left: main.left
        width: main.width
        height: main.height
        model: statusModel
        clip: true
    }

    states: [
        State {
            name: "unauthorized"; when: authorizer.accessToken.length === 0
            PropertyChanges {
                target: webcontent
                opacity: 1
            }
        },
        State {
            name: "authorized"; when: authorizer.accessToken.length > 0
            PropertyChanges {
                target: facebook_header
                opacity: 1
            }
            AnchorChanges {
                target:  statusview
                anchors.top: facebook_header.bottom
            }
        }
    ]

    transitions: Transition {
        AnchorAnimation {
            duration:  1000
        }
    }
}
