/**
 * File: frame.h
 * Desc: the frame model.
 * Date: 2021.12.26
 */


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

    char address_ = 0;
    char control_ = 0;
    char data_ = 0;

    char endTag_ = FRAME_TAG;

public:
	explicit DataFrame(QObject* parent=nullptr);

	DataFrame(const DataFrame& another);

	~DataFrame() override;

	DataFrame& operator=(const DataFrame& another);

	DataFrame& operator=(char another);

    [[nodiscard]] char address() const;

    void setAddress(char n);

    [[nodiscard]] char control() const;

    void setControl(char n);

    [[nodiscard]] char data() const;

    void setData(char n);

signals:
    void addressChanged(char n);

    void controlChanged(char n);

    void dataChanged(char n);

};
