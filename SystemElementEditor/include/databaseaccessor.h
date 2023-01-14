#ifndef DATABASEACCESSOR_H
#define DATABASEACCESSOR_H

#include <QString>
#include <QtSql>
#include <QSqlQuery>
#include <QDir>
#include <QComboBox>
#include <QSettings>
#include <QString>
#include <treeitem.h>

/*!
 * \class DatabaseAccessor
 * \brief обеспечивает доступ к базе данных и выполнение sql запросов
 */
class DatabaseAccessor : public QObject{
    Q_OBJECT
public:
    static DatabaseAccessor* getInstance();
    static QVector<QVector<QVariant>> executeSqlQuery();
    void setQuery(const QString &value);
private:
    QString query;
    DatabaseAccessor();
    DatabaseAccessor(const DatabaseAccessor& );
    DatabaseAccessor& operator=(const DatabaseAccessor& );
    /// объект подключение к базе данных
    static QSqlDatabase mDBPtr;
};


#endif // DATABASEACCESSOR_H
