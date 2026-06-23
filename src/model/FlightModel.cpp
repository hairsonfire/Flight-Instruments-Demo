#include "FlightModel.h"

FlightModel::FlightModel(QObject* parent):
    QObject(parent),
    m_speed(0),
    m_altitude(0.0),
    m_pitch(0.0),
    m_roll(0.0),
    m_rollRateDegPerSec(0.0),
    m_pitchRateDegPerSec(0.0),
    m_climbRateFtPerSec(0.0)
{
}

int FlightModel::speed() const
{
    return m_speed;
}

double FlightModel::altitude() const
{
    return m_altitude;
}

double FlightModel::pitch() const
{
    return m_pitch;
}

double FlightModel::roll() const
{
    return m_roll;
}

double FlightModel::rollRateDegPerSec() const
{
    return m_rollRateDegPerSec;
}

double FlightModel::pitchRateDegPerSec() const
{
    return m_pitchRateDegPerSec;
}

double FlightModel::climbRateFtPerSec() const
{
    return m_climbRateFtPerSec;
}

void FlightModel::setAltitude(double altitude)
{
    if(qFuzzyCompare(m_altitude, altitude))
    {
        return;
    }

    m_altitude = altitude;

    emit altitudeChanged(altitude);
}

void FlightModel::setSpeed(int speed)
{
    if(m_speed == speed)
    {
        return;
    }

    m_speed = speed;

    emit speedChanged(speed);
}

void FlightModel::setPitch(double pitch)
{
    if(qFuzzyCompare(m_pitch, pitch))
    {
        return;
    }

    m_pitch = pitch;

    emit pitchChanged(pitch);
}

void FlightModel::setRoll(double roll)
{
    if(qFuzzyCompare(m_roll, roll))
    {
        return;
    }

    m_roll = roll;

    emit rollChanged(roll);
}

void FlightModel::setRollRateDegPerSec(double rollRateDegPerSec)
{
    m_rollRateDegPerSec = rollRateDegPerSec;
}

void FlightModel::setPitchRateDegPerSec(double pitchRateDegPerSec)
{
    m_pitchRateDegPerSec = pitchRateDegPerSec;
}

void FlightModel::setClimbRateFtPerSec(double climbRateFtPerSec)
{
    m_climbRateFtPerSec = climbRateFtPerSec;
}