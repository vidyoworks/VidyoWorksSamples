#include "VDCall.h"
#include "ui_VDCall.h"

#include <QSettings>
#include <QMessageBox>

static QSettings * appSettings = new QSettings("Vidyo","VidyoCallAndFecc");

void VDCall::SetConfig(QString category, QString key, QVariant value)
{
    appSettings->setValue(category + "/" + key, value);
}

QVariant VDCall::GetConfig(QString category, QString key)
{
    return appSettings->value(category + "/" + key);
}

VDCall::VDCall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VDCall)
{
    ui->setupUi(this);
    m_isLegacy = false;
    m_id  = "";

    QVariant vCallId = GetConfig("Call", "CallId");
    QString callId("203");
    if (vCallId.isValid())
        callId = vCallId.toString();
    ui->lineToCall->setText(callId);

    QVariant vIsLegacy = GetConfig("Call", "IsLegacy");
    bool isLegacy(false);
    if (vIsLegacy.isValid())
        isLegacy = vIsLegacy.toBool();
    ui->checkBoxIsGateway->setChecked(isLegacy);
}

VDCall::~VDCall()
{
    delete ui;
}

bool VDCall::Validate()
{
    if(ui->lineToCall->text().isEmpty())
        return false;

    return true;
}

void VDCall::on_buttonBox_accepted()
{
    if(!Validate())
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText("Incomplete paras");
        msgBox.exec();
        return;
    }


    SetConfig("Call", "CallId", ui->lineToCall->text());
    SetConfig("Call", "IsLegacy",  ui->checkBoxIsGateway->isChecked());

    m_id = ui->lineToCall->text();
    m_isLegacy = ui->checkBoxIsGateway->isChecked();
    this->close();

}
