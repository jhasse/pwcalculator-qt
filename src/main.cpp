#include "MainObject.hpp"

#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <iostream>

int main(int argc, char** argv) {
#ifdef Q_OS_ANDROID
	QQuickStyle::setStyle("Material");
#endif
#ifdef _WIN32
	QQuickStyle::setStyle("Universal");
#endif
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);
	if (argc > 1) {
		std::cerr << "unknown option: " << argv[1] << std::endl;
		return EXIT_FAILURE;
	}
	app.setWindowIcon(QIcon(":/com.bixense.PasswordCalculator.svg"));
	QQmlApplicationEngine engine;
	engine.connect(&engine, &QQmlApplicationEngine::objectCreated,
	               [](QObject* const object, const QUrl&) {
		               if (!object) {
			               throw std::runtime_error("Couldn't open QML file.");
		               }
	               });
	engine.load("qrc:/main.qml");

	const auto rootObjects = engine.rootObjects();
	const auto firstRootObject = rootObjects.first();
	const auto button = firstRootObject->findChild<QObject*>("clipboardButton");
	MainObject main;
	button->connect(button, SIGNAL(qmlSignal(QString, QString)), &main,
	                SLOT(copyPassword(QString, QString)));

	return app.exec();
}
