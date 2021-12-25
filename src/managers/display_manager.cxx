/**
 * File: display_manager.cxx
 * Desc: display misc settings for user interface.
 * Date: 2021.12.26
 */


#include "display_manager.h"

#include <QApplication>
#include <QObject>
#include <QSettings>

DisplayManager* DisplayManager::mInstance = nullptr;

DisplayManager* DisplayManager::instance(QObject* parent) {
    if (mInstance == nullptr) mInstance = new DisplayManager(parent);
    return mInstance;
}

DisplayManager::DisplayManager(QObject* parent) : QObject(parent) {
    loadSettings();
}

DisplayManager::~DisplayManager() { saveSettings(); }

void DisplayManager::loadSettings() {
    QSettings settings;
    settings.beginGroup("Display");
    setThemeColor(settings.value("ThemeColor", "#0078d6").toString());
    setAlertColor(settings.value("AlertColor", "#ff6033").toString());
    setColorStyle(settings.value("ColorStyle", true).toBool());
    settings.endGroup();
}

void DisplayManager::saveSettings() const {
    QSettings settings;
    settings.beginGroup("Display");
    settings.setValue("ThemeColor", themeColor().name());
    settings.setValue("AlertColor", alertColor().name());
    settings.setValue("ColorStyle", colorStyle());
    settings.endGroup();

    settings.sync();
}

bool DisplayManager::colorStyle() const { return mColorStyle; }

void DisplayManager::setColorStyle(bool value) {
    mColorStyle = value;
    emit colorStyleChanged(value);
    emit contentColorChanged(contentColor());
}

QColor DisplayManager::themeColor() const { return mThemeColor; }

void DisplayManager::setThemeColor(const QColor& value) {
    mThemeColor = value;
    emit themeColorChanged(value);
}

void DisplayManager::setThemeColor(const QString& value) {
    mThemeColor.setNamedColor(value);
    emit themeColorChanged(value);
}

QColor DisplayManager::alertColor() const { return mAlertColor; }

void DisplayManager::setAlertColor(const QColor& value) {
    mAlertColor = value;
    emit alertColorChanged(value);
}

void DisplayManager::setAlertColor(const QString& value) {
    mAlertColor.setNamedColor(value);
    emit alertColorChanged(value);
}

QColor DisplayManager::contentColor() const {
    return colorStyle() ? QColor(0x222222) : QColor(0xdddddd);
}

void DisplayManager::setContentColor(const QColor& value) {
    emit contentColorChanged(contentColor());
}

