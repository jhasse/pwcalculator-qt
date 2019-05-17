import QtQuick 2.12
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12

ApplicationWindow
{
	id: mainWindow
	visible: true
	title: qsTr("Password Calculator")
	minimumWidth: gridLayout.implicitWidth + 20
	minimumHeight: gridLayout.implicitHeight + 20

	GridLayout {
		id: gridLayout
		anchors {
			horizontalCenter: parent.horizontalCenter
			top: parent.top
			topMargin: 10 + (parent.height - implicitHeight - 20) / 4
		}
		ColumnLayout {
			spacing: 10
			TextField {
				id: alias
				placeholderText: qsTr("Alias")
				selectByMouse: true
				Layout.fillWidth: true
				Keys.onReturnPressed: {
					// On Android this gets called when the users clicks "Next" on the virutal keyboard
					if (Qt.platform.os === "android") {
						secret.focus = true
					} else {
						clipboardButton.clicked()
					}
				}
				focus: true
				EnterKey.type: Qt.EnterKeyNext
			}

			TextField {
				id: secret
				placeholderText: qsTr("Secret")
				selectByMouse: true
				echoMode: TextInput.Password
				Layout.fillWidth: true
				Keys.onReturnPressed: clipboardButton.clicked()
			}

			Button {
				id: clipboardButton
				signal qmlSignal(string alias, string secret)
				onClicked: {
					qmlSignal(alias.text, secret.text)
					secret.text = ""
					mainWindow.showMinimized()
				}
				objectName: "clipboardButton"
				text: qsTr("Copy to clipboard")
				Layout.fillWidth: true
			}
		}
	}
}
