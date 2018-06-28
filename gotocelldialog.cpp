#include "gotocelldialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExp>
#include <QRegExpValidator>

GotoCellDialog::GotoCellDialog(QWidget *parent)
    :QDialog(parent)
{
    QSize sz = sizeHint();
    setMinimumSize(sz);
    setMaximumSize(sz);

    label = new QLabel(tr("&Cell Location:"));
    lineEdit = new QLineEdit;
    QRegExp regexp("[a-zA-Z][1-9][0-9]{0,2}");
    lineEdit->setValidator(new QRegExpValidator(regexp,this));

    label->setBuddy(lineEdit);

    okButton = new QPushButton(tr("确定"));
    okButton->setEnabled(false);

    cancelButton = new QPushButton(tr("取消"));

    connect(lineEdit,SIGNAL(textChanged(QString)), this, SLOT(enableOK(QString)));
    connect(okButton,SIGNAL(clicked(bool)), this ,SLOT(accept()));
    connect(cancelButton,SIGNAL(clicked(bool)), this, SLOT(reject()));

    QHBoxLayout *top = new QHBoxLayout;
    top->addWidget(label);
    top->addWidget(lineEdit);

    QHBoxLayout *down = new QHBoxLayout;
    down->addWidget(okButton);
    down->addWidget(cancelButton);

    QVBoxLayout *main = new QVBoxLayout(this);
    main->addLayout(top);
    main->addLayout(down);

    setLayout(main);
}
QString GotoCellDialog::GetString()
{
    return lineEdit->text();
}

void GotoCellDialog::enableOK(const QString &str)
{
    okButton->setEnabled(!str.isEmpty());
}
