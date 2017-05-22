#pragma once

#include <QObject>
#include <QDialog>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "../table/table.h"

class DatabaseManager;

class SearchStudentDialog : public QDialog
{
    Q_OBJECT
public:
    SearchStudentDialog(DatabaseManager *mng, QWidget *parent);

    DatabaseManager *getManager() const;
    void setManager(DatabaseManager *value);

private:
    void manageSearchFields();
    void manageButtons();
    void manageLayouts();

    QCheckBox *firstNameCheckBox;
    QLineEdit *firstNameInput;

    QCheckBox *secondNameCheckBox;
    QLineEdit *secondNameInput;

    QCheckBox *middleNameCheckBox;
    QLineEdit *middleNameInput;

    QCheckBox *birthDateCheckBox;
    QDateEdit *birthDateLowerBound;
    QDateEdit *birthDateHigherBound;
    QCalendarWidget *birthDateLowerBoundCalendar;
    QCalendarWidget *birthDateHigherBoundCalendar;

    QCheckBox *enrollDateCheckBox;
    QDateEdit *enrollDateLowerBound;
    QDateEdit *enrollDateHigherBound;
    QCalendarWidget *enrollDateLowerBoundCalendar;
    QCalendarWidget *enrollDateHigherBoundCalendar;

    QCheckBox *graduateDateCheckBox;
    QDateEdit *graduateDateLowerBound;
    QDateEdit *graduateDateHigherBound;
    QCalendarWidget *graduateDateLowerBoundCalendar;
    QCalendarWidget *graduateDateHigherBoundCalendar;

    QPushButton *find;
    QPushButton *cancel;

    MultipageTable *table;

    DatabaseManager *manager;
};
