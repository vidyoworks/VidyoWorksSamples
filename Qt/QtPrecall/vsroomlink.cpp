#include "vsroomlink.h"
#include "ui_vsroomlink.h"
#include <QMessageBox>
#include <QDebug>
#include <QSettings>

QSettings * appSettings = new QSettings("Vidyo","VidyoSample");

void VsRoomLink::SetConfig(QString category, QString key, QVariant value)
{
    appSettings->setValue(category + "/" + key, value);
}

QVariant VsRoomLink::GetConfig(QString category, QString key)
{
    return appSettings->value(category + "/" + key);
}

VsRoomLink::VsRoomLink(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VsRoomLink)
{
    ui->setupUi(this);
    result.clear();

    QVariant vPortalName = GetConfig("Account", "PortalName");
    QString portalName("http://test.sandboxga.vidyo.com");
    if (vPortalName.isValid())
        portalName = vPortalName.toString();
    ui->lineEditPortalName->setText(portalName);

    QVariant vRoomKey = GetConfig("Account", "RoomKey");
    QString roomKey("iUC7CrJ822");
    if (vRoomKey.isValid())
        roomKey = vRoomKey.toString();
    ui->lineEditRoomKey->setText(roomKey);

    int number = 100;
    int randomValue = qrand() % number;

    QVariant vDisplayName = GetConfig("Account", "DisplayName");
    QString displayName("TestUser - " + QString::number(randomValue));
    if (vDisplayName.isValid())
        displayName = vDisplayName.toString();
    ui->lineEditDisplayName->setText(displayName);
}

VsRoomLink::~VsRoomLink()
{
    delete ui;
}

bool VsRoomLink::Validate()
{
    if(ui->lineEditPortalName->text().isEmpty())
        return false;
    if(ui->lineEditRoomKey->text().isEmpty())
        return false;
    if(ui->lineEditDisplayName->text().isEmpty())
        return false;
    return true;
}

void VsRoomLink::on_buttonBox_accepted()
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
              << ui->lineEditRoomKey->text()
              << ui->lineEditDisplayName->text()
              << ui->lineEditPin->text();

    SetConfig("Account", "PortalName", ui->lineEditPortalName->text());
    SetConfig("Account", "RoomKey", ui->lineEditRoomKey->text());
    SetConfig("Account", "DisplayName", ui->lineEditDisplayName->text());

    QString joined = result.join(", ");
    qDebug() << joined ;

}

