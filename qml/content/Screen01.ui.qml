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
        target: UiProcessor
        function onSocketsConnected() {
            rectangle.state = "login";
            console.log("Sockets connected");
        }
        function onPipesConnected() {
            rectangle.state = "chat";
            console.log("Pipes connected");
        }
        function onMailslotsConnected() {
            rectangle.state = "chat";
            console.log("Mailslots connected");
        }
    }

    Connections {
        target: ServerEventService
        function onShowServerDisconnected() {
            console.log("Lost connection with server")
            rectangle.state = "base"
        }
    }

    Connections {
        target: MessageHandler
        function onMessageReceived(sender, msg) {
            console.log("Appending message from client: ", sender, ": ", msg)
            const isMy = (name.text === sender)
            const msgAnchors = (isMy) ? "anchors.right: parent.right\n anchors.rightMargin: 0" : "anchors.left: parent.left\nanchors.leftMargin: 0"
            const msgBackgroundColor = (isMy) ? "white" : "#a61547"
            const msgColor = (isMy) ? "black" : "white"
            let msgWidth = Math.max(msg.length, Math.round(sender.length * 0.9)) * 12 + 15
            const msgHeight = Math.ceil(msgWidth / 350) * 20 + (isMy ? 20 : 30)
            msgWidth = Math.min(msgWidth, 350)
            const msgSender = sender

            const newObj = Qt.createQmlObject(`
                                              import QtQuick 2.0
                                              Item {
                                              width: 400
                                              height: ${msgHeight}

                                              Rectangle {
                                              id: message_sample
                                              width: ${msgWidth}
                                              height: ${msgHeight}
                                              radius: 15
                                              color: "${msgBackgroundColor}"
                                              ${msgAnchors}

                                              Text {
                                              id: sender
                                              visible: ${!isMy}
                                              font.bold: true
                                              color: "${msgColor}"
                                              text: "${msgSender}"
                                              anchors.left: parent.left
                                              anchors.top: parent.top
                                              anchors.leftMargin: 10
                                              anchors.topMargin: 5

                                              }

                                              Text {
                                              id: msg
                                              color: "${msgColor}"
                                              text: "${msg}"
                                              anchors.fill: parent
                                              font.pixelSize: 16
                                              wrapMode: Text.Wrap
                                              horizontalAlignment: Text.AlignHLeft
                                              verticalAlignment: Text.AlignVCenter
                                              anchors.rightMargin: 10
                                              anchors.leftMargin: 10
                                              anchors.bottomMargin: 10
                                              anchors.topMargin: ${isMy ? 10 : 20}
                                              }
                                              }
                                              }

                                              `, messages, "myDynamicSnippet")
            messages_scroll.ScrollBar.vertical.position = 1.0
        }
    }

    Connections {
        target: RegisterHandler
        function onFailedRegistration() {
            console.log("FAILED REGISTRATION")
            register_error.visible = true
            register_error.text = "This username is already used."
        }
        function onSuccessfulRegistration(receivedName) {
            console.log("SUCCESSFUL REGISTRATION")
            rectangle.state = "chat"
            name.text = receivedName
        }
    }

    Connections {
        target: LoginHandler
        function onFailedLogin() {
            console.log("FAILED LOGIN")
            register_error.visible = true
            register_error.text = "No such user found. Try again."
        }
        function onSuccessfulLogin(receivedName) {
            console.log("SUCCESSFUL LOGIN")
            rectangle.state = "chat"
            name.text = receivedName
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

            signal socketsClicked()

            Connections {
                target: sockets_btn
                function onClicked() {
                    sockets_btn.socketsClicked();
//                    rectangle.state = "login"
                }
            }
        }

        Button {
            id: pipes_btn
            objectName: "pipes_btn"
            height: 48
            text: qsTr("PIPES")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            flat: true
            highlighted: true

            signal pipesClicked()

            Connections {
                target: pipes_btn
                function onClicked() {
                    pipes_btn.pipesClicked();
                }
            }
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

            signal mailslotsClicked()

            Connections {
                target: mailslots_btn
                function onClicked() {
                    mailslots_btn.mailslotsClicked();
                }
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
                                /^[0-9A-Za-z_]+$/)) {
                        username_error.visible = true
                        username_error.text = "Name should be at least 3 character long \
and contain only latin letters or digits"
                        password_error.visible = false
                    } else if (password.length < 6 || !password.text.match(
                                   /^[0-9A-Za-z]+$/)) {
                        password_error.visible = true
                        password_error.text = "Password should be at least 6 character long \
and contain only latin letters or digits"
                        username_error.visible = false
                    } else {
                        login_btn.loginClicked(username.text, password.text)
                        username_error.visible = false
                        password_error.visible = false
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
        x: 169
        y: 20
        width: 286
        height: 40
        visible: false
        color: "#ffffff"
        text: qsTr("Username")
        font.pixelSize: 24
        horizontalAlignment: Text.AlignRight
        font.bold: true
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
                flat: false
                highlighted: false
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
                visible: true
                color: "#ffffff"
                text: qsTr("Username")
                font.pixelSize: 24
                horizontalAlignment: Text.AlignRight
                font.bold: true
            }

            PropertyChanges {
                target: messages_scroll
                x: 39
                y: 66
                visible: true
                anchors.topMargin: 56
                anchors.bottomMargin: 73
                anchors.rightMargin: 30
                anchors.leftMargin: 30
            }

            PropertyChanges {
                target: message
                placeholderText: "Type here..."
                placeholderTextColor: "#b3ffffff"
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
                    message.text = ""
                }
            }
        }
    }

    ScrollView {
        id: messages_scroll
        visible: false
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: name.top
        anchors.bottom: message_row.bottom
        anchors.bottomMargin: 0
        anchors.topMargin: 0

        Flow {
            id: messages
            width: 400
            anchors.fill: parent
            spacing: 10
        }
    }
}
