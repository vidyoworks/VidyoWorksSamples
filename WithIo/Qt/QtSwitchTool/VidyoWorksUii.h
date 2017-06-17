#ifndef VIDYOWORKSUII_H
#define VIDYOWORKSUII_H

#include <QDialog>
#include "VsStatus.h"
#include "VsPlugin.h"

namespace Ui {
class VidyoWorksUi;
}

class VidyoWorksUi : public QDialog,
        public VsStatus
{
    Q_OBJECT

public:
    explicit VidyoWorksUi(QWidget *parent = 0);
    ~VidyoWorksUi();
    virtual void InCall();
    virtual void NotInCall();
    virtual void VideoMute(bool value);
    virtual void MicMute(bool value);

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButtonRoomLink_clicked();

    void on_pushButtonEndCall_clicked();

private:
    Ui::VidyoWorksUi *ui;
    void ShowAfterStart();
    void ShowAfterStop();
    VsPluginPtr vsPlugin;
};

#endif // VIDYOWORKSUII_H
