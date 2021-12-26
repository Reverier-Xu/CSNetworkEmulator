/**
 * File: entry.cxx
 * Desc: entry point of the whole application.
 * Date: 2021.12.26
 */


#include <QApplication>
#include <QObject>
#include <QIcon>
#include <QFont>

#include "managers/app_manager.h"


int main(int argc, char* argv[]) {
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QApplication app(argc, argv);

	QApplication::setApplicationDisplayName("Network Emulator");
	QApplication::setApplicationName("Network Emulator");
	QApplication::setOrganizationName("Wootec");
	QApplication::setOrganizationDomain("woooo.tech");
	QApplication::setWindowIcon(QIcon(":/assets/simulation.svg"));
#ifdef Q_OS_WINDOWS
	QApplication::setFont(QFont("Microsoft YaHei UI"));
#endif

	auto main_app = AppManager();
	main_app.initialize();

	return QApplication::exec();
}
