/**
 * File: logs_model.cxx
 * Desc: logs model for frames.
 * Date: 2021.12.29
 */

#include "logs_model.h"

LogContent::LogContent(const QColor &color, const QString &content,
                       const QTime &time)
    : content_(content), time_(time), color_(color) {}

LogContent::LogContent(const LogContent &another)
    : content_(another.content()),
      time_(another.time()),
      color_(another.color()) {}

QColor LogContent::color() const { return color_; }

QString LogContent::content() const { return content_; }

QTime LogContent::time() const { return time_; }

LogContent &LogContent::operator=(const LogContent &another) {
    content_ = another.content_;
    time_ = another.time_;
    color_ = another.color_;
    return *this;
}

LogsModel::LogsModel(QObject *parent) : QAbstractListModel(parent) {}

int LogsModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return logs_.size();
}

QVariant LogsModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= logs_.size()) {
        return QVariant();
    }
    const auto &log = logs_.at(index.row());
    switch (role) {
        case LogsRoles::LogId:
            return index.row();
        case LogsRoles::LogMessage:
            return log.content();
        case LogsRoles::LogColor:
            return log.color();
        case LogsRoles::LogTime:
            return QString::asprintf("%02d:%02d.%02d", log.time().minute(),
                                     log.time().second(), log.time().msec());
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> LogsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[LogsRoles::LogId] = "logId";
    roles[LogsRoles::LogMessage] = "logMessage";
    roles[LogsRoles::LogColor] = "logColor";
    roles[LogsRoles::LogTime] = "logTime";
    return roles;
}

void LogsModel::clear() {
    if (!logs_.isEmpty()) {
        beginRemoveRows(QModelIndex(), 0, logs_.size() - 1);
        logs_.clear();
        endRemoveRows();
    }
}

void LogsModel::log(const QColor &color, const QString &message) {
    beginInsertRows(QModelIndex(), logs_.size(), logs_.size());
    logs_.append(LogContent(color, message, QTime::currentTime()));
    endInsertRows();
}

void LogsModel::log_info(const QString &message) {
    log(QColor("#0078D6"), message);
}

void LogsModel::log_success(const QString &message) {
    log(QColor("#00B050"), message);
}

void LogsModel::log_warning(const QString &message) {
    log(QColor("#FF9900"), message);
}

void LogsModel::log_error(const QString &message) {
    log(QColor("#FF0000"), message);
}
