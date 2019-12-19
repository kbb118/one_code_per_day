#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QString>

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
    void rename();

signals:
    void removed(SubWindow* task);
    void statusChanged(SubWindow* task);

private slots:
    void checked(bool checked);

private:
};

#endif // SUBWINDOW_H
