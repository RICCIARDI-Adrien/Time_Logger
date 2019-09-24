/** @file MainWindow.cpp
 * See MainWindow.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <MainWindow.hpp>
#include <QTime>
#include <ui_MainWindow.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect slots
    connect(ui->lineEditTaskName, &QLineEdit::textChanged, this, &MainWindow::_slotLineEditTaskNameTextChanged);
    connect(&_timerSeconds, &QTimer::timeout, this, &MainWindow::_slotTimerSecondsTimeout);
    connect(ui->pushButtonPlay, &QPushButton::pressed, this, &MainWindow::_slotPushButtonPlayPressed);

    // Configure seconds counting timer
    _timerSeconds.setInterval(1000);
    _timerSeconds.setTimerType(Qt::PreciseTimer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_slotLineEditTaskNameTextChanged(const QString &referenceText)
{
    // Enable "play" button only if the line edit contains some text
    if (referenceText.length() > 0) ui->pushButtonPlay->setEnabled(true);
    else ui->pushButtonPlay->setEnabled(false);
}

void MainWindow::_slotTimerSecondsTimeout()
{
    _timeElapsed = _timeElapsed.addSecs(1);
    ui->labelTime->setText(_timeElapsed.toString());
}

void MainWindow::_slotPushButtonPlayPressed()
{
    // Cache some values
    QTime currentTime = QTime::currentTime();
    QString time = currentTime.toString();
    QString taskName = ui->lineEditTaskName->text();

    // Start timer
    QString logMessage;
    if (!_isTimerRunning)
    {
        // Start counting time
        _timerSeconds.start();
        _timeElapsed.setHMS(0, 0, 0);

        // Update user interface
        ui->pushButtonPlay->setText(tr("Stop")); // Change button caption to "Stop"
        ui->lineEditTaskName->setEnabled(false); // Prevent task name from being modified

        // Create log message
        logMessage = tr("%1 : Started task \"%2\".").arg(time).arg(taskName);

        _isTimerRunning = true;
    }
    // Stop timer
    else
    {
        // Stop counting time
        _timerSeconds.stop();

        // Update user interface
        ui->pushButtonPlay->setText(tr("Play")); // Change button caption to "Play"
        ui->lineEditTaskName->setEnabled(true); // Allow task name to be modified

        // Create log message
        logMessage = tr("%1 : Stopped task \"%2\", duration : %3.").arg(time).arg(taskName).arg(_timeElapsed.toString());

        _isTimerRunning = false;
    }

    // Append log message to the list
    ui->listWidgetLog->addItem(logMessage);
}
