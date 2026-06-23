#include "MainWindow.h"
#include "../view/ArtificialHorizonWidget.h"
#include "../view/AltimeterWidget.h"

#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QTimer>
#include <QElapsedTimer>
#include <QHBoxLayout>

MainWindow::MainWindow():
    m_flightModel(this),
    m_flightSimulator(m_flightModel)
{
    setWindowTitle("Flight Display");
    resize(1000, 700);

    createMenus();
    createCentralWidget();

    statusBar()->showMessage("Ready");

    connect(&m_flightModel,
            &FlightModel::pitchChanged,
            artificialHorizonWidget,
            &ArtificialHorizonWidget::setPitch);

    connect(&m_flightModel,
            &FlightModel::rollChanged,
            artificialHorizonWidget,
            &ArtificialHorizonWidget::setRoll);

    connect(&m_flightModel,
            &FlightModel::altitudeChanged,
            altimeterWidget,
            &AltimeterWidget::setAltitude);

    m_timer = new QTimer(this);

    m_elapsedTimer = new QElapsedTimer();
    m_elapsedTimer->start();

    m_flightModel.setRollRateDegPerSec(0);
    m_flightModel.setPitchRateDegPerSec(0);
    m_flightModel.setClimbRateFtPerSec(100);

    connect(m_timer,
            &QTimer::timeout,
            this,
            [this]()
            {
                double deltaTime =
                    m_elapsedTimer->restart() / 1000.0;

                m_flightSimulator.update(deltaTime);
            });

    m_timer->start(16);
}

void MainWindow::createMenus()
{
    auto* fileMenu = menuBar()->addMenu("&File");

    exitAction = new QAction("Quit", this);

    fileMenu->addAction(exitAction);

    connect(exitAction,
            &QAction::triggered,
            this,
            &QWidget::close);
}

void MainWindow::createCentralWidget()
{
    auto* centralWidget = new QWidget(this);
    auto* layout = new QHBoxLayout(centralWidget);

    artificialHorizonWidget = new ArtificialHorizonWidget(centralWidget);
    altimeterWidget = new AltimeterWidget(centralWidget);

    layout->addWidget(artificialHorizonWidget);
    layout->addWidget(altimeterWidget);

    setCentralWidget(centralWidget);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
        m_flightModel.setRollRateDegPerSec(-30);
        break;

    case Qt::Key_Right:
        m_flightModel.setRollRateDegPerSec(30);
        break;

    case Qt::Key_Up:
        m_flightModel.setPitchRateDegPerSec(30);
        break;

    case Qt::Key_Down:
        m_flightModel.setPitchRateDegPerSec(-30);
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
        m_flightModel.setRollRateDegPerSec(0);
        break;

    case Qt::Key_Up:
    case Qt::Key_Down:
        m_flightModel.setPitchRateDegPerSec(0);
        break;
    }
}