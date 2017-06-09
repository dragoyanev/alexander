//
// ScheduleTab.h
//
// Copyright (C) 2017
//

#ifndef TRANSPORTSYSTEMGUI_SCHEDULETAB_H
#define TRANSPORTSYSTEMGUI_SCHEDULETAB_H

#include <QStandardItemModel>

#include "ui_ScheduleTab.h"
#include "Schedule.h"
#include "Vehicle.h"
#include "Route.h"

namespace TransportSystemDlg {

class ScheduleTab : public QWidget, private Ui::ScheduleTab
{
    Q_OBJECT

public:
    explicit ScheduleTab(QWidget *parent = 0);

    const QList<Schedule> &scheduleData() const;
    void setScheduleData(const QList<Schedule> &scheduleData);

    const QList<Vehicle> &vehicleData() const;
    void setVehicleData(const QList<Vehicle> &vehicleData);

    const QList<Route> &routeData() const;
    void setRouteData(const QList<Route> &routeData);

public slots:
    void onVehicleRowDeleted(unsigned currRow);
    void onVehicleRowAdded(const QList<Vehicle> &vehicleData);
    void onRouteRowDeleted(unsigned currRow);
    void onRouteRowAdded(const QList<Route> &routeData);

private slots:
    void onNewButtonClicked();
    void onDeleteButtonClicked();

private:
    void updateTable();
    void refreshVehicleCombo();
    void refreshRouteCombo();

private:
    QList<Vehicle> mVehicleData;
    QList<Route> mRouteData;
    QList<Schedule> mScheduleData;
};

}   // namespace TransportSystemDlg

#endif // TRANSPORTSYSTEMGUI_SCHEDULETAB_H
