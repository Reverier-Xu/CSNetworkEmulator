/**
 * File: gui_manager.h
 * Desc: user interface manager, exports managers to qml.
 * Date: 2021.12.26
 */

#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

#include "devices/bridge.h"
#include "devices/station_receiver.h"
#include "devices/station_sender.h"
#include "models/ui/logs_model.h"

class GuiManager : public QObject {
    Q_OBJECT
   private:
    QQmlApplicationEngine* mUiEngine;
    Bridge* mBridge;
    StationReceiver* mReceiver;
    StationSender* mSender;
    LogsModel* mSenderLogsModel;
    LogsModel* mReceiverLogsModel;

   protected:
    explicit GuiManager(QObject* parent);

    static GuiManager* mInstance;

   public:
    static GuiManager* instance(QObject* parent = nullptr);

    void createUI();

    void exportObjects();

    static void exportComponents();
};
