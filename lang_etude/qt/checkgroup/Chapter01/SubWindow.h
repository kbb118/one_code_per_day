#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QCheckBox>

#include <QVBoxLayout>
#include <QScrollArea>

class SubWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SubWindow(const QString& name, QWidget *parent = 0);
    ~SubWindow();

    void setName(const QString& name);
    QString name() const;
    bool isCompleted() const;

public slots:
    void add();

signals:
    void removed(SubWindow* task);
    void statusChanged(SubWindow* task);

private slots:
    void checked(bool checked);

private:
    QPushButton *mAddButton;
    QPushButton *mRemoveButton;
    QCheckBox *mCheckBox;

    QVBoxLayout *mVLayout;
};

#endif // SUBWINDOW_H
