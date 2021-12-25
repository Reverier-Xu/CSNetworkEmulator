/**
 * File: display_manager.h
 * Desc: display misc settings for user interface.
 * Date: 2021.12.26
 */

#pragma once

#include <QColor>
#include <QObject>
#include <QTimer>
#include <QTranslator>

class DisplayManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool colorStyle READ colorStyle WRITE setColorStyle NOTIFY
                   colorStyleChanged)
    Q_PROPERTY(QColor themeColor READ themeColor WRITE setThemeColor NOTIFY
                   themeColorChanged)
    Q_PROPERTY(QColor contentColor READ contentColor WRITE setContentColor
                   NOTIFY contentColorChanged)
    Q_PROPERTY(QColor alertColor READ alertColor WRITE setAlertColor NOTIFY
                   alertColorChanged)

   private:
    bool mColorStyle = false;
    QColor mThemeColor = QColor(0x00, 0x78, 0xd6);
    QColor mAlertColor = QColor(0xff, 0x60, 0x33);

   protected:
    explicit DisplayManager(QObject* parent);

    ~DisplayManager() override;

    void loadSettings();

    void saveSettings() const;

    static DisplayManager* mInstance;

   public:
    static DisplayManager* instance(QObject* parent = nullptr);

    [[nodiscard]] bool colorStyle() const;

    void setColorStyle(bool value);

    [[nodiscard]] QColor themeColor() const;

    void setThemeColor(const QColor& value);

    void setThemeColor(const QString& value);

    [[nodiscard]] QColor alertColor() const;

    void setAlertColor(const QColor& value);

    void setAlertColor(const QString& value);

    [[nodiscard]] QColor contentColor() const;

    void setContentColor(const QColor& value);

   signals:

    void colorStyleChanged(bool n);

    void themeColorChanged(QColor n);

    void alertColorChanged(QColor n);

    void contentColorChanged(QColor n);
};
