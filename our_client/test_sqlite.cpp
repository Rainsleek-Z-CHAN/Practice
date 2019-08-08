#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
void test(){
QSqlDatabase database;
if (QSqlDatabase::contains("qt_sql_default_connection"))
{
    database = QSqlDatabase::database("qt_sql_default_connection");
}
else
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyDataBase.db");
    database.setUserName("XingYeZhiXia");
    database.setPassword("123456");
}
}
