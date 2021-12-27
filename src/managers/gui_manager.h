/**
 * File: gui_manager.h
 * Desc: user interface manager, exports managers to qml.
 * Date: 2021.12.26
 */

#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

class GuiManager : public QObject {
    Q_OBJECT
   private:
    QQmlApplicationEngine* mUiEngine;

   protected:
    explicit GuiManager(QObject* parent);

    static GuiManager* mInstance;

   public:
    static GuiManager* instance(QObject* parent = nullptr);

    void createUI();

    void exportManagers();

    static void exportComponents();
};
