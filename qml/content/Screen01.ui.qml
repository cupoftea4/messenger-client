import QtQuick 2.0
import QtQuick.Controls
import Messanger
import QtQuick.Timeline 1.0

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height
    color: "#1b1b1b"

    Connections {
        target: MessageHandler
        function onMessageReceived(sender: string, msg: string) {
            console.log("Appending message from client: ", sender, ": ", msg);
        }
    }

    Connections {
        target: RegisterHandler
        function onFailedRegistration() {
            console.log("FAILED REGISTRATION");
        }
        function onSuccessfulRegistration() {
            console.log("SUCCESSFUL REGISTRATION");
        }
    }

    Connections {
        target: LoginHandler
        function onFailedLogin() {
            console.log("FAILED LOGIN");
        }
        function onSuccessfulLogin() {
            console.log("SUCCESSFUL LOGIN");
        }
    }
    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: timelineAnimation
                running: false
                loops: 1
                duration: 1000
                to: 1000
                from: 0
            }
        ]
        endFrame: 1000
        enabled: false
        startFrame: 0
    }

    Column {
        id: form
        width: 219
        height: 170
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Button {
            id: sockets_btn
            objectName: "sockets_btn"
            height: 48
            text: qsTr("SOCKETS")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            highlighted: true
            flat: false


            Connections {
                target: sockets_btn
                function onClicked() {
                    rectangle.state = "login"
                }
            }
        }

        Button {
            id: pipes_btn
            height: 48
            text: qsTr("PIPES")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            flat: true
            highlighted: true
        }

        Button {
            id: mailslots_btn
            objectName: "mailslots_btn"
            height: 48
            text: qsTr("MAILSLOTS")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            flat: true
            highlighted: true
            Connections {

            }
        }

        TextField {
            id: username
            visible: false
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            placeholderText: qsTr("Text Field")
            color: "white"
        }

        Text {
            id: username_error
            height: 20
            visible: false
            color: "#ff3a3a"
            text: qsTr("Error")
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 12
            wrapMode: Text.WordWrap
            anchors.leftMargin: 0
            anchors.rightMargin: 0
        }

        TextField {
            id: password
            echoMode: TextInput.Password
            visible: false
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            placeholderText: qsTr("Text Field")
            color: "white"
        }

        Text {
            id: password_error
            visible: false
            color: "#ff3a3a"
            text: qsTr("Text")
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 12
            wrapMode: Text.WordWrap
            anchors.rightMargin: 0
            anchors.leftMargin: 0
        }

        TextField {
            id: password_rep
            echoMode: TextInput.Password
            visible: false
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            placeholderText: qsTr("repeat password")
            color: "white"
        }

        Button {
            id: login_btn
            objectName: "login_btn"
            visible: false
            text: qsTr("LOG IN")
            anchors.left: parent.left
            anchors.right: parent.right
            highlighted: true
            anchors.rightMargin: 0
            anchors.leftMargin: 0

            signal loginClicked(string username, string password)


            Connections {
                target: login_btn

                function onClicked() {
                    if (username.length < 3 || !username.text.match(
                                /^[0-9a-z_]+$/)) {
                        username_error.visible = true
                        username_error.text = "Name should be at least 3 character long \
and contain only latin letters or digits"
                        password_error.visible = false
                    } else if (password.length < 6 || !password.text.match(
                                   /^[0-9a-z]+$/)) {
                        password_error.visible = true
                        password_error.text = "Password should be at least 6 character long \
and contain only latin letters or digits"
                        username_error.visible = false
                    } else {
                        // TODO: replace with the right signal
                        login_btn.loginClicked(username.text, password.text);
                        username_error.visible = false;
                        password_error.visible = false;
                    }
                }
            }
        }
        Button {
            id: register_btn
            objectName: "register_btn"
            visible: false
            text: qsTr("Register")
            anchors.left: parent.left
            anchors.right: parent.right
            flat: true
            highlighted: true
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            signal registerClicked(string username, string password)

            Connections {
                target: register_btn
                function onClicked() {
                    if (rectangle.state === "register") {
                        if (username.length < 3 || !username.text.match(
                                    /^[0-9a-z_]+$/)) {
                            username_error.visible = true
                            username_error.text = "Name should be at least 3 character long \
and contain only latin letters or digits"
                            password_error.visible = false
                        } else if (password.length < 6 || !password.text.match(
                                       /^[0-9a-z]+$/)) {
                            password_error.visible = true
                            password_error.text = "Password should be at least 6 character long \
and contain only latin letters or digits"
                            username_error.visible = false
                        } else if (password_rep.text !== password.text) {
                            password_error.visible = true
                            password_error.text = "Passwords do no match."
                            username_error.visible = false
                        } else {
                            // TODO: replace with the right signal
                            register_btn.registerClicked(username.text, password.text)
                        }
                    } else {
                        rectangle.state = "register"
                    }
                }
            }
        }

        Text {
            id: register_error
            visible: false
            color: "#ff3a3a"
            text: qsTr("Error")
            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: 12
            anchors.leftMargin: 0
            anchors.rightMargin: 0
        }
    }

    Button {
        id: back_btn
        x: 8
        y: 8
        visible: false
        text: qsTr("Back")
        flat: true

        Connections {
            target: back_btn
            function onClicked() {
                rectangle.state = "login"
            }
        }
    }

    Text {
        id: name
        text: qsTr("Text")
        font.pixelSize: 12
    }

    Flow {
        id: messages
        x: 39
        width: 400
        anchors.top: back_btn.bottom
        anchors.bottom: message_row.top
        anchors.topMargin: 10
        anchors.bottomMargin: 10
    }

    states: [
        State {
            name: "login"

            PropertyChanges {
                target: timeline
                enabled: true
            }

            PropertyChanges {
                target: timelineAnimation
                running: true
            }

            PropertyChanges {
                target: sockets_btn
                opacity: 1
                visible: false
                text: qsTr("SOCKETS")
                clip: false
            }

            PropertyChanges {
                target: pipes_btn
                visible: false
            }

            PropertyChanges {
                target: mailslots_btn
                visible: false
            }

            PropertyChanges {
                target: username
                visible: true
                placeholderTextColor: "#73ffffff"
                placeholderText: qsTr("username")
            }

            PropertyChanges {
                target: password
                visible: true
                placeholderTextColor: "#7affffff"
                placeholderText: qsTr("password")
                font.italic: true
                renderType: Text.NativeRendering
                hoverEnabled: true
            }

            PropertyChanges {
                target: login_btn
                visible: true
            }

            PropertyChanges {
                target: register_btn
                visible: true
                highlighted: true
                flat: true
            }

            PropertyChanges {
                target: rectangle
                clip: false
                antialiasing: false
            }

            PropertyChanges {
                target: username_error
                x: 130
                y: 274
                width: 219
                height: 30
                visible: false
                color: "#ff3a3a"
                text: qsTr("")
            }

            PropertyChanges {
                target: back_btn
                visible: false
                text: qsTr("Back")
                highlighted: false
                flat: true
            }

            PropertyChanges {
                target: message_row
                visible: false
            }

            PropertyChanges {
                target: password_error
                visible: false
            }
        },
        State {
            name: "register"
            PropertyChanges {
                target: timeline
                enabled: true
            }

            PropertyChanges {
                target: timelineAnimation
                running: true
            }

            PropertyChanges {
                target: sockets_btn
                opacity: 1
                visible: false
                text: qsTr("SOCKETS")
                clip: false
            }

            PropertyChanges {
                target: pipes_btn
                visible: false
            }

            PropertyChanges {
                target: mailslots_btn
                visible: false
            }

            PropertyChanges {
                target: username
                visible: true
                placeholderTextColor: "#73ffffff"
                placeholderText: qsTr("username")
            }

            PropertyChanges {
                target: password
                visible: true
                hoverEnabled: true
                font.italic: true
                renderType: Text.NativeRendering
                placeholderTextColor: "#7affffff"
                placeholderText: qsTr("password")
            }

            PropertyChanges {
                target: login_btn
                visible: false
            }

            PropertyChanges {
                target: register_btn
                visible: true
                flat: false
                highlighted: true
            }

            PropertyChanges {
                target: rectangle
                antialiasing: false
            }

            PropertyChanges {
                target: form
                visible: true
            }

            PropertyChanges {
                target: back_btn
                visible: true
                flat: false
            }

            PropertyChanges {
                target: password_rep
                visible: true
                placeholderTextColor: "#87ffffff"
                font.italic: true
            }

            PropertyChanges {
                target: message_row
                visible: false
            }

            PropertyChanges {
                target: username_error
                wrapMode: Text.WordWrap
            }
        },
        State {
            name: "chat"
            PropertyChanges {
                target: timeline
                enabled: true
            }

            PropertyChanges {
                target: timelineAnimation
                running: true
            }

            PropertyChanges {
                target: sockets_btn
                opacity: 1
                visible: false
                text: qsTr("SOCKETS")
                clip: false
            }

            PropertyChanges {
                target: pipes_btn
                visible: false
            }

            PropertyChanges {
                target: mailslots_btn
                visible: false
            }

            PropertyChanges {
                target: username
                visible: true
                placeholderTextColor: "#73ffffff"
                placeholderText: qsTr("username")
            }

            PropertyChanges {
                target: password
                visible: true
                placeholderTextColor: "#7affffff"
                hoverEnabled: true
                font.italic: true
                placeholderText: qsTr("password")
                renderType: Text.NativeRendering
            }

            PropertyChanges {
                target: login_btn
                visible: false
            }

            PropertyChanges {
                target: register_btn
                visible: true
                flat: false
                highlighted: true
            }

            PropertyChanges {
                target: rectangle
                antialiasing: false
            }

            PropertyChanges {
                target: form
                visible: false
            }

            PropertyChanges {
                target: back_btn
                visible: false
            }

            PropertyChanges {
                target: password_rep
                visible: true
                font.italic: true
            }

            PropertyChanges {
                target: message_row
                visible: true
            }

            PropertyChanges {
                target: name
                x: 151
                y: 24
                width: 297
                height: 36
                color: "#ffffff"
                text: qsTr("Username")
                font.pixelSize: 24
                horizontalAlignment: Text.AlignRight
                font.bold: true
            }
        }
    ]
    Row {
        id: message_row
        y: 572
        height: 42
        visible: false
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 25
        anchors.leftMargin: 25
        anchors.bottomMargin: 25

        TextField {
            id: message
            anchors.left: parent.left
            anchors.right: send_btn.left
            anchors.rightMargin: 15
            anchors.leftMargin: 0
            placeholderText: qsTr("Text Field")
            color: "white"
        }

        Button {
            id: send_btn
            objectName: "send_btn"
            text: qsTr("Send")
            anchors.right: parent.right
            font.capitalization: Font.Capitalize
            highlighted: true
            anchors.rightMargin: 0
            signal sendMessage(string message)
            Connections {
                function onClicked() {
                    send_btn.sendMessage(message.text)
                }
            }

        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}D{i:1}D{i:2}D{i:6}D{i:5}D{i:7}D{i:8}D{i:9}D{i:10}D{i:11}
D{i:12}D{i:13}D{i:15}D{i:14}D{i:17}D{i:16}D{i:18}D{i:4}D{i:20}D{i:19}D{i:21}D{i:22}
D{i:71}D{i:72}D{i:70}
}
##^##*/

