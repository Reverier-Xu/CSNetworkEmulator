/**
 * File: frame.h
 * Desc: the frame model.
 * Date: 2021.12.26
 */

#pragma once

#include <QObject>

const char FRAME_TAG = 0x7e;

class DataFrame : public QObject {
    // this application just emulate.
    Q_OBJECT
    Q_PROPERTY(char address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(char data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(char control READ control WRITE setControl NOTIFY controlChanged)
    Q_PROPERTY(QByteArray raw READ raw NOTIFY rawChanged)

   private:
    char startTag_ = FRAME_TAG;

    // this item is not used at this emulator, just for reference.
    char address_ = 0;

    // ACK/Data only.
    char control_ = 0;

    // data.
    char data_ = 0;

    char endTag_ = FRAME_TAG;

   public:
    explicit DataFrame(QObject* parent = nullptr);

    DataFrame(const DataFrame& another);

    ~DataFrame() override;

    DataFrame& operator=(const DataFrame& another);

    DataFrame& operator=(char another);

    DataFrame& operator=(const QByteArray& another);

    [[nodiscard]] char address() const;

    void setAddress(char n);

    [[nodiscard]] char control() const;

    void setControl(char n);

    [[nodiscard]] char data() const;

    void setData(char n);

    [[nodiscard]] QByteArray raw() const;

    [[nodiscard]] bool isDataFrame() const;

    [[nodiscard]] bool isControlFrame() const;

    [[nodiscard]] bool isAckFrame() const;

   public slots:
    Q_INVOKABLE void parse(QByteArray raw);

    Q_INVOKABLE void setAck(char id);

    Q_INVOKABLE void setData(char id, char data);

   signals:
    void addressChanged(char n);

    void controlChanged(char n);

    void dataChanged(char n);

    void rawChanged(QByteArray n);
};
