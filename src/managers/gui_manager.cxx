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
    mBridge = new Bridge(this);
    mReceiver = new StationReceiver(this);
    mSender = new StationSender(this);
    mSenderLogsModel = new LogsModel(this);
    mReceiverLogsModel = new LogsModel(this);
    mSender->setLogsModel(mSenderLogsModel);
    mReceiver->setLogsModel(mReceiverLogsModel);
    connect(mBridge, &Bridge::senderReceived, mSender, &StationSender::onFrameReceived);
    connect(mBridge, &Bridge::receiverReceived, mReceiver, &StationReceiver::onFrameReceived);
    connect(mSender, &StationSender::frameSendRequested, mBridge, &Bridge::onSenderRequested);
    connect(mReceiver, &StationReceiver::frameSendRequested, mBridge, &Bridge::onReceiverRequested);
}

void GuiManager::createUI() {
    const QUrl url(QStringLiteral("qrc:/views/MainWindow.qml"));
    mUiEngine->load(url);
}

void GuiManager::exportObjects() {
    mUiEngine->rootContext()->setContextProperty(
        "display", DisplayManager::instance(this->parent()));
    mUiEngine->rootContext()->setContextProperty("bridge", mBridge);
    mUiEngine->rootContext()->setContextProperty("receiver", mReceiver);
    mUiEngine->rootContext()->setContextProperty("sender", mSender);
    mUiEngine->rootContext()->setContextProperty("senderLogsModel", mSenderLogsModel);
    mUiEngine->rootContext()->setContextProperty("receiverLogsModel", mReceiverLogsModel);
}

GuiManager* GuiManager::instance(QObject* parent) {
    if (mInstance == nullptr) mInstance = new GuiManager(parent);
    return mInstance;
}

void GuiManager::exportComponents() {
    // qmlRegisterType<SOMETYPES>("Reverier.SOMETYPES", 1, 0, "SOMETYPES");
}
