/**
 * File: frame.cxx
 * Desc: the frame model.
 * Date: 2021.12.26
 */

#include "frame.h"

DataFrame::DataFrame(QObject* parent) : QObject(parent) {}

DataFrame::DataFrame(const DataFrame& another) {
    address_ = another.address();
    control_ = another.control();
    data_ = another.data();
}

DataFrame::~DataFrame() = default;

DataFrame& DataFrame::operator=(const DataFrame& another) {
    address_ = another.address();
    control_ = another.control();
    data_ = another.data();
    return *this;
}

DataFrame& DataFrame::operator=(char another) {
    address_ = 0;
    control_ = 0;  // Data frame
    data_ = another;
    return *this;
}

DataFrame& DataFrame::operator=(const QByteArray& another) {
    if (another.size() != 5) {
        return *this;
    }
    if (another.at(0) != FRAME_TAG) {
        return *this;
    }
    if (another.at(4) != FRAME_TAG) {
        return *this;
    }
    address_ = another.at(1);
    control_ = another.at(2);
    data_ = another.at(3);
    return *this;
}

char DataFrame::address() const { return address_; }

void DataFrame::setAddress(char n) {
    address_ = n;
    emit addressChanged(n);
    emit rawChanged(raw());
}

char DataFrame::control() const { return control_; }

void DataFrame::setControl(char n) {
    control_ = n;
    emit controlChanged(n);
    emit rawChanged(raw());
}

char DataFrame::data() const { return data_; }

void DataFrame::setData(char n) {
    data_ = n;
    emit dataChanged(n);
    emit rawChanged(raw());
}

QByteArray DataFrame::raw() const {
    QByteArray raw;
    raw.append(startTag_);
    raw.append(address_);
    raw.append(control_);
    raw.append(data_);
    raw.append(endTag_);
    return raw;
}

bool DataFrame::isDataFrame() const { return control_ == 0; }

bool DataFrame::isControlFrame() const { return (control_ >> 7 & 1); }

bool DataFrame::isAckFrame() const {
    return isControlFrame() && !(control_ >> 5 & 1) && !(control_ >> 4 & 1);
}

void DataFrame::parse(QByteArray n) {
    if (n.size() < 5) {
        return;
    }
    if (n.at(0) != startTag_) {
        return;
    }
    if (n.at(4) != endTag_) {
        return;
    }
    address_ = n.at(1);
    control_ = n.at(2);
    data_ = n.at(3);
    emit addressChanged(address_);
    emit controlChanged(control_);
    emit dataChanged(data_);
    emit rawChanged(n);
}

void DataFrame::setAck(char id) {
    setAddress(id);
    setControl(1 << 7);
    setData(0);
}

void DataFrame::setData(char id, char data) {
    setAddress(id);
    setControl(0);
    setData(data);
}
