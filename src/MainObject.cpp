#include "MainObject.hpp"

#include "password.hpp"

#include <QClipboard>
#include <QGuiApplication>

void MainObject::copyPassword(const QString& alias, const QString& secret) {
	const auto pw = calculatePassword(secret.toUtf8().constData(), alias.toUtf8().constData());
	const auto clipboard = QGuiApplication::clipboard();
	clipboard->setText(QString::fromUtf8(pw.c_str()));
}
