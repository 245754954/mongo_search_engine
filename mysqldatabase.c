#include "mysqldatabase.h"

int init_database(wiser_env *env, const char *db_path)
{

    env->conn = mysql_init(NULL);
    if (!env->conn)
    {
        fprintf(stderr, "mysql_init failed\n");
        return EXIT_FAILURE;
    }

    env->conn = mysql_real_connect(env->conn, env->server, env->user, env->password, env->database, 0, NULL, 0);

    if (env->conn)
        printf("Connection success\n");
    else
        printf("Connection failed\n");

    mysql_query(env->conn, "DROP TABLE IF EXISTS `settings`;");
    mysql_query(env->conn, "DROP TABLE IF EXISTS `tokens`;");
    mysql_query(env->conn, "DROP TABLE IF EXISTS `documents`;");

    // mysql_query(env->conn,"drop database if exists invertindex;");
    // mysql_query(env->conn,"create database invertindex;");

    mysql_query(env->conn, "CREATE TABLE documents ("
                           "id int(11) NOT NULL AUTO_INCREMENT,"
                           "title text,"
                           "body text,"
                           "PRIMARY KEY (id)) ENGINE=InnoDB DEFAULT CHARSET=utf8;");

    mysql_query(env->conn,
                "CREATE TABLE tokens ("
                "id int(11) NOT NULL AUTO_INCREMENT,"
                "token text NOT NULL,"
                "docs_count int(255) NOT NULL,"
                "postings blob NOT NULL,"
                "PRIMARY KEY (id)"
                ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");

    mysql_query(env->conn,
                "CREATE TABLE settings ("
                "key varchar(255) NOT NULL,"
                "value varchar(255) DEFAULT NULL,"
                "PRIMARY KEY (key)"
                ") ENGINE=InnoDB DEFAULT CHARSET=utf8;");

    mysql_query(env->conn,
                "CREATE UNIQUE INDEX token_index ON tokens(token);");

    mysql_query(env->conn,
                "CREATE UNIQUE INDEX title_index ON documents(title);");

    env->get_document_id_st = mysql_stmt_init(env->conn);
    env->get_document_title_st = mysql_stmt_init(env->conn);
    env->insert_document_st = mysql_stmt_init(env->conn);
    env->update_document_st = mysql_stmt_init(env->conn);
    env->get_token_id_st = mysql_stmt_init(env->conn);
    env->get_token_st = mysql_stmt_init(env->conn);
    env->store_token_st = mysql_stmt_init(env->conn);
    env->get_postings_st = mysql_stmt_init(env->conn);
    env->update_postings_st = mysql_stmt_init(env->conn);
    env->get_settings_st = mysql_stmt_init(env->conn);
    env->replace_settings_st = mysql_stmt_init(env->conn);
    env->get_document_count_st = mysql_stmt_init(env->conn);
    env->begin_st = mysql_stmt_init(env->conn);
    env->commit_st = mysql_stmt_init(env->conn);
    env->rollback_st = mysql_stmt_init(env->conn);

    char *get_document_id_st_str = "SELECT id FROM documents WHERE title = ?;";
    char *get_document_title_st_str = "SELECT title FROM documents WHERE id = ?;";
    char *insert_document_st_str = "INSERT INTO documents (title, body) VALUES (?, ?);";
    char *update_document_st_str = "UPDATE documents set body = ? WHERE id = ?;";
    char *get_token_id_st_str = "SELECT id, docs_count FROM tokens WHERE token = ?;";
    char *get_token_st_str = "SELECT token FROM tokens WHERE id = ?;";
    char *store_token_st_str = "INSERT OR IGNORE INTO tokens (token, docs_count, postings) VALUES (?, 0, ?);";
    char *get_postings_st_str = "SELECT docs_count, postings FROM tokens WHERE id = ?;";
    char *update_postings_st_str = "UPDATE tokens SET docs_count = ?, postings = ? WHERE id = ?;";
    char *get_settings_st_str = "SELECT value FROM settings WHERE key = ?;";
    char *replace_settings_st_str = "INSERT OR REPLACE INTO settings (key, value) VALUES (?, ?);";
    char *get_document_count_st_str = "SELECT COUNT(*) FROM documents;";
    char *begin_st_str = "BEGIN;";
    char *commit_st_str = "COMMIT;";
    char *rollback_st_str = "ROLLBACK;";

    if (mysql_stmt_prepare(env->get_document_id_st,
                           get_document_id_st_str,
                           strlen(get_document_id_st_str)))
    {

        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    if (mysql_stmt_prepare(env->get_document_title_st,
                           get_document_title_st_str,
                           strlen(get_document_title_st_str)))
    {

        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    if (mysql_stmt_prepare(env->insert_document_st,
                           insert_document_st_str,
                           strlen(insert_document_st_str)))
    {
        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    if (mysql_stmt_prepare(env->update_document_st,
                           update_document_st_str,
                           strlen(update_document_st_str)))
    {
        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    if (mysql_stmt_prepare(env->get_token_id_st,
                           get_token_id_st_str,
                           strlen(get_token_id_st_str)))
    {
        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    if (mysql_stmt_prepare(env->get_token_st,
                           get_token_st_str,
                           strlen(get_token_st_str)))
    {
        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    if (mysql_stmt_prepare(
            env->store_token_st,
            store_token_st_str,
            strlen(store_token_st_str)))
    {
        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    if (mysql_stmt_prepare(

            env->get_postings_st,
            get_postings_st_str,
            strlen(get_postings_st_str)))
    {
        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    if (mysql_stmt_prepare(
            env->update_postings_st,
            update_postings_st_str,
            strlen(update_postings_st_str)))
    {
        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    if (mysql_stmt_prepare(
            env->get_settings_st,
            get_settings_st_str,
            strlen(get_settings_st_str)))
    {
        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    if (mysql_stmt_prepare(
            env->replace_settings_st,
            replace_settings_st_str,
            strlen(replace_settings_st_str)))
    {
        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    if (mysql_stmt_prepare(
            env->get_document_count_st,
            get_document_count_st_str,
            strlen(get_document_count_st_str)))
    {
        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    if (mysql_stmt_prepare(
            env->begin_st,
            begin_st_str,
            strlen(begin_st_str)))
    {
    };

    if (mysql_stmt_prepare(env->commit_st, commit_st_str, strlen(commit_st_str)))
    {
        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    }

    if (mysql_stmt_prepare(
            env->rollback_st,
            rollback_st_str,
            strlen(rollback_st_str)))
    {
        fprintf(stderr, "char *_prepare: %s\n", mysql_error(env->conn));
        return -1;
    };

    return EXIT_SUCCESS;
}
void fin_database(wiser_env *env)
{
    mysql_stmt_close(env->get_document_id_st);
    mysql_stmt_close(env->get_document_title_st);
    mysql_stmt_close(env->insert_document_st);
    mysql_stmt_close(env->update_document_st);
    mysql_stmt_close(env->get_token_id_st);
    mysql_stmt_close(env->get_token_st);
    mysql_stmt_close(env->store_token_st);
    mysql_stmt_close(env->get_postings_st);
    mysql_stmt_close(env->update_postings_st);
    mysql_stmt_close(env->get_document_count_st);
    mysql_stmt_close(env->replace_settings_st);
    mysql_stmt_close(env->get_document_count_st);
    mysql_stmt_close(env->commit_st);
    mysql_stmt_close(env->rollback_st);
    mysql_stmt_close(env->begin_st);
    mysql_close(env->conn);
}

int db_get_document_id(const wiser_env *env,const char *title, unsigned int title_size)
{
    int rc;
    my_bool is_null[0];
    my_bool error[0];
    int document_id;
    unsigned long length[0];
    mysql_stmt_reset(env->get_document_id_st);

    MYSQL_BIND params[1];
    memset(params, 0, sizeof(params));
    params[0].buffer_type = MYSQL_TYPE_STRING;
    params[0].buffer = title;
    params[0].buffer_length = title_size;
    mysql_stmt_bind_param(env->get_document_id_st, params);
    ////执行与语句句柄相关的预处理
    /* Execute the SELECT query */
    if (mysql_stmt_execute(env->get_document_id_st))
    {
        fprintf(stderr, " mysql_stmt_execute(), failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(env->get_document_id_st));
        exit(0);
    }
    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));
    /* INTEGER COLUMN */
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = (char *)&document_id;
    bind[0].is_null = &is_null[0];
    bind[0].length = &length[0];
    bind[0].error = &error[0];

    /* Bind the result buffers */
    if (mysql_stmt_bind_result(env->get_document_id_st, bind))
    {
        fprintf(stderr, " mysql_stmt_bind_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(env->get_document_id_st));
        exit(0);
    }

    if (mysql_stmt_fetch_column(env->get_document_count_st, bind, 0, 0))
    {

        /* Close the statement */
        if (mysql_stmt_close(env->get_document_id_st))
        {
            /* mysql_stmt_close() invalidates stmt, so call          */
            /* mysql_error(mysql) rather than mysql_stmt_error(stmt) */
            fprintf(stderr, " failed while closing the statement\n");
            fprintf(stderr, " %s\n", mysql_error(env->conn));
            exit(0);
        };
        return -1;
    }
    else
    {
        return document_id;
    }
}

// int db_get_document_title(const wiser_env *env, int document_id,
//                           const char **title, int *title_size)
// {
//     int rc;
//     MYSQL_BIND params[1];
//     memset(params, 0, sizeof(params));
//     params[0].buffer_type = MYSQL_TYPE_LONG;
//     params[0].buffer = document_id;
//     params[0].buffer_length = strlen(document_id);

//     mysql_stmt_reset(env->get_document_title_st);
//     mysql_stmt_bind_param(env->get_document_title_st, params);

//     mysql_stmt_execute(env->get_document_title_st);



//     rc = sqlite3_step(env->get_document_title_st);
//     if (rc == SQLITE_ROW)
//     {
//         if (title)
//         {
//             *title = (const char *)sqlite3_column_text(env->get_document_title_st,
//                                                        0);
//         }
//         if (title_size)
//         {
//             *title_size = (int)sqlite3_column_bytes(env->get_document_title_st,
//                                                     0);
//         }
//     }
//     return 0;
// }

int main(int argc, char const *argv[])
{
    
    
    return 0;
}
