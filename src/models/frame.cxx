/**
 * File: frame.cxx
 * Desc: the frame model.
 * Date: 2021.12.26
 */

#include "frame.h"

DataFrame::DataFrame(QObject* parent) : QObject(parent) {

}

DataFrame::DataFrame(const DataFrame& another) {
	type_ = another.type();
	data_ = another.data();
}

DataFrame::~DataFrame() = default;

DataFrame& DataFrame::operator=(const DataFrame& another) {
	type_ = another.type();
	data_ = another.data();
	return *this;
}

DataFrame& DataFrame::operator=(char another) {
	type_ = FrameType::Data;
	data_ = another;
	return *this;
}

FrameType DataFrame::type() const {
	return type_;
}

void DataFrame::setType(const FrameType& n) {
	type_ = n;
	emit typeChanged(n);
}

char DataFrame::data() const {
	return data_;
}

void DataFrame::setData(char n) {
	data_ = n;
	emit dataChanged(n);
}
