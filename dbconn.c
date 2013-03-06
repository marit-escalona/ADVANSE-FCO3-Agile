
#include <stdio.h>
#include <string.h>
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
    int fn_ret;

    fn_ret = mysql_query(conn, "SELECT id, name FROM Users");

    if (fn_ret != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    // mysql_store_result gets *all* rows in one go
    result = mysql_store_result(conn);

    // For this to return the correct number of rows, all rows must already have
    // been retrieved from the database.
    *numUsers = (int) mysql_num_rows(result);

    // There is no point in continuing if there are no users
    if (*numUsers == 0) {
        return NULL;
    }

    // A utility function for allocation memory, from utils.h
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

void db_add_user(MYSQL *conn, User *user)
{
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    MYSQL_BIND bind[1];
    char *sql = "INSERT INTO Users (name) VALUES (?)";

    // Prepared statements are used here to prevent SQL injection
    if (mysql_stmt_prepare(stmt, sql, strlen(sql) != 0)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }

    // Specify data type and size
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = user->name;
    bind[0].buffer_length = strlen(user->name);
    bind[0].length = &bind[0].buffer_length;

    // Bind data to prepared statement
    mysql_stmt_bind_param(stmt, bind);

    // Run the prepared statement
    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }
}

