
#include <stdio.h>
#include <mysql.h>

#include "dbconn.h"

MYSQL *db_connect()
{
    int success = 0;
    MYSQL *conn = mysql_init(NULL);

    // If we get connected, this returns conn
    // If not, this returns NULL
    return mysql_real_connect(conn, DB_HOSTNAME, DB_USERNAME, DB_PASSWORD,
            DB_DATABASE, 0, NULL, 0);
}

