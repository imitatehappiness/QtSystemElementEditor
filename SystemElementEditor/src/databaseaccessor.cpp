#include "databaseaccessor.h"

QSqlDatabase DatabaseAccessor::mDBPtr;

/*!
 * \brief DatabaseAccessor::DatabaseAccessor конструктор
 * \details подключение к базе данных
 *
 * \details по хорошему нужно было переписать на потоки
 */
DatabaseAccessor::DatabaseAccessor(){
    QString pathConfig = QDir::currentPath();
    QSettings settings(pathConfig.left(pathConfig.lastIndexOf(QChar('/'))) + "/SystemElementEditor/configs/config.ini", QSettings::IniFormat);

    mDBPtr = QSqlDatabase::addDatabase(settings.value("CONNECT/DatabaseType").toString());
    mDBPtr.setHostName(settings.value("CONNECT/HostName").toString());
    mDBPtr.setDatabaseName(settings.value("CONNECT/DatabaseName").toString());
    mDBPtr.setUserName(settings.value("CONNECT/UserName").toString());
    mDBPtr.setPassword(settings.value("CONNECT/Password").toString());
    if (!mDBPtr.open()){
        qDebug() << "Database not open";
    }
}

/*!
 * \brief DatabaseAccessor::getInstance получение указателя на объект DatabaseAccessor
 * \return указатель объекта DatabaseAccessor
 */
DatabaseAccessor* DatabaseAccessor::getInstance(){
    static DatabaseAccessor instance;
    return &instance;
}

/*!
 * \brief DatabaseAccessor::executeSqlQuery выполнение sql запроса
 * \param query запрос
 * \return результат выполнения запроса
 */
QVector<QVector<QVariant>> DatabaseAccessor::executeSqlQuery(){
    QVector<QVector<QVariant>> result;
    QSqlQuery sqlQuery(DatabaseAccessor::getInstance()->mDBPtr);
    sqlQuery.exec(DatabaseAccessor::getInstance()->mQuery);

    while(sqlQuery.next()){
        QVector<QVariant> collum;
        for(int j = 0; j < sqlQuery.record().count(); j++){
            collum.append(sqlQuery.value(j));
        }
        result.append(collum);
    }
    return result;
}

/*!
 * \brief DatabaseAccessor::setQuery установка sql запроса
 * \param value запрос
 */
void DatabaseAccessor::setQuery(const QString &query){
    mQuery = query;
}







