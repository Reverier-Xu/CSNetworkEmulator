/**
 * File: bridge.cxx
 * Desc: the bridge emulator
 * Date: 2021.12.26
 */

#include "bridge.h"

#include <QRandomGenerator>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <QDebug>

Bridge::Bridge(QObject* parent) : QObject(parent) {}

Bridge::~Bridge() = default;

void Bridge::onSenderRequested(const QByteArray& frame) {
    auto p =  QRandomGenerator::global()->generateDouble();
    qDebug() << "Lost ratepoint is: " << p;
    DataFrame dataFrame;
    dataFrame = frame;
    if (p < lostRate_) {
        qDebug() << "FRAME LOST!";
        emit toReceiver(dataFrame.address(), false);
        return;
    }
    emit toReceiver(dataFrame.address(), true);
    QFuture<void> future = QtConcurrent::run([this, frame]() {
        QThread::msleep(300);
        emit receiverReceived(frame);
    });
}

void Bridge::onReceiverRequested(const QByteArray& frame) {
    QRandomGenerator generator;
    DataFrame dataFrame;
    dataFrame = frame;
    if (QRandomGenerator::global()->generateDouble() < lostRate_) {
        qDebug() << "LOST!";
        emit toSender(dataFrame.address(), false);
        return;
    }
    emit toSender(dataFrame.address(), true);
    QFuture<void> future = QtConcurrent::run([this, frame]() {
        QThread::msleep(300);
        emit senderReceived(frame);
    });
}

void Bridge::setLostRate(double lostRate) {
    if (lostRate_ == lostRate) {
        return;
    }
    lostRate_ = lostRate;
    emit lostRateChanged(lostRate_);
}

double Bridge::lostRate() const {
    return lostRate_;
}
