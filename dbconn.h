
#ifndef _DBCONN_H_
#define _DBCONN_H_

/*
 * For basic info on working with MySQL in C, see:
 * http://www.cyberciti.biz/tips/linux-unix-connect-mysql-c-api-program.html
 */

#define DB_USERNAME "root"
#define DB_PASSWORD "notsecure"
#define DB_HOSTNAME "localhost"
#define DB_DATABASE "ADVANSE_FCO3"

MYSQL *db_connect();

#endif // _DBCONN_H_

