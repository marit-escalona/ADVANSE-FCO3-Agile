
#include <stdio.h>
#include <stdlib.h>
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

    // A utility function for allocating memory, from utils.h
    users = safe_alloc(sizeof(User) * *numUsers);

    while ((row = mysql_fetch_row(result))) {
        user = (users + i);
        user_init(user);
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
    if (mysql_stmt_prepare(stmt, sql, strlen(sql)) != 0) {
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

/*
 * Gets the programs for the specified user, and updates the user struct with
 * the retrieved programs.
 */
void db_get_programs_for_user(MYSQL *conn, User *user)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    Program *program;
    int i = 0;
    int fn_ret, numPrograms;
    char queryBuf[100];

    // We're dealing with an int - there should be no risk of SQL injection here
    sprintf(queryBuf, "SELECT id, programNumber FROM Programs WHERE userID = %d",
            user->rowID);

    fn_ret = mysql_query(conn, queryBuf);

    if (fn_ret != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    // mysql_store_result gets *all* rows in one go
    result = mysql_store_result(conn);

    // For this to return the correct number of rows, all rows must already have
    // been retrieved from the database.
    numPrograms = (int) mysql_num_rows(result);

    // There is no point in continuing if there are no users
    if (numPrograms == 0) {
        return;
    }

    while ((row = mysql_fetch_row(result))) {
        program = program_new();
        program->rowID = atoi(row[0]);
        program_set_prog_number(program, row[1]);
        user_add_program(user, program);

        i++;
    }

    mysql_free_result(result);
}


void db_get_trl_entries_for_program(MYSQL *conn, Program *program)
{
    // The commented out bit is roughly what a correct implementation looks
    // like.
    /*
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    MYSQL_BIND bind_param[1];
    MYSQL_BIND bind_result[4];
    char *sql = "SELECT id, startTime, endTime, phaseNumber "
        "FROM TimeRecordingLogEntries WHERE programID = ?";

    if (mysql_stmt_prepare(stmt, sql, strlen(sql)) != 0) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }

    // Set up parameter
    memset(bind_param, 0, sizeof(bind_param));
    bind_param[0].buffer_type = MYSQL_TYPE_STRING;
    bind_param[0].buffer = &program->rowID;
    bind_param[0].buffer_length = sizeof(program->rowID);
    bind_param[0].length = &bind_param[0].buffer_length;

    mysql_stmt_bind_param(stmt, bind_param);

    // Set up MYSQL_BIND output
    memset(bind_result, 0, sizeof(bind_result));

    // Run the prepared statement
    if (mysql_stmt_execute(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    }
    */

    // This is a quickly-made implementation specifically made for the
    // prototype.
    MYSQL_RES *result;
    MYSQL_ROW row;
    int i = 0;
    int fn_ret;
    char querySql[128];
    TRLEntry *trlEntry;

    sprintf(querySql, "SELECT id, startTime, endTime, phaseNumber FROM TimeRecordingLogEntries WHERE programID = %d", program->rowID);

    fn_ret = mysql_query(conn, querySql);

    if (fn_ret != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    // mysql_store_result gets *all* rows in one go
    result = mysql_store_result(conn);

    while ((row = mysql_fetch_row(result))) {
        printf("%s - %s\n", row[1], row[2]);
        trlEntry = trl_entry_new();
        trlEntry->rowID = atoi(row[0]);
        trl_entry_set_start_string_rep(trlEntry, row[1]);
        trl_entry_set_end_string_rep(trlEntry, row[2]);
        trlEntry->phaseID = atoi(row[3]);

        trl_add_entry(program->trl, trlEntry);
    }

    mysql_free_result(result);
}
