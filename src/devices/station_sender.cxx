/**
 * File: station_sender.cxx
 * Desc: the sender station emulator
 * Date: 2021.12.26
 */

#include "station_sender.h"

#include <QtMath>
#include <QDebug>

#include "models/frame.h"

StationSender::StationSender(QObject* parent) : QAbstractListModel(parent) {
    timer_ = new QTimer(this);
    timer_->setInterval(500);
    connect(timer_, &QTimer::timeout, this, &StationSender::sendNextFrame);
}

StationSender::~StationSender() = default;

int StationSender::bufferSize() const { return bufferSize_; }

int StationSender::interval() const { return timer_->interval(); }

int StationSender::bufferPosition() const { return bufferPosition_; }

int StationSender::bufferSendCursor() const { return bufferSendCursor_; }

bool StationSender::isRunning() const { return timer_->isActive(); }

void StationSender::setBufferSize(int size) {
    bufferSize_ = size;
    emit bufferSizeChanged(size);
}

void StationSender::setInterval(int interval) {
    timer_->setInterval(interval);
    emit intervalChanged(interval);
}

void StationSender::setBufferPosition(int position) {
    bufferPosition_ = position;
    emit bufferPositionChanged(position);
}

void StationSender::setBufferSendCursor(int cursor) {
    bufferSendCursor_ = cursor;
    emit bufferSendCursorChanged(cursor);
}

void StationSender::setIsRunning(bool n) {
    if (n) {
        start();
    } else {
        stop();
    }
    emit isRunningChanged(n);
}

void StationSender::setLogsModel(LogsModel* model) { logsModel_ = model; }

void StationSender::start() {
    timer_->start();
}

void StationSender::stop() {
    timer_->stop();
}

void StationSender::sendNextFrame() {
    // qDebug() << "Ready to send next frame.";
    if (bufferPosition() >= frameQueue_.size()) {
        logsModel_->log_success("全部发送完毕！");
        stop();
        emit finished();
        return;
    }
    while (bufferSendCursor() < frameQueue_.size() && frameState_[bufferSendCursor()]) {
        ++bufferSendCursor_;
        if (bufferPosition() >= frameQueue_.size()) {
            logsModel_->log_success("全部发送完毕！");
            stop();
            emit finished();
            return;
        }
    }
    if (bufferSize() + bufferPosition() <= bufferSendCursor()) {
        // find the first frame that is not sent in buffer
        for (int i = bufferPosition(); i < bufferSendCursor(); ++i) {
            if (frameState_[i]) {
                continue;
            }
            // send the frame
            logsModel_->log_error("数据帧[" + QString::number(frameQueue_[i].address()) + "]超时! 重发...");
            emit frameSendRequested(frameQueue_[i].raw());
            setBufferSendCursor(i);
            return;
        }
    } else {
        // send the frame
        if (bufferSendCursor() < frameQueue_.size()) {
            logsModel_->log_warning("正在发送数据帧[" + QString::number(frameQueue_[bufferSendCursor()].address()) + "]...");
            emit frameSendRequested(frameQueue_[bufferSendCursor()].raw());
        }
        setBufferSendCursor(bufferSendCursor() + 1);
        return;
    }
}

void StationSender::resetAll() {
    beginResetModel();
    frameQueue_.clear();
    frameState_.clear();
    bufferPosition_ = 0;
    bufferSendCursor_ = 0;
    logsModel_->clear();
    endResetModel();
}

void StationSender::clear() {
    beginResetModel();
    frameState_.clear();
    for (int i = 0; i < frameQueue_.size(); ++i) {
        frameState_.append(false);
    }
    bufferPosition_ = 0;
    bufferSendCursor_ = 0;
    logsModel_->clear();
    endResetModel();
}

void StationSender::onFrameReceived(QByteArray frame) {
    DataFrame dataFrame;
    dataFrame = frame;
    if (!dataFrame.isAckFrame() && !dataFrame.isNakFrame()) {
        logsModel_->log_error("BROKEN: 收到损坏帧：" + dataFrame.raw().toHex());
        return;
    }
    beginResetModel();
    int authorizedId = dataFrame.address();
    if (dataFrame.isAckFrame()) {
        frameState_[authorizedId] = true;
        // move buffer position
        if (bufferPosition() < frameQueue_.size() && frameState_[bufferPosition()])
            logsModel_->log_success("ACK: 数据帧[" + QString::number(authorizedId) +
                                 "]与之前的帧全部成功抵达。");
        else {
            logsModel_->log_info("ACK: 数据帧[" + QString::number(authorizedId) +
                                 "]帧已抵达。");
        }
        while (bufferPosition() < frameQueue_.size() && frameState_[bufferPosition()]) {
            bufferPosition_++;
        }
        emit bufferPositionChanged(bufferPosition());
    } else if (dataFrame.isNakFrame()) {
        frameState_[authorizedId] = false;
        logsModel_->log_error("NAK: 数据帧[" + QString::number(authorizedId) +
                             "]抵达失败，重新发送。");
        emit frameSendRequested(frameQueue_[authorizedId].raw());
    }
    endResetModel();
}

void StationSender::prepareData(const QByteArray& data) {
    resetAll();
    beginResetModel();
    for (int i = 0; i < data.size(); ++i) {
        DataFrame frame;
        frame.setData(data[i]);
        frame.setAddress(i);
        frameQueue_.append(frame);
        logsModel_->log_success(
            QString::asprintf("数据帧[%d]已添加到队列：%c", i, data[i]));
        frameState_.append(false);
    }
    auto size = frameQueue_.size();
    // figure the binary length of size
    int length = 0;
    while (size) {
        size >>= 1;
        ++length;
    }
    setBufferSize(qPow(2, length - 1) - 1);
    setBufferPosition(0);
    qDebug() << "buffer size is " << bufferSize();
    endResetModel();
}

int StationSender::rowCount(const QModelIndex& parent) const {
    return frameQueue_.size();
}

QVariant StationSender::data(const QModelIndex& index, int role) const {
    if (index.row() < 0 || index.row() >= frameQueue_.size()) {
        return QVariant();
    }
    if (role == FrameStateRole) {
        return frameState_[index.row()];
    }
    return QVariant();
}

QHash<int, QByteArray> StationSender::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FrameStateRole] = "frameState";
    return roles;
}
