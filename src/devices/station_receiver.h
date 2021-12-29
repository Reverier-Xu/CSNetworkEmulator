/**
 * File: station_receiver.h
 * Desc: the receiver station emulator
 * Date: 2021.12.26
 */

#pragma once

#include <QAbstractListModel>
#include <QMap>
#include <QObject>
#include <QTimer>

#include "models/frame.h"
#include "models/ui/logs_model.h"

class StationReceiver : public QAbstractListModel {
    Q_OBJECT
   private:
    QMap<int, DataFrame> frameMap_;
    // buffer size
    int bufferSize_;
    // buffer position
    int bufferPosition_;
    // frame receive cursor
    int bufferReceiveCursor_;
    LogsModel* logsModel_;

   public:
    enum StationReceiverRole {
        FrameStateRole = Qt::UserRole + 1,
    };

    explicit StationReceiver(QObject* parent = nullptr);

    ~StationReceiver() override;

    [[nodiscard]] int rowCount(const QModelIndex& parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex& index,
                                int role) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    void setLogsModel(LogsModel* logsModel);

   public slots:
    void onFrameReceived(const QByteArray& frame);

    Q_INVOKABLE void clear();

   signals:
    void frameSendRequested(QByteArray frame);
};
