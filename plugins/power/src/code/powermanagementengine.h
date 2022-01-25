/*
    SPDX-FileCopyrightText: 2007 Aaron Seigo <aseigo@kde.org>
    SPDX-FileCopyrightText: 2007-2008 Sebastian Kuegler <sebas@kde.org>
    SPDX-FileCopyrightText: 2008 Dario Freddi <drf54321@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#pragma once


#include <QDBusConnection>
#include <QHash>
#include <QPair>

using InhibitionInfo = QPair<QString, QString>;

class PowerManagementJob;
/**
 * This class provides runtime information about the battery and AC status
 * for use in power management Plasma applets.
 */
class PowermanagementEngine : public QObject
{
    Q_OBJECT

public:
    PowermanagementEngine(QObject *parent = nullptr);
    QStringList sources() const;
    bool sourceRequestEvent(const QString &name);

    void setScreenBrightness(int value, bool silent);

protected:
    bool updateSourceEvent(const QString &source);
    void init();

private Q_SLOTS:

    void keyboardBrightnessChanged(int brightness);
    void maximumKeyboardBrightnessChanged(int maximumBrightness);
    void triggersLidActionChanged(bool triggers);
    void inhibitionsChanged(const QList<InhibitionInfo> &added, const QStringList &removed);

    void onMaximumScreenBrightness(int maximumBrightness);
    void onScreenBrightness(int brightness);

    void updatePowerProfileCurrentProfile(const QString &profile);
    void updatePowerProfileChoices(const QStringList &choices);
    void updatePowerProfilePerformanceInhibitedReason(const QString &reason);
    void updatePowerProfilePerformanceDegradedReason(const QString &reason);
    void updatePowerProfileHolds(const QList<QVariantMap> &holds);

private:
    PowerManagementJob *m_job;
    void populateApplicationData(const QString &name, QString *prettyName, QString *icon);
    QStringList basicSourceNames() const;

    QStringList m_sources;

    QHash<QString, QPair<QString, QString>> m_applicationInfo; // <appname, <pretty name, icon>>

    void setData(const QString &name, const QString &name2, const QVariant &value);

signals:
    void screenBrightnessChanged(int brightness);
    void screenBrightnessAvailableChanged(bool value);
    void maximumScreenBrightnessChanged(int maximumBrightness);

};
