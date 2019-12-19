#include "CheckGroup.h"

#include <Qt3DInput/QMouseEvent>
#include <QInputDialog>
#include <QDebug>

CheckGroup::CheckGroup(const QString& name, QWidget *parent) :
        QScrollArea(parent)
{
    auto w = new QWidget();

    mVLayout = new QVBoxLayout(w);
    mVLayout->setSpacing(0);
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
    c->installEventFilter(this);
    mVLayout->addWidget(c);
}

bool
CheckGroup::eventFilter(QObject *o, QEvent *e)
{
    if ( !dynamic_cast<QCheckBox*>(o) )
        return false;
    auto cb = (QCheckBox*)o;

    if ( dynamic_cast<QMouseEvent*>(e) )
    {
        qDebug() << o << "," << e << endl;
        return true;
    }
    else if ( e->type() == QEvent::Enter )
    {
        qDebug() << o << "," << e << endl;
        cb->setStyleSheet("background-color: yellow");
        return true;
    }
    else if ( e->type() == QEvent::Leave )
    {
        qDebug() << o << "," << e << endl;
        cb->setStyleSheet("");
        return true;
    }
    return false;
}

void
CheckGroup::mousePressEvent(QMouseEvent *event)
{
 //   qDebug() << event->x() << "," << event->y() << endl;
}
void
CheckGroup::mouseReleaseEvent(QMouseEvent *event)
{
//    qDebug() << event->x() << "," << event->y() << endl;
}

void
CheckGroup::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << event->x() << "," << event->y() << endl;
}
