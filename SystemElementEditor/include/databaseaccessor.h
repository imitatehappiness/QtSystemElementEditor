#pragma once

#include <QtSql>

#include "treeitem.h"

/*!
 * \class DatabaseAccessor
 * \brief обеспечивает доступ к базе данных и выполнение sql запросов
 *
 * \details по хорошему нужно было переписать на потоки
 */
class DatabaseAccessor : public QObject{
    Q_OBJECT
public:
    static DatabaseAccessor* getInstance();
    QVector<QVector<QVariant>> executeSqlQuery();
    void setQuery(const QString &query);
    bool executeUpdateQuery();

signals:
    void errorOpenDataBase();

private:
    DatabaseAccessor();
    DatabaseAccessor(const DatabaseAccessor& );
    DatabaseAccessor& operator=(const DatabaseAccessor& );
    /// объект подключение к базе данных
    static QSqlDatabase mDBPtr;
    /// sql запрос
    QString mQuery;

};
