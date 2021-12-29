/**
 * File: bridge.h
 * Desc: the bridge emulator
 * Date: 2021.12.26
 */

#pragma once

#include <QObject>
#include <QQueue>

#include "models/frame.h"

class Bridge : public QObject {
    Q_OBJECT
    Q_PROPERTY(double lostRate READ lostRate WRITE setLostRate NOTIFY lostRateChanged)

   private:
    double lostRate_ = 0.4;

   public:
    explicit Bridge(QObject* parent = nullptr);

    ~Bridge() override;

    [[nodiscard]] double lostRate() const;

    void setLostRate(double lostRate);

   public slots:
    Q_INVOKABLE void onSenderRequested(const QByteArray& frame);

    Q_INVOKABLE void onReceiverRequested(const QByteArray& frame);

   signals:
    void senderReceived(const QByteArray& frame);

    void receiverReceived(const QByteArray& frame);

    void toReceiver(int id, bool ok);

    void toSender(int id, bool ok);

    void lostRateChanged(double lostRate);

};
