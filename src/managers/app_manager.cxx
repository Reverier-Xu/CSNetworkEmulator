/**
 * File: app_manager.cxx
 * Desc: the whole app manager.
 * Date: 2021.12.26
 */

#include "app_manager.h"

#include <QDir>
#include <QStandardPaths>
#include <QThread>

#include "gui_manager.h"
#include "models/frame.h"

void detectPaths();

AppManager::AppManager(QObject* parent) : QObject(parent) {}

void AppManager::initialize() {
    registerTypes();
    detectPaths();
    auto guiManager = GuiManager::instance(this);
    GuiManager::exportComponents();
    guiManager->exportObjects();
    guiManager->createUI();
}

void AppManager::registerTypes() { qRegisterMetaType<DataFrame>("DataFrame"); }

AppManager::~AppManager() {}

void detectPaths() {
    auto dataPath =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir;
    QStringList dataPaths = {"/Database"};
    for (auto& i : dataPaths)
        if (!dir.exists(dataPath + i)) dir.mkpath(dataPath + i);
}
