#include "searchdialog.h"
#include "../manager/manager.h"

SearchStudentDialog::SearchStudentDialog(DatabaseManager *mng, QWidget *parent)
    :QDialog(parent)
{
    setManager(mng);
    table = new MultipageTable(getManager()->getDatabase(), this);

    manageButtons();
    manageSearchFields();
    manageLayouts();
}

void SearchStudentDialog::manageSearchFields()
{
    firstNameCheckBox = new QCheckBox(tr("Имя"), this);
    firstNameInput = new QLineEdit(this);
    firstNameInput->setPlaceholderText(tr("Введите имя..."));

    secondNameCheckBox = new QCheckBox(tr("Фамилия"), this);
    secondNameInput = new QLineEdit(this);
    secondNameInput->setPlaceholderText(tr("Введите фамилию..."));

    middleNameCheckBox = new QCheckBox(tr("Отчество"), this);
    middleNameInput = new QLineEdit(this);
    middleNameInput->setPlaceholderText(tr("Введите отчество..."));

    birthDateCheckBox = new QCheckBox(tr("Дата рождения"), this);
    birthDateLowerBound = new QDateEdit();
    birthDateLowerBoundCalendar = new QCalendarWidget();
    birthDateLowerBound->setCalendarPopup(true);
    birthDateLowerBound->setCalendarWidget(birthDateLowerBoundCalendar);
    birthDateHigherBound = new QDateEdit();
    birthDateHigherBoundCalendar = new QCalendarWidget();
    birthDateHigherBound->setCalendarPopup(true);
    birthDateHigherBound->setCalendarWidget(birthDateHigherBoundCalendar);

    enrollDateCheckBox = new QCheckBox(tr("Дата поступления"), this);
    enrollDateLowerBound = new QDateEdit();
    enrollDateLowerBoundCalendar = new QCalendarWidget();
    enrollDateLowerBound->setCalendarPopup(true);
    enrollDateLowerBound->setCalendarWidget(enrollDateLowerBoundCalendar);
    enrollDateHigherBound = new QDateEdit();
    enrollDateHigherBoundCalendar = new QCalendarWidget();
    enrollDateHigherBound->setCalendarPopup(true);
    enrollDateHigherBound->setCalendarWidget(enrollDateHigherBoundCalendar);

    graduateDateCheckBox = new QCheckBox(tr("Дата окончания"), this);
    graduateDateLowerBound = new QDateEdit();
    graduateDateLowerBoundCalendar = new QCalendarWidget();
    graduateDateLowerBound->setCalendarPopup(true);
    graduateDateLowerBound->setCalendarWidget(graduateDateLowerBoundCalendar);
    graduateDateHigherBound = new QDateEdit();
    graduateDateHigherBoundCalendar = new QCalendarWidget();
    graduateDateHigherBound->setCalendarPopup(true);
    graduateDateHigherBound->setCalendarWidget(graduateDateHigherBoundCalendar);
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
    QVBoxLayout *searchLayout = new QVBoxLayout();
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    QHBoxLayout *horizontalTop = new QHBoxLayout();
    QVBoxLayout *namesVerticalLayout = new QVBoxLayout();
    QVBoxLayout *datesVerticalLayout = new QVBoxLayout();


    QHBoxLayout *firstNameLayout = new QHBoxLayout();
    firstNameLayout->addWidget(firstNameCheckBox);
    firstNameLayout->addWidget(firstNameInput);

    QHBoxLayout *secondNameLayout = new QHBoxLayout();
    secondNameLayout->addWidget(secondNameCheckBox);
    secondNameLayout->addWidget(secondNameInput);

    QHBoxLayout *middleNameLayout = new QHBoxLayout();
    middleNameLayout->addWidget(middleNameCheckBox);
    middleNameLayout->addWidget(middleNameInput);

    namesVerticalLayout->addLayout(firstNameLayout);
    namesVerticalLayout->addLayout(secondNameLayout);
    namesVerticalLayout->addLayout(middleNameLayout);


    QHBoxLayout *birthDateLayout = new QHBoxLayout();
    birthDateLayout->addWidget(birthDateCheckBox);
    birthDateLayout->addWidget(birthDateHigherBound);
    birthDateLayout->addWidget(birthDateLowerBound);

    QHBoxLayout *enrollDateLayout = new QHBoxLayout();
    enrollDateLayout->addWidget(enrollDateCheckBox);
    enrollDateLayout->addWidget(enrollDateHigherBound);
    enrollDateLayout->addWidget(enrollDateLowerBound);

    QHBoxLayout *graduateDateLayout = new QHBoxLayout();
    graduateDateLayout->addWidget(graduateDateCheckBox);
    graduateDateLayout->addWidget(graduateDateHigherBound);
    graduateDateLayout->addWidget(graduateDateLowerBound);

    datesVerticalLayout->addLayout(birthDateLayout);
    datesVerticalLayout->addLayout(enrollDateLayout);
    datesVerticalLayout->addLayout(graduateDateLayout);

    horizontalTop->addLayout(namesVerticalLayout);
    horizontalTop->addLayout(datesVerticalLayout);

    searchLayout->addLayout(horizontalTop);
    searchLayout->addWidget(table);

    buttonsLayout->addWidget(find);
    buttonsLayout->addWidget(cancel);

    verticalMain->addLayout(searchLayout);
    verticalMain->addLayout(buttonsLayout);

    setLayout(verticalMain);
}

DatabaseManager *SearchStudentDialog::getManager() const
{
    return manager;
}

void SearchStudentDialog::setManager(DatabaseManager *value)
{
    manager = value;
}

