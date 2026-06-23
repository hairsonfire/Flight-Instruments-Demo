#pragma once

#include <QObject>

class FlightModel: public QObject
{
    Q_OBJECT

private:
    int m_speed;
    double m_altitude;
    double m_pitch;
    double m_roll;
    double m_rollRateDegPerSec;
    double m_pitchRateDegPerSec;
    double m_climbRateFtPerSec;

signals:
    void speedChanged(int speed);
    void altitudeChanged(double altitude);
    void pitchChanged(double pitch);
    void rollChanged(double roll);

public:
    explicit FlightModel(QObject* parent = nullptr);

    int speed() const;
    double altitude() const;
    double pitch() const;
    double roll() const;
    double rollRateDegPerSec() const;
    double pitchRateDegPerSec() const;
    double climbRateFtPerSec() const;

    void setSpeed(int speed);
    void setAltitude(double altitude);
    void setPitch(double pitch);
    void setRoll(double roll);
    void setPitchRateDegPerSec(double rate);
    void setRollRateDegPerSec(double rate);
    void setClimbRateFtPerSec(double rate);
};