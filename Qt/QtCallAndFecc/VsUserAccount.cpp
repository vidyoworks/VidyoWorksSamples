#include "VsUserAccount.h"
#include "ui_VsUserAccount.h"
#include <QMessageBox>
#include <QDebug>
#include <QSettings>

static QSettings * appSettings = new QSettings("Vidyo","VidyoCallAndFecc");

void VsUserAccount::SetConfig(QString category, QString key, QVariant value)
{
    appSettings->setValue(category + "/" + key, value);
}

QVariant VsUserAccount::GetConfig(QString category, QString key)
{
    return appSettings->value(category + "/" + key);
}

VsUserAccount::VsUserAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VsUserAccount)
{
    ui->setupUi(this);
    result.clear();

    QVariant vPortalName = GetConfig("Account", "PortalName");
    QString portalName("http://vvp9.vidyoqa.com");
    if (vPortalName.isValid())
        portalName = vPortalName.toString();
    ui->lineEditPortalName->setText(portalName);

    QVariant vUser = GetConfig("Account", "User");
    QString user("qa5");
    if (vUser.isValid())
        user = vUser.toString();
    ui->lineEditUser->setText(user);

    ui->lineEditPassword->setText("");
}

VsUserAccount::~VsUserAccount()
{
    delete ui;
}

bool VsUserAccount::Validate()
{
    if(ui->lineEditPortalName->text().isEmpty())
        return false;
    if(ui->lineEditUser->text().isEmpty())
        return false;
    if(ui->lineEditPassword->text().isEmpty())
        return false;
    return true;
}

void VsUserAccount::on_buttonBox_accepted()
{
    if(!Validate())
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Incomplete paras");
        msgBox.exec();
        return;
    }
    result << ui->lineEditPortalName->text()
              << ui->lineEditUser->text()
              << ui->lineEditPassword->text();

    SetConfig("Account", "PortalName", ui->lineEditPortalName->text());
    SetConfig("Account", "User", ui->lineEditUser->text());

    QString joined = result.join(", ");
    qDebug() << joined ;
    this->close();

}
