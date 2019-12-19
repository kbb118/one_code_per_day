#ifndef CHECKGROUP_H
#define CHECKGROUP_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QCheckBox>

#include <QVBoxLayout>
#include <QScrollArea>

class CheckGroup : public QScrollArea
{
    Q_OBJECT

public:
    explicit CheckGroup(const QString& name, QWidget *parent = 0);
    ~CheckGroup();

public slots:
    void add();

signals:
    void removed(CheckGroup* task);
    void statusChanged(CheckGroup* task);

private slots:

private:
    QVBoxLayout *mVLayout;
};

#endif // CHECKGROUP_H
