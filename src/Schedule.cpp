//
// Schedule.cpp
//
// Copyright (C) 2017
//

#include "Schedule.h"

namespace TransportSystemDlg {

Schedule::Schedule()
{
    mVehicleId = 0;
    mRouteId = 0;
}

Schedule::Schedule(unsigned vehicleId, unsigned routeId)
{
    setVehicleId(vehicleId);
    setRouteId(routeId);
}

Schedule::~Schedule()
{
}

unsigned Schedule::vehicleId() const
{
    return mVehicleId;
}

void Schedule::setVehicleId(unsigned vehicleId)
{
    mVehicleId = vehicleId;
}

unsigned Schedule::routeId() const
{
    return mRouteId;
}

void Schedule::setRouteId(unsigned routeId)
{
    mRouteId = routeId;
}

QDebug operator<<(QDebug debug, const Schedule &schedule) {
    QString str;
    str += QString("%1 ").arg(schedule.vehicleId());
    str += QString("%1 ").arg(schedule.routeId());
    debug << str;
    return debug;
}

}   // namespace TransportSystemDlg


