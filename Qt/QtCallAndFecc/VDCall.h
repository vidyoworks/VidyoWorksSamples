#ifndef VDCALL_H
#define VDCALL_H

#include <QDialog>
#include <QString>

namespace Ui {
class VDCall;
}

class VDCall : public QDialog
{
    Q_OBJECT

public:
    explicit VDCall(QWidget *parent = 0);
    ~VDCall();
    QString m_id;
    bool m_isLegacy;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::VDCall *ui;
    void SetConfig(QString category, QString key, QVariant value);
    QVariant GetConfig(QString category, QString key);
    bool Validate();
};

#endif // VDCALL_H
