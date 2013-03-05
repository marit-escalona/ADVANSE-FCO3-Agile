
#include <stdio.h>
#include <mysql.h>

#include "dbconn.h"

#include "user.h"
#include "utils.h"

MYSQL *db_connect()
{
    int success = 0;
    MYSQL *conn = mysql_init(NULL);

    // If we get connected, this returns conn
    // If not, this returns NULL
    return mysql_real_connect(conn, DB_HOSTNAME, DB_USERNAME, DB_PASSWORD,
            DB_DATABASE, 0, NULL, 0);
}

User *db_get_users(MYSQL *conn, int *numUsers)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    User *users = NULL;
    User *user;
    int i = 0;

    mysql_query(conn, "SELECT id, name FROM Users;");
    result = mysql_use_result(conn);
    *numUsers = (int) mysql_num_rows(result);

    // There is no point in continuing if there are no users
    if (*numUsers == 0) {
        return NULL;
    }

    users = safe_alloc(sizeof(User) * *numUsers);

    while ((row = mysql_fetch_row(result))) {
        user = (users + i);
        user->rowID = atoi(row[0]);
        user_set_name(user, row[1]);

        i++;
    }

    mysql_free_result(result);
    return users;
}

