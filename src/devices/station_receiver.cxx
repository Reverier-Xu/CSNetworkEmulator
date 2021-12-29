/**
 * File: station_receiver.cxx
 * Desc: the receiver station emulator
 * Date: 2021.12.26
 */

#include "station_receiver.h"

StationReceiver::StationReceiver(QObject* parent)
    : QAbstractListModel(parent) {}

StationReceiver::~StationReceiver() = default;

void StationReceiver::onFrameReceived(const QByteArray& frame) {
    DataFrame dataFrame;
    dataFrame = frame;
    if (!dataFrame.isDataFrame()) {
        logsModel_->log_error("收到损坏数据帧：" + dataFrame.raw().toHex());
        DataFrame nakFrame;
        nakFrame.setNak(dataFrame.address());
        emit frameSendRequested(nakFrame.raw());
        return;
    }
    auto data = dataFrame.data();
    auto id = dataFrame.address();
    beginResetModel();
    frameMap_.insert(id, dataFrame);
    logsModel_->log_info(QString("收到数据帧[") + QString::number(dataFrame.address()) +
                         QString("]：") + dataFrame.data());
    DataFrame ackFrame;
    ackFrame.setAck(dataFrame.address());
    emit frameSendRequested(ackFrame.raw());
    endResetModel();
}

int StationReceiver::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent)
    if (!frameMap_.size())
        return 0;
    return frameMap_.keys().takeLast() + 1;
}

QVariant StationReceiver::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }
    auto id = index.row();

    if (role == FrameStateRole) {
        return frameMap_.contains(id);
    }

    return QVariant();
}

QHash<int, QByteArray> StationReceiver::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FrameStateRole] = "frameState";
    return roles;
}

void StationReceiver::setLogsModel(LogsModel* logsModel) {
    logsModel_ = logsModel;
}

void StationReceiver::clear() {
    beginResetModel();
    frameMap_.clear();
    logsModel_->clear();
    endResetModel();
}
