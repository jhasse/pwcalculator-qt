#include "MainObject.hpp"

#include "password.hpp"

#include <QClipboard>
#include <QGuiApplication>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras>

enum Duration { SHORT = 0, LONG = 1 };

void showToast(const QString& message, Duration duration = LONG) {
	// all the magic must happen on Android UI thread
	QtAndroid::runOnAndroidThread([message, duration] {
		QAndroidJniObject javaString = QAndroidJniObject::fromString(message);
		QAndroidJniObject toast = QAndroidJniObject::callStaticObjectMethod(
		    "android/widget/Toast", "makeText",
		    "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;",
		    QtAndroid::androidActivity().object(), javaString.object(), jint(duration));
		toast.callMethod<void>("show");
	});
}
#endif

void MainObject::copyPassword(const QString& alias, const QString& secret) {
	const auto pw = calculatePassword(secret.toUtf8().constData(), alias.toUtf8().constData());
	const auto clipboard = QGuiApplication::clipboard();
	clipboard->setText(QString::fromUtf8(pw.c_str()));
#ifdef Q_OS_ANDROID
	showToast(QStringLiteral("Password copied to clipboard."), SHORT);
#endif
}
