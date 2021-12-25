/**
 * File: app_manager.cxx
 * Desc: the whole app manager.
 * Date: 2021.12.26
 */


#include <QDir>
#include <QStandardPaths>
#include <QThread>

#include "app_manager.h"
#include "gui_manager.h"
#include "models/frame.h"

void detectPaths();

AppManager::AppManager(QObject* parent) : QObject(parent) {}

void AppManager::initialize() {
    registerTypes();
    detectPaths();
    auto guiManager = GuiManager::instance(this);
    GuiManager::exportComponents();
    guiManager->exportManagers();
    guiManager->createUI();

}

void AppManager::registerTypes() { qRegisterMetaType<DataFrame>("DataFrame"); }

AppManager::~AppManager() {}

void detectPaths() {
    auto dataPath =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    auto cachePath =
        QStandardPaths::writableLocation(QStandardPaths::TempLocation) +
        "/CSNetworkEmulator";
    QDir dir;
    QStringList dataPaths = { "/Database" };
    QStringList cachePaths = { "/Covers", "/CachedSongs" };
    for (auto& i : dataPaths)
        if (!dir.exists(dataPath + i)) dir.mkpath(dataPath + i);
    for (auto& i : cachePaths)
        if (!dir.exists(cachePath + i)) dir.mkpath(cachePath + i);
}
