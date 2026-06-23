#include "FlightSimulator.h"
#include "../model/FlightModel.h"

FlightSimulator::FlightSimulator(FlightModel& model):
    m_model(model)
{
}

void FlightSimulator::update(double deltaTime)
{
    double roll = m_model.roll()+ m_model.rollRateDegPerSec() * deltaTime;

    double pitch = m_model.pitch() + m_model.pitchRateDegPerSec() * deltaTime;

    double altitude = m_model.altitude() + m_model.climbRateFtPerSec() * deltaTime;

    roll = std::clamp(roll, -180.0, 180.0);

    pitch = std::clamp(pitch, -90.0, 90.0);

    altitude = std::clamp(altitude, 0.0, 10000.0);

    m_model.setRoll(roll);
    m_model.setPitch(pitch);
    m_model.setAltitude(altitude);
}