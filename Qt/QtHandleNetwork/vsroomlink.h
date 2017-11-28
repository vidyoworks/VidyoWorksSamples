#ifndef VSROOMLINK_H
#define VSROOMLINK_H

#include <QDialog>
#include <QAbstractButton>
#include <QStringList>
#include <QSharedPointer>

namespace Ui {
class VsRoomLink;
}

class VsRoomLink : public QDialog
{
    Q_OBJECT

public:
    explicit VsRoomLink(QWidget *parent = 0);
    virtual ~VsRoomLink();
    QStringList result;

private slots:

    void on_buttonBox_accepted();
private:
    Ui::VsRoomLink *ui;
    bool Validate();
    void SetConfig(QString category, QString key, QVariant value);
    QVariant GetConfig(QString category, QString key);
};

#endif // VSROOMLINK_H
