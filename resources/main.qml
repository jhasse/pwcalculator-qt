import QtQuick 2.1
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
		anchors.centerIn: parent
		ColumnLayout {
			spacing: 10
			TextField {
				id: alias
				placeholderText: qsTr("Alias")
				selectByMouse: true
				Layout.fillWidth: true
			}

			TextField {
				id: secret
				placeholderText: qsTr("Secret")
				selectByMouse: true
				echoMode: TextInput.Password
				Layout.fillWidth: true
			}

			Button {
				signal qmlSignal(string alias, string secret)
				onClicked: {
					qmlSignal(alias.text, secret.text)
					mainWindow.showMinimized()
				}

				objectName: "clipboardButton"
				text: qsTr("Copy to clipboard")
				Layout.fillWidth: true
			}
		}
	}
}
