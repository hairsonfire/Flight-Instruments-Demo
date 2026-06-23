#pragma once

class FlightModel;

class FlightSimulator
{
public:
    explicit FlightSimulator(FlightModel& model);

    void update(double deltaTime);

private:
    FlightModel& m_model;
};