/**
 * File: frame.h
 * Desc: the frame model.
 * Date: 2021.12.26
 */


#include <QObject>

enum FrameType {
	// ignore emulation-not-related types and subtypes.
	ACK = 1,
	Data = 2
};

class DataFrame : public QObject {
	// this application just emulate ARQ,
	// the frame structure is not compeleted.
	Q_OBJECT
		Q_PROPERTY(FrameType type READ type WRITE setType NOTIFY typeChanged)
		Q_PROPERTY(char data READ data WRITE setData NOTIFY dataChanged)
private:
	FrameType type_;
	char data_;

public:
	explicit DataFrame(QObject* parent=nullptr);

	DataFrame(const DataFrame& another);

	~DataFrame() override;

	DataFrame& operator=(const DataFrame& another);

	DataFrame& operator=(char another);

	[[nodiscard]] FrameType type() const;

	void setType(const FrameType& n);

	[[nodiscard]] char data() const;

	void setData(char n);

signals:
	void typeChanged(FrameType n);

	void dataChanged(char n);
};
