#include "SubWindow.h"

#include <QInputDialog>
#include <QDebug>

SubWindow::SubWindow(const QString& name, QWidget *parent) :
        QWidget(parent)
{
    /*
      this-superVlayout
      \_w1
        \_w1_1-vlayout
      \_w2
      \_w3
     */


    auto w1 = new QWidget(this);
    auto w1_1 = new QWidget(w1);

    auto scrl = new QScrollArea(w1);
    scrl->setWidgetResizable(true);

    // w の子にする。
    mCheckBox = new QCheckBox(w1_1);
    mEditButton = new QPushButton(w1_1);
    mRemoveButton = new QPushButton(w1_1);
    mVLayout = new QVBoxLayout(w1_1);
    setName(name);
    mVLayout->addWidget(mCheckBox);
    mVLayout->addWidget(mEditButton);
    mVLayout->addWidget(mRemoveButton);
    mVLayout->setSizeConstraint(QLayout::SetMinimumSize);

    for ( int i=0; i<30; i++ )
    {
        auto c = new QCheckBox(QString::number(i), w1_1);
        mVLayout->addWidget(c);
    }
    scrl->setWidget(w1_1);

    auto superLayout = new QVBoxLayout(this);

    //ここで w1_1 を add するとおかしくなる。
    superLayout->addWidget(scrl);

    //w2, w3...
    for ( int i=0; i<3; i++ )
    {
        auto c = new QCheckBox("super", this);
        superLayout->addWidget(c);
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
