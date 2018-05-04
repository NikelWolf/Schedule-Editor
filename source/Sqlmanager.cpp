#include "Sqlmanager.h"


void SqlManager::createAllTables(){
    QSqlQuery query;

    QString sheduleTable  = "CREATE TABLE shedule ("
                   "inst_id TINYINT(1), curse_id TINYINT(1), group_id TINYINT(4), day_id TINYINT(1), "
                   "num_id TINYINT(1), parity_id TINYINT(1), subj_id TINYINT(4), prof_id TINYINT(4), "
                   "cab_id TINYINT(4) );";
    QString instituteTable = "CREATE TABLE institute( id TINYINT(4), name VARCHAR(20) );";
    QString coursesTable = "CREATE TABLE courses( id TINYINT(4), name VARCHAR(20) );";
    QString groupsTable = "CREATE TABLE groups( id TINYINT(4), name VARCHAR(20) );";
    QString day_of_weekTable = "CREATE TABLE day_of_week( id TINYINT(4), name VARCHAR(20) );";
    //
    //
    QString subjectsTable = "CREATE TABLE subjects( id TINYINT(4), name VARCHAR(20) );";
    QString proffesorsTable = "CREATE TABLE proffesors( id TINYINT(4), name VARCHAR(20) );";
    QString cabinetTable = "CREATE TABLE cabinet( id TINYINT(4), name VARCHAR(20) );";

    QStringList strExec = {
        sheduleTable,
        instituteTable,
        coursesTable,
        groupsTable,
        day_of_weekTable,
        subjectsTable,
        proffesorsTable,
        cabinetTable
    };
    for(QString str: strExec){
        if (!query.exec(str)) {
            qDebug() << "Unable to create " + str;
            qDebug() << query.lastError();
        }
    }
}

SqlManager::SqlManager(){

    if (QFile::exists(db_path)) {
        qDebug() << "DB exists";
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_path);

    if (!db.open()) {
        qDebug() << "Cannot open database: " << db.lastError();
    }

    QSqlQuery query;


    QString str = "INSERT INTO subjects (id, name) VALUES (1, 'физика');";
//    if (!query.exec(str)) {
//        qDebug() << "error";
//        qDebug() << query.lastError();
//    }
    QString strF =
          "INSERT INTO  shedule (inst_id, "
          "curse_id, group_id, day_id, num_id, "
          "parity_id, subj_id, prof_id, cab_id)"
          " VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9');";

    for(int i=1; i <10; ++i){
        QString j = QString::number(i);
        strF = strF.arg(j);

    }

    str = strF;
//    if (!query.exec(str)) {
//        qDebug() << "Unable to make insert opeation";
//        qDebug() << query.lastError();
//    }

//    if (!query.exec("SELECT shedule.subj_id, subjects.id, subjects.name FROM shedule, subjects  "
//                    "WHERE  shedule.subj_id =subjects.id;")
//            ) {
//        qDebug() << "Unable to execute query - exiting";
//        qDebug()<< query.lastError();
//    }

    QSqlRecord rec = query.record();

    while (query.next()) {
        qDebug() << query.value(0).toString()
                 << query.value(1).toString()
                 << query.value(2).toString()
                 << query.value(3).toString();

//          qDebug() << query.value(rec.indexOf("inst_id")).toString()
//          << query.value(rec.indexOf("curse_id")).toString()
//          << query.value(rec.indexOf("group_id")).toString()
//          << query.value(rec.indexOf("day_id")).toString()
//          << query.value(rec.indexOf("num_id")).toString()
//          << query.value(rec.indexOf("parity_id")).toString()
//          << query.value(rec.indexOf("subj_id")).toString()
//          << query.value(rec.indexOf("prof_id")).toString()
//          << query.value(rec.indexOf("cab_id")).toString();
    }
}
