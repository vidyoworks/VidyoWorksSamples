#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "VsStatus.h"
#include "VsPlugin.h"

namespace Ui {
class MainWindow;
}

typedef QSharedPointer<QTimer> SmartTimer;

class MainWindow : public QMainWindow,
        public VsStatus
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    virtual void InCall();
    virtual void NotInCall();
    virtual void VideoMute(bool value);
    virtual void MicMute(bool value);

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButtonRoomLink_clicked();

    void on_pushButtonEndCall_clicked();
    //void on_pushStaticButton_clicked();

    void on_pushCameraTest_clicked();

    void on_pushButtonMicTest_clicked();

    void OnQueryEnergy();

    void on_pushButtonSpeaker_clicked();

private:
    void ShowAfterStart();
    void ShowAfterStop();
    Ui::MainWindow *ui;
    VsPluginPtr vsPlugin;
    bool m_bCameraTestOn;
    bool m_bMicTestOn;
    bool m_bSpeakerTestOn;
    SmartTimer pingMicTimer;
};

#endif // MAINWINDOW_H
