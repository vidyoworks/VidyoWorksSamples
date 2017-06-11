#ifndef VSUSERACCOUNT_H
#define VSUSERACCOUNT_H

#include <QDialog>
#include <QAbstractButton>
#include <QStringList>

namespace Ui {
class VsUserAccount;
}

class VsUserAccount : public QDialog
{
    Q_OBJECT

public:
    explicit VsUserAccount(QWidget *parent = 0);
    ~VsUserAccount();
     QStringList result;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::VsUserAccount *ui;
    bool Validate();
    void SetConfig(QString category, QString key, QVariant value);
    QVariant GetConfig(QString category, QString key);
};

#endif // VSUSERACCOUNT_H
