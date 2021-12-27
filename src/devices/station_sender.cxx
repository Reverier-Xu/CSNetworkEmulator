/**
 * File: station_sender.cxx
 * Desc: the sender station emulator
 * Date: 2021.12.26
 */

#include "station_sender.h"


StationSender::StationSender(QObject* parent) : QObject(parent) {}

StationSender::~StationSender() = default;

void StationSender::setBridge(Bridge* bridge) {
    bridge_ = bridge;
}

int StationSender::bufferSize() const {
    return bufferSize_;
}

int StationSender::interval() const {
    return timer_->interval();
}

int StationSender::bufferPosition() const {
    return bufferPosition_;
}

int StationSender::bufferSendCursor() const {
    return bufferSendCursor_;
}

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

void StationSender::start() {
    timer_->start();
}

void StationSender::stop() {
    timer_->stop();
    frameState_.clear();
    for (int i = 0; i < frameQueue_.size(); ++i) {
        frameState_.append(false);
    }
}

void StationSender::sendNextFrame() {
    if (bufferSendCursor() >= frameQueue_.size()) {
        emit finished();
        return;
    }
    while (frameState_[bufferSendCursor()]) {
        ++bufferSendCursor_;
        if (bufferSendCursor() >= frameQueue_.size()) {
            emit finished();
            return;
        }
    }
    if (bufferSize() + bufferPosition() >= bufferSendCursor()) {
        // find the first frame that is not sent in buffer
        for (int i = bufferPosition(); i < bufferSendCursor(); ++i) {
            if (frameState_[i]) {
                continue;
            }
            // send the frame
            emit frameSendRequested(frameQueue_[i].raw());
            setBufferSendCursor(i);
            return;
        }
    } else {
        // send the frame
        emit frameSendRequested(frameQueue_[bufferSendCursor()].raw());
        setBufferSendCursor(bufferSendCursor()+1);
        return;
    }
}

void StationSender::onFrameReceived(QByteArray frame) {
    DataFrame dataFrame;
    dataFrame = frame;
    if (!dataFrame.isAckFrame()) {
        return;
    }
    int authorizedId = dataFrame.address();
    frameState_[authorizedId] = true;
    // move buffer position
    while (authorizedId == bufferPosition()) {
        bufferPosition_++;
    }
    emit bufferPositionChanged(bufferPosition());
}
