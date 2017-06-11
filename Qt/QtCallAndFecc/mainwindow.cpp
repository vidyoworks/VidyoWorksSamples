#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VsPlugin.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include "VsUserAccount.h"
#include "VDCall.h"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetClientState(VidyoClientStateUninitialized);
    SetLoginState(VidyoLoginStateLoggedOut);
    SetCallState(VidyoCallStateNotJoined);
    SetFeccAvailable("");
    vsPlugin = VsPluginPtr(new VsPlugin(this));
    Refresh();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStart_clicked()
{
    if(!vsPlugin->VsStart())
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("VidyoClientStart");
        msgBox.exec();
        return;

    }
    SetClientState(VidyoClientStateInitialized);
    Refresh();
}

void MainWindow::Refresh()
{
    QTimer::singleShot(0, this, SLOT(_Refresh()));
}

void MainWindow::_Refresh()
{
    ui->pushButtonStart->setEnabled(GetClientState() == VidyoClientStateUninitialized);
    ui->pushButton_Stop->setEnabled(GetClientState() == VidyoClientStateInitialized);

    ui->pushButton_Login->setEnabled(GetClientState() == VidyoClientStateInitialized && GetLoginState() == VidyoLoginStateLoggedOut);
    ui->pushButton_Logout->setEnabled(GetLoginState() == VidyoLoginStateLoggedIn);

    ui->pushButtonCall->setEnabled(GetClientState() == VidyoClientStateInitialized && GetCallState() == VidyoCallStateNotJoined);
    ui->pushButtonEndCall->setEnabled(GetCallState() == VidyoCallStateJoined);

    ui->pushButtonRefresh->setEnabled(GetCallState() == VidyoCallStateJoined);

    ui->pushButtonUp->setEnabled(!GetFeccAvailable().isEmpty());
    ui->pushButtonDown->setEnabled(!GetFeccAvailable().isEmpty());
    ui->pushButtonLeft->setEnabled(!GetFeccAvailable().isEmpty());
    ui->pushButtonRight->setEnabled(!GetFeccAvailable().isEmpty());
}



void MainWindow::on_pushButton_Stop_clicked()
{
    if(!vsPlugin->VsStop())
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("VidyoClientStop");
        msgBox.exec();
        return;

    }
    SetClientState(VidyoClientStateUninitialized);
    SetLoginState(VidyoLoginStateLoggedOut);
    SetCallState(VidyoCallStateNotJoined);
    Refresh();
}


void MainWindow::on_pushButtonEndCall_clicked()
{
    vsPlugin->VsCallEnd();
}

void MainWindow::SignedIn()
{
    SetLoginState(VidyoLoginStateLoggedIn);
    Refresh();
}

void MainWindow::SignedOut()
{
    SetLoginState(VidyoLoginStateLoggedOut);
    Refresh();
}

void MainWindow::InCall()
{
    SetCallState(VidyoCallStateJoined);
    Refresh();
}

void MainWindow::NotInCall()
{
    SetCallState(VidyoCallStateNotJoined);
    Refresh();
}

void MainWindow::VideoMute(bool value)
{

}

void MainWindow::MicMute(bool value)
{

}


void MainWindow::on_pushButton_Login_clicked()
{
    QScopedPointer<VsUserAccount> accountDlg(new VsUserAccount(this));
    accountDlg->exec();

    if(accountDlg->result.isEmpty())
        return;
    if(!vsPlugin->VsLogin(accountDlg->result))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("login");
        msgBox.exec();
        return;
    }
}

void MainWindow::on_pushButton_Logout_clicked()
{
    vsPlugin->VsLogout();
}

void MainWindow::on_pushButtonCall_clicked()
{
    QScopedPointer<VDCall> call(new VDCall(this));
    call->exec();

    if(call->m_id.isEmpty())
        return;
    if(!vsPlugin->VsCall(call->m_id, call->m_isLegacy))
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Call");
        msgBox.exec();
        return;
    }


}

void MainWindow::on_pushButtonRefresh_clicked()
{
    SetFeccAvailable(vsPlugin->VsGetFecc());
    Refresh();
}

void MainWindow::on_pushButtonUp_clicked()
{
    vsPlugin->VsMoveCamera(GetFeccAvailable(), MoveUp);
}
