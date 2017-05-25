#pragma once

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "searchwidget.h"
#include "../table/table.h"
#include "../manager/manager.h"

class SearchStudentDialog : public QDialog
{
    Q_OBJECT
public:
    SearchStudentDialog(DatabaseManager *mng, QWidget *parent);

    DatabaseManager *getManager();
    void setManager(DatabaseManager *value);

private:
    void manageButtons();
    void manageLayouts();

    StudentSearchWidget *searchWidget;
    QPushButton *find;
    QPushButton *cancel;

    MultipageTable *table;
    DatabaseManager *manager;
};
