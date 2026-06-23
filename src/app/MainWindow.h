#pragma once

#include "../model/FlightModel.h"
#include "../flightsimulator/FlightSimulator.h"

#include <QMainWindow>
#include <QKeyEvent>

class QAction;
class QLabel;
class QTimer;
class QElapsedTimer;
class ArtificialHorizonWidget;
class AltimeterWidget;

class MainWindow : public QMainWindow
{
public:
    MainWindow();

private:
    void createMenus();
    void createToolBar();
    void createCentralWidget();

    QAction* exitAction;
    QAction* startAction;
    QAction* stopAction;

    QLabel* speedLabel;
    QLabel* altitudeLabel;

    FlightModel m_flightModel;

    ArtificialHorizonWidget* artificialHorizonWidget;
    AltimeterWidget* altimeterWidget;

    QTimer* m_timer;

    QElapsedTimer* m_elapsedTimer;

    FlightSimulator m_flightSimulator;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
};