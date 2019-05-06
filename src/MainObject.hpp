#pragma once

#include <QObject>

class MainObject : public QObject {
	Q_OBJECT
public slots:
	void copyPassword(const QString& alias, const QString& secret);
};
