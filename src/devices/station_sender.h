/**
 * File: station_sender.h
 * Desc: the sender station emulator
 * Date: 2021.12.26
 */

#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QQueue>
#include <QTimer>

#include "models/frame.h"
#include "models/ui/logs_model.h"

class StationSender : public QAbstractListModel {
    Q_OBJECT
    // this class emulates the sender station in computer network
    // the sender station is the one who sends the frames to the receiver
    // station, and the receiver station is the one who receives the frames.
    Q_PROPERTY(int bufferSize READ bufferSize WRITE setBufferSize NOTIFY
                   bufferSizeChanged)
    Q_PROPERTY(
        int interval READ interval WRITE setInterval NOTIFY intervalChanged)
    Q_PROPERTY(int bufferPosition READ bufferPosition WRITE setBufferPosition
                   NOTIFY bufferPositionChanged)
    Q_PROPERTY(int bufferSendCursor READ bufferSendCursor WRITE
                   setBufferSendCursor NOTIFY bufferSendCursorChanged)
    Q_PROPERTY(bool isRunning READ isRunning WRITE setIsRunning NOTIFY
                   isRunningChanged)

   private:
    // the queue of frames to be sent
    QQueue<DataFrame> frameQueue_;
    QList<bool> frameState_;
    // buffer size
    int bufferSize_;
    // buffer position
    int bufferPosition_;
    // frame send cursor
    int bufferSendCursor_;
    // the timer to be used to send the frames
    QTimer* timer_;

    LogsModel* logsModel_;

   public:
    enum StationSenderRole {
        FrameStateRole = Qt::UserRole + 1,
    };

    explicit StationSender(QObject* parent = nullptr);

    ~StationSender() override;

    [[nodiscard]] int bufferSize() const;

    [[nodiscard]] int interval() const;

    [[nodiscard]] int bufferPosition() const;

    [[nodiscard]] int bufferSendCursor() const;

    [[nodiscard]] bool isRunning() const;

    void setBufferSize(int size);

    void setInterval(int interval);

    void setBufferPosition(int position);

    void setBufferSendCursor(int cursor);

    void setLogsModel(LogsModel* logsModel);

    void setIsRunning(bool isRunning);

    [[nodiscard]] int rowCount(const QModelIndex& parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex& index,
                                int role) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

   public slots:
    Q_INVOKABLE void start();

    void sendNextFrame();

    Q_INVOKABLE void prepareData(const QByteArray& data);

    Q_INVOKABLE void stop();

    Q_INVOKABLE void onFrameReceived(QByteArray frame);

    Q_INVOKABLE void resetAll();

    Q_INVOKABLE void clear();

   signals:
    void frameSendRequested(QByteArray frame);

    void bufferSizeChanged(int size);

    void intervalChanged(int interval);

    void bufferPositionChanged(int position);

    void bufferSendCursorChanged(int cursor);

    void isRunningChanged(bool isRunning);

    void finished();
};
