#include "finddialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

FindDialog::FindDialog(QWidget *parent)
    :QDialog(parent)
{
    QSize sz = sizeHint();
    setMinimumSize(sz);
    setMaximumSize(sz);

    findLabel = new QLabel(tr("Find What:"));
    lineEdit = new QLineEdit;
    findLabel->setBuddy(lineEdit);

    matchBox = new QCheckBox;
    matchBox->setText(tr("Match &case"));
    searchBox = new QCheckBox;
    searchBox->setText(tr("Search &backward"));

    findButton = new QPushButton(tr("查找"));
    findButton->setDefault(true);
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("关闭"));

    connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(enableFind(const QString&)));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
    connect(findButton,SIGNAL(clicked(bool)), this, SLOT(find()));

    QHBoxLayout *main = new QHBoxLayout();

    QVBoxLayout *left = new QVBoxLayout();
    QHBoxLayout *lefttop = new QHBoxLayout();
    lefttop->addWidget(findLabel);
    lefttop->addWidget(lineEdit);

    QVBoxLayout *leftdown = new QVBoxLayout();
    leftdown->addWidget(matchBox);
    leftdown->addWidget(searchBox);

    left->addLayout(lefttop);
    left->addLayout(leftdown);

    QVBoxLayout *right = new QVBoxLayout();
    right->addWidget(findButton);
    right->addWidget(closeButton);

    main->addLayout(left);
    main->addLayout(right);
    setLayout(main);


}

void FindDialog::enableFind(const QString &str)
{
    findButton->setEnabled(!str.isEmpty());
}

void FindDialog::closeWindow()
{
    close();
}

void FindDialog::find()
{
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs= matchBox->isChecked()?Qt::CaseSensitive
            : Qt::CaseInsensitive;

    if(searchBox->isChecked()){
        emit findPrevious(text, cs);
    }else{
        emit findNext(text, cs);
    }

}
