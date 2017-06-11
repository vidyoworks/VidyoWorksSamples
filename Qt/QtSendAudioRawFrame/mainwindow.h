#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSharedPointer>

#include "VsStatus.h"
#include "VsPlugin.h"
#include <QMap>

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
    virtual void OnReceivedFrame(void* videoFrame);

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButtonRoomLink_clicked();

    void on_pushButtonEndCall_clicked();

    void on_pushButtonCaptureRaw_clicked();

    void on_pushButtonPlay_clicked();
    void OnPlayBack();

private:
    void ShowAfterStart();
    void ShowAfterStop();
    Ui::MainWindow *ui;
    VsPluginPtr vsPlugin;
    QMap<QString, int> uriToWidget;
    QWidget* GetWidgetForUri(QString& uri);
    bool m_bIsRawCapturing;
    SmartTimer playBackTimer;
};

#endif // MAINWINDOW_H
