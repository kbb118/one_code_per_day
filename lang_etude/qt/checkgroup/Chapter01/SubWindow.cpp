#include "SubWindow.h"

#include <QInputDialog>
#include <QDebug>

SubWindow::SubWindow(const QString& name, QWidget *parent) :
        QWidget(parent),
{
    setName(name);

    connect(editButton, &QPushButton::clicked, this, &SubWindow::rename);
    connect(removeButton, &QPushButton::clicked, [this] {
        emit removed(this);
    });
    connect(checkbox, &QCheckBox::toggled, this, &SubWindow::checked);
}

SubWindow::~SubWindow()
{
    qDebug() << "~SubWindow() called";
}

void SubWindow::setName(const QString& name)
{
    checkbox->setText(name);
}

QString SubWindow::name() const
{
    return checkbox->text();
}

bool SubWindow::isCompleted() const
{
   return checkbox->isChecked();
}

void SubWindow::rename()
{
    bool ok;
    QString value = QInputDialog::getText(this, tr("Edit task"),
                                          tr("SubWindow name"), QLineEdit::Normal,
                                          this->name(), &ok);
    if (ok && !value.isEmpty()) {
        setName(value);
    }
}

void SubWindow::checked(bool checked)
{
    QFont font(checkbox->font());
    font.setStrikeOut(checked);
    checkbox->setFont(font);

    emit statusChanged(this);
}
