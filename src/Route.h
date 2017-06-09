//
// Route.h
//
// Copyright (C) 2017
//

#ifndef TRANSPORTSYSTEMGUI_ROUTE_H
#define TRANSPORTSYSTEMGUI_ROUTE_H

#include <QString>
#include <QDebug>

namespace TransportSystemDlg {

class Route
{
public:
    static const unsigned MAX_ROUTE_DISTANCE;
    static const unsigned MAX_ROUTE_DAILY_REPEATS;

    static const QString ROUTE_REGULAR_EXPRESSION_VALID;
    static const QString ROUTE_REGULAR_EXPRESSION_INVALID;

public:
    Route();
    Route(const QString &points, unsigned distance, unsigned dailyRepeats);
    ~Route();

    const QString &points() const;
    void setPoints(const QString &points);

    unsigned distance() const;
    void setDistance(unsigned distance);

    unsigned dailyRepeats() const;
    void setDailyRepeats(unsigned dailyRepeats);

private:
    bool pointsValid(const QString &points);
    bool distanceValid(unsigned distance);
    bool dailyRepeatsValid(unsigned dailyRepeats);

private:
    unsigned mId;
    QString mPoints;
    unsigned mDistance;
    unsigned mDailyRepeats;
};

QDebug operator<<(QDebug debug, const Route &route);

}   // namespace TransportSystemDlg

#endif //TRANSPORTSYSTEMGUI_ROUTE_H

