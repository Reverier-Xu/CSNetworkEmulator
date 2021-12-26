/**
 * File: frame.cxx
 * Desc: the frame model.
 * Date: 2021.12.26
 */

#include "frame.h"

DataFrame::DataFrame(QObject* parent) : QObject(parent) {
    // TODO
}

DataFrame::DataFrame(const DataFrame& another) {
    // TODO
}

DataFrame::~DataFrame() = default;

DataFrame& DataFrame::operator=(const DataFrame& another) {
    // TODO
	return *this;
}

DataFrame& DataFrame::operator=(char another) {
    // TODO
	return *this;
}
