#include "MainObject.hpp"

#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <iostream>
#include <sstream>

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QGuiApplication>

using QAPP = QGuiApplication;
#else
#include <QMessageBox>
#include <QApplication>

using QAPP = QApplication;
#endif

int main(int argc, char** argv) {
#ifdef Q_OS_ANDROID
	QQuickStyle::setStyle("Material");
#endif
#ifdef _WIN32
	QQuickStyle::setStyle("Universal");
#endif
	QAPP::setAttribute(Qt::AA_EnableHighDpiScaling);
	QAPP app(argc, argv);
	if (argc > 1) {
		std::cerr << "unknown option: " << argv[1] << std::endl;
		return EXIT_FAILURE;
	}
	app.setWindowIcon(QIcon(":/com.bixense.PasswordCalculator.svg"));
	std::stringstream errorMsg;
	QQmlApplicationEngine engine;
	engine.connect(&engine, &QQmlApplicationEngine::objectCreated,
	               [&errorMsg](QObject* const object, const QUrl&) {
		               if (!object) {
			               errorMsg << "Couldn't open QML file.\n";
		               }
	               });
	engine.connect(&engine, &QQmlApplicationEngine::warnings,
	               [&errorMsg](const QList<QQmlError>& warnings) {
		               for (const auto& warning : warnings) {
			               errorMsg << std::string(warning.description().toUtf8()) << "\n";
		               }
	               });
	engine.load("qrc:/main.qml");
	const auto errorStr = errorMsg.str();
	if (!errorStr.empty()) {
#ifdef Q_OS_ANDROID
		throw std::runtime_error(errorStr);
#else
		QMessageBox msgBox(QMessageBox::Critical, "Error", QString::fromUtf8(errorStr.c_str()));
		return msgBox.exec();
#endif
	}

	const auto rootObjects = engine.rootObjects();
	const auto firstRootObject = rootObjects.first();
	const auto button = firstRootObject->findChild<QObject*>("clipboardButton");
	MainObject main;
	button->connect(button, SIGNAL(qmlSignal(QString, QString)), &main,
	                SLOT(copyPassword(QString, QString)));

#ifdef Q_OS_ANDROID
	QtAndroid::hideSplashScreen(200);
#endif

	return app.exec();
}
