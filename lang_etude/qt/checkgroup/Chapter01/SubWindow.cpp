#include "SubWindow.h"
#include "CheckGroup.h"

#include <QInputDialog>
#include <QDebug>

SubWindow::SubWindow(const QString& name, QWidget *parent) :
        QWidget(parent),
        mAddButton(new QPushButton("Add",this)),
        mRemoveButton(new QPushButton("Remove", this)),
        mCheckBox(new QCheckBox(this)),
        mVLayout(new QVBoxLayout(this))
{
    setName(name);
    mVLayout->addWidget(mCheckBox);
    mVLayout->addWidget(mAddButton);
    mVLayout->addWidget(mRemoveButton);
//    mVLayout->setSizeConstraint(QLayout::SetMinimumSize);

    CheckGroup *cg = new CheckGroup("my", nullptr);
    mVLayout->addWidget(cg);

    //w2, w3...
    for ( int i=0; i<3; i++ )
    {
        auto c = new QCheckBox("super", this);
        mVLayout->addWidget(c);
    }

    connect(mAddButton, &QPushButton::clicked, cg, &CheckGroup::add);
//    connect(mRemoveButton, &QPushButton::clicked, cg, &CheckGroup::remove);
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

void SubWindow::add()
{
    auto c = new QCheckBox("newbie", this);
    mVLayout->addWidget(c);
}

void SubWindow::checked(bool checked)
{
    QFont font(mCheckBox->font());
    font.setStrikeOut(checked);
    mCheckBox->setFont(font);

    emit statusChanged(this);
}
