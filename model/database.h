#ifndef STUDENTDATABASE_H
#define STUDENTDATABASE_H

#include <QObject>

class StudentDatabase : public QObject
{
    Q_OBJECT
public:
    explicit StudentDatabase(QObject *parent = 0);

signals:

public slots:
};

#endif // STUDENTDATABASE_H
