/** @file MainWindow.hpp
 * Display user interface and handle all application logic.
 * @author Adrien RICCIARDI
 */
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /** This timer is called each second and refreshes the displayed time. */
    QTimer _timerSeconds;

    /** Tell whether seconds timer is currently running. */
    bool _isTimerRunning = false;
    /** How many time elapsed since chronometer start. */
    QTime _timeElapsed;

    /** Called when "task name" line edit text is modified. */
    void _slotLineEditTaskNameTextChanged(const QString &referenceText);

    /** Called when seconds timer times out. */
    void _slotTimerSecondsTimeout();

    /** Called when "play" push button is pressed. */
    void _slotPushButtonPlayPressed();
    /** Called when "reset" push button is pressed. */
    void _slotPushButtonResetPressed();
};

#endif // MAINWINDOW_HPP
