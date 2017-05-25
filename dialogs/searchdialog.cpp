#include "searchdialog.h"

SearchStudentDialog::SearchStudentDialog(DatabaseManager *mng, QWidget *parent)
    :QDialog(parent)
{
    setManager(mng);
    table = new MultipageTable(getManager()->getDatabase(), this);
    searchWidget = new StudentSearchWidget(this);

    manageButtons();
    manageLayouts();
}

void SearchStudentDialog::manageButtons()
{
    find = new QPushButton(tr("Найти"), this);
    //connect(ok, SIGNAL(clicked(bool)), this, SLOT(addStudentToDatabase()));
    find->setDefault(true);

    cancel = new QPushButton(tr("Отмена"), this);
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void SearchStudentDialog::manageLayouts()
{
    QVBoxLayout *verticalMain = new QVBoxLayout();
    QVBoxLayout *verticalTop = new QVBoxLayout();
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    verticalTop->addWidget(searchWidget);
    verticalTop->addWidget(table);

    buttonsLayout->addWidget(find);
    buttonsLayout->addWidget(cancel);

    verticalMain->addLayout(verticalTop);
    verticalMain->addLayout(buttonsLayout);

    setLayout(verticalMain);
}

DatabaseManager *SearchStudentDialog::getManager()
{
    return manager;
}

void SearchStudentDialog::setManager(DatabaseManager *value)
{
    manager = value;
}

