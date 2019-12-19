#include "SubWindow.h"

#include <QInputDialog>
#include <QDebug>

SubWindow::SubWindow(const QString& name, QWidget *parent) :
        QWidget(parent),
        mEditButton(new QPushButton(this)),
        mRemoveButton(new QPushButton(this)),
        mCheckBox(new QCheckBox(this)),
        mVLayout(new QVBoxLayout(this))
{
    setName(name);

    mVLayout->addWidget(mCheckBox);
    mVLayout->addWidget(mEditButton);
    mVLayout->addWidget(mRemoveButton);

    for ( int i=0; i<30; i++ )
    {
        mVLayout->addWidget(new QCheckBox(QString::number(i), this));
    }

    connect(mEditButton, &QPushButton::clicked, this, &SubWindow::rename);
    connect(mRemoveButton, &QPushButton::clicked, [this] {
        emit removed(this);
    });
    connect(mCheckBox, &QCheckBox::toggled, this, &SubWindow::checked);
}

SubWindow::~SubWindow()
{
    qDebug() << "~SubWindow() called";
}

void SubWindow::setName(const QString& name)
{
    mCheckBox->setText(name);
}

QString SubWindow::name() const
{
    return mCheckBox->text();
}

bool SubWindow::isCompleted() const
{
   return mCheckBox->isChecked();
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
    QFont font(mCheckBox->font());
    font.setStrikeOut(checked);
    mCheckBox->setFont(font);

    emit statusChanged(this);
}
