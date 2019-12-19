#include "CheckGroup.h"

#include <QInputDialog>
#include <QDebug>

CheckGroup::CheckGroup(const QString& name, QWidget *parent) :
        QScrollArea(parent)
{
    auto w = new QWidget();

    mVLayout = new QVBoxLayout(w);
    qDebug() << mVLayout << endl;
    setWidget(w);
    setWidgetResizable(true); // これがないと追加が反映されない。

    /*
    connect(parent, &QPushButton::clicked, this, &CheckGroup::add);
    connect(parent, &QPushButton::clicked, [this] {
        emit removed(this);
    });
    connect(mCheckBox, &QCheckBox::toggled, this, &CheckGroup::checked);
    */
}

CheckGroup::~CheckGroup()
{
    qDebug() << "~CheckGroup() called";
}

void CheckGroup::add()
{
    auto c = new QCheckBox("newbie", widget());
    mVLayout->addWidget(c);
}

