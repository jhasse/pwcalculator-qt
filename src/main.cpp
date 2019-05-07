#include "MainObject.hpp"

#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>

int main(int argc, char** argv) {
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);
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
