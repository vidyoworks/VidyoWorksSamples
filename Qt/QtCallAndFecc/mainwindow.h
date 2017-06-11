#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "VsStatus.h"
#include "VsPlugin.h"

namespace Ui {
class MainWindow;
}

enum CallState { VidyoCallStateJoined, VidyoCallStateNotJoined};
enum ClientState { VidyoClientStateInitialized, VidyoClientStateUninitialized};
enum LoginState { VidyoLoginStateLoggedIn, VidyoLoginStateLoggedOut};
class MainWindow : public QMainWindow,
        public VsStatus
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    virtual void SignedIn();
    virtual void SignedOut();
    virtual void InCall();
    virtual void NotInCall();
    virtual void VideoMute(bool value);
    virtual void MicMute(bool value);

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButtonEndCall_clicked();
    //void on_pushStaticButton_clicked();

    void on_pushButtonCall_clicked();

    void on_pushButton_Login_clicked();
    void _Refresh();

    void on_pushButton_Logout_clicked();

    void on_pushButtonRefresh_clicked();

    void on_pushButtonUp_clicked();

private:
    void Refresh();
    Ui::MainWindow *ui;
    VsPluginPtr vsPlugin;
    CallState m_callState;
    void SetCallState(CallState state){m_callState = state;}
    CallState GetCallState(){return m_callState;}

    ClientState m_clientState;
    void SetClientState(ClientState state){m_clientState = state;}
    ClientState GetClientState(){return m_clientState;}

    LoginState m_loginState;
    void SetLoginState(LoginState state){m_loginState = state;}
    LoginState GetLoginState(){return m_loginState;}

    QString m_feccAvailableUrl;
    void SetFeccAvailable(const QString& state){m_feccAvailableUrl = state;}
    QString GetFeccAvailable(){return m_feccAvailableUrl;}

};

#endif // MAINWINDOW_H
