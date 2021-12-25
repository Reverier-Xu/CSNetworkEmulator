/**
 * File: gui_manager.cxx
 * Desc: user interface manager, exports managers to qml.
 * Date: 2021.12.26
 */

#include "gui_manager.h"

#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QQmlContext>

#include "display_manager.h"

GuiManager* GuiManager::mInstance = nullptr;

GuiManager::GuiManager(QObject* parent) : QObject(parent) {
    mUiEngine = new QQmlApplicationEngine(this);
}

void GuiManager::createUI() {
    const QUrl url(QStringLiteral("qrc:/views/MainWindow.qml"));
    mUiEngine->load(url);
}

void GuiManager::exportManagers() {
    mUiEngine->rootContext()->setContextProperty(
        "display", DisplayManager::instance(this->parent()));
}

GuiManager* GuiManager::instance(QObject* parent) {
    if (mInstance == nullptr) mInstance = new GuiManager(parent);
    return mInstance;
}

void GuiManager::exportComponents() {
    // qmlRegisterType<SOMETYPES>("Reverier.SOMETYPES", 1, 0, "SOMETYPES");
}
