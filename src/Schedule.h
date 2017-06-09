//
// Schedule.h
//
// Copyright (C) 2017
//

#ifndef TRANSPORTSYSTEMGUI_SCHEDULE_H
#define TRANSPORTSYSTEMGUI_SCHEDULE_H

#include <QString>
#include <QDebug>

namespace TransportSystemDlg {

class Schedule
{
public:
    Schedule();
    Schedule(unsigned vehicleId, unsigned routeId);
    ~Schedule();

    unsigned vehicleId() const;
    void setVehicleId(unsigned vehicleId);

    unsigned routeId() const;
    void setRouteId(unsigned routeId);

private:
    unsigned mVehicleId;
    unsigned mRouteId;
};

QDebug operator<<(QDebug debug, const Schedule &schedule);

}   // namespace TransportSystemDlg

#endif //TRANSPORTSYSTEMGUI_SCHEDULE_H

