#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <iostream>
#include <string>


void createDB();
void queryDB();
void hostDBconnect();

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    //createDB();  // создание локальноый базы данных
    //queryDB();   // запросы к локальной базе данных

    //hostDBconnect();  // запросы к удаленной базе данных


    //std::system("pause");
    return a.exec();
}

void hostDBconnect()
{
    QSqlDatabase data_base = QSqlDatabase::addDatabase("QMYSQL");


    data_base.setHostName("127.0.0.1");
    data_base.setPort(3306);
    data_base.setDatabaseName("Fight");
    data_base.setUserName("root");
    data_base.setPassword("");

    if(data_base.open())
    {
        qInfo() << "открыто норм";
    }
    else
    {
         qInfo() << "не открыто, ошибка!!";
    }

    QSqlQuery query;
    query.exec("SELECT * FROM Item;");

    while (query.next())
    {
        QString name = query.value(0).toString();
        QString pass = query.value(1).toString();
        qInfo() << name << "   " << pass;
    }

    data_base.close();
}

void queryDB()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./profiles.db");

    if(db.open())
    {
        std::cout << "db openned" << std::endl;
    }
    else
    {
        std::cout << "db not open !!" << std::endl;
    }

    QSqlQuery query;
    query.exec("SELECT * FROM account;");

    while (query.next())
    {
        QString name = query.value(0).toString();
        QString pass = query.value(1).toString();
        std::cout << name.toStdString() << "   " << pass.toStdString() << std::endl;
    }

    db.close();
}

void createDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./profiles.db");

    if(db.open())
    {
        std::cout << "db created !!" << std::endl;
    }
    else
    {
        std::cout << "db not created !!" << std::endl;
    }

    QSqlQuery query;

    query.exec("CREATE TABLE account(login TEXT, password TEXT);");
    query.exec("INSERT INTO account VALUES ('user', '123456');");
    query.exec("INSERT INTO account VALUES ('admin', '654321');");

    db.close();

}
