#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char** argv) {
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	engine.connect(&engine, &QQmlApplicationEngine::objectCreated,
	               [](QObject* const object, const QUrl&) {
		               if (!object) {
			               throw std::runtime_error("Couldn't open QML file.");
		               }
	               });
	engine.load("qrc:/main.qml");
	return app.exec();
}
