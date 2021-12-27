/**
 * File: app_manager.h
 * Desc: the whole app manager.
 * Date: 2021.12.26
 */

#pragma once

#include <QObject>

class AppManager : public QObject {
    Q_OBJECT
   public:
    explicit AppManager(QObject* parent = nullptr);

    ~AppManager() override;

    void initialize();

    static void registerTypes();
};
