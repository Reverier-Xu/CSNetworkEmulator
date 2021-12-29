/**
 * File: logs_model.h
 * Desc: logs model for frames.
 * Date: 2021.12.28
 */

#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QTime>
#include <QColor>

class LogContent {
public:
    LogContent(const QColor& color, const QString& content, const QTime& time);
    LogContent(const LogContent& another);
    LogContent& operator=(const LogContent& another);
    QString content() const;
    QTime time() const;
    QColor color() const;
private:
    QString content_;
    QTime time_;
    QColor color_;
};

class LogsModel : public QAbstractListModel {
    Q_OBJECT
   public:
    enum LogsRoles {
        LogId = Qt::UserRole + 1,
        LogMessage,
        LogColor,
        LogTime,
    };

    explicit LogsModel(QObject *parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index,
                                int role) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

   public slots:
    Q_INVOKABLE void clear();

    Q_INVOKABLE void log(const QColor &color, const QString &message);

    Q_INVOKABLE void log_info(const QString &message);

    Q_INVOKABLE void log_success(const QString &message);

    Q_INVOKABLE void log_warning(const QString &message);

    Q_INVOKABLE void log_error(const QString &message);

   private:
    QList<LogContent> logs_;
};
