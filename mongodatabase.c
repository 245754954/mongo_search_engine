<<<<<<< HEAD
// #include "mongodatabase.h"
// #include <mongoc/mongoc.h>
// #include <mongoc/mongoc.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <errno.h>
// #include "util.h"
// #include <cjson/cJSON.h>
// int init_database2(wiser_env *env, const char *mongo_url)
// {

//    mongoc_init();

//    /*
//     * 创建一个新的client实例
//     */

//    env->client = mongoc_client_new(mongo_url);
//    if (!env->client)
//    {

//       return EXIT_FAILURE;
//    }

//    /*
//     * Register the application name so we can track it in the profile logs
//     * on the server. This can also be done from the URI (see other examples).
//     */
//    //mongoc_client_set_appname(env->client, "connect-example");

//    /*
//     * 获取数据库"db_name"和集合"coll_name"的句柄
//     */
//    /*
//     * Get a handle on the database "db_name" and collection "coll_name"
//     */
//    env->database = mongoc_client_get_database(env->client, "invertindex");
//    env->settings = mongoc_client_get_collection(env->client, "invertindex", "settings");
//    env->documents = mongoc_client_get_collection(env->client, "invertindex", "documents");
//    env->tokens = mongoc_client_get_collection(env->client, "invertindex", "tokens");
//    env->tokencountcollections = mongoc_client_get_collection(env->client, "invertindex", "tokencountcollections");
//    env->documentcountcollections = mongoc_client_get_collection(env->client, "invertindex", "documentcountcollections");

//    return 0;
// }

// void fin_database2(wiser_env *env)
// {

//    mongoc_collection_destroy(env->settings);
//    mongoc_collection_destroy(env->documents);
//    mongoc_collection_destroy(env->tokens);
//    mongoc_collection_destroy(env->documentcountcollections);
//    mongoc_collection_destroy(env->tokencountcollections);
//    mongoc_database_destroy(env->database);

//    mongoc_client_destroy(env->client);
//    mongoc_cleanup();
// }

// //if dind the corresponding _id ,then return 1 otherwise return 0;
// /**
//  * search  the corresponding article id corresponding article tittle
//  * @param[in] env: Architecture that stores the application runtime environment
//  * @param[in] title: article title
//  * @param[out] _id:the corresponding article id
//  */
// //SELECT id FROM documents WHERE title = ?;
// int db_get_document_id2(const wiser_env *env, const char *title, int64_t *_id)
// {

//    bson_t *query;
//    char *str = NULL;
//    const bson_t *doc;
//    mongoc_cursor_t *cursor;
//    query = bson_new();
//    BSON_APPEND_UTF8(query, "title", title);
//    cursor = mongoc_collection_find_with_opts(env->documents, query, NULL, NULL);
//    int id;
//    if (mongoc_cursor_next(cursor, &doc))
//    {

//       str = bson_as_canonical_extended_json(doc, NULL);

//       cJSON *json = cJSON_Parse(str);
//       id = atoi(cJSON_GetObjectItem(cJSON_GetObjectItem(json, "_id"), "$numberLong")->valuestring);
//       *(_id) = id;
//       bson_free(str);
//       bson_destroy(query);
//       mongoc_cursor_destroy(cursor);
//       return id;
//    }

//    //printf(" mongodatabase 103 the value of _id %ld\n", *(_id));
//    bson_destroy(query);
//    mongoc_cursor_destroy(cursor);
//    return 0;
// }

// //根据指定的文档编号获取文档标题
// //SELECT title FROM documents WHERE id = ?
// int db_get_document_title2(const wiser_env *env, int64_t document_id, char *title)
// {
//    bson_t *query;

//    char *str;
//    const bson_t *doc;
//    mongoc_cursor_t *cursor;
//    //set the query condition
//    // bson_oid_t oid;
//    // bson_oid_init_from_string(&oid, document_id);
//    // query = BCON_NEW("_id", BCON_OID(&oid));

//    query = BCON_NEW("_id", BCON_INT64(document_id));
//    cursor = mongoc_collection_find_with_opts(env->documents, query, NULL, NULL);

//    bson_iter_t iter;
//    // bson_type_t type;
//    //d const bson_value_t *value;
//    if (mongoc_cursor_next(cursor, &doc))
//    {
//       if (bson_iter_init(&iter, doc) && bson_iter_find(&iter, "title"))
//       {
//          //printf("Found field name key: %s\n", bson_iter_key(&iter));

//          // type = bson_iter_type(&iter);
//          // printf("The type: %d\n", (int)type);

//          //value = bson_iter_value(&iter);
//          // strcpy(title, value->value.v_utf8.str);

//          str = bson_as_canonical_extended_json(doc, NULL);
//          // printf("%s\n", str);
//          cJSON *json = cJSON_Parse(str);
//          cJSON *node = NULL;
//          node = cJSON_GetObjectItem(json, "title");
//          if (node == NULL)
//          {
//             printf("the value == NULL\n");
//          }
//          else
//          {
//             // printf("the valuee is %s\n", node->valuestring);
//             strcpy(title, node->valuestring);
//          }
//          // printf("%s\n", node->valuestring);

//          bson_free(str);
//          //rintf("String value is: %s", value->value.v_utf8.str);
//       }

//       // str = bson_as_json(doc, NULL);
//       // printf("%s\n", str);
//       // bson_free(str);
//    }
//    bson_destroy(query);
//    mongoc_cursor_destroy(cursor);
//    return 0;
// }

// //if add successfully ,then return 1, otherwise return 0
// /**
//  * Add the document to the documents table
//  * @param[in] env Architecture that stores the application runtime environment
//  * @param[in] title article title
//  * @param[in] body article body
//  */
// int db_add_document2(wiser_env *env, const char *title, const char *body)
// {
//    bson_t *doc = NULL;
//    bson_error_t error;
//    bson_t *update = NULL;
//    bson_t *query = NULL;
//    int64_t document_id;
//    //memset(document_id, 0, sizeof(document_id));
//    //if didn't find the _id corresponding to article title
//    if (!db_get_document_id2(env, title, &document_id))
//    {

//       //if get the result
//       //INSERT INTO documents (title, body) VALUES (?, ?);
//       doc = bson_new();
//       document_id = get_id_for_document(env);
//       BSON_APPEND_UTF8(doc, "title", title);
//       BSON_APPEND_UTF8(doc, "body", body);
//       BSON_APPEND_INT64(doc, "_id", document_id);

//       // 将bson文档插入到集合
//       if (!mongoc_collection_insert(env->documents, MONGOC_INSERT_NONE, doc, NULL, &error))
//       {
//          fprintf(stderr, "%s\n", error.message);
//          goto exit;
//       }
//    }
//    //if find the _id corresponding to article title then execute the update operation
//    else
//    {
//       //if didn't get the result
//       //UPDATE documents set body = ? WHERE id = ?;
//       // bson_oid_t oid;
//       // bson_oid_init_from_string(&oid, document_id);
//       // query = BCON_NEW("_id", BCON_OID(&oid));

//       query = BCON_NEW("_id", BCON_INT64(document_id));
//       update = BCON_NEW("$set", "{",
//                         "_id", BCON_INT64(document_id),
//                         "title", BCON_UTF8(title) /*修改值*/,
//                         "body", BCON_UTF8(body) /*修改值*/,
//                         "updated", BCON_BOOL(true) /*添加的字段*/,
//                         "}");
//       // 执行update操作。这个操作将使用update的内容去替换之前插入到数据库中的doc的内容
//       if (!mongoc_collection_update(env->documents, MONGOC_UPDATE_NONE, query, update, NULL, &error))
//       {
//          fprintf(stderr, "%s\n", error.message);
//          goto exit;
//       }
//    }

// exit:
//    if (doc)
//       bson_destroy(doc);
//    if (query)
//       bson_destroy(query);
//    if (update)
//       bson_destroy(update);
//    return document_id;
// }

// /**
//  * 获取已添加到数据库中的文档数
//  * @param[in] env 存储着应用程序运行环境的结构体
//  */
// int db_get_document_count2(const wiser_env *env)
// {

//    bson_error_t error;
//    // 进行统计操作
//    bson_t *filter = BCON_NEW(NULL, NULL);

//    int64_t count = mongoc_collection_count_documents(env->documents, filter, 0, 0, NULL, &error);
//    //printf("the value of document_count %ld\n",count);
//    if (count < 0)
//    {
//       fprintf(stderr, "%s\n", error.message);
//    }

//    bson_destroy(filter);
//    //`printf("the document_count is %ld\n", count);
//    return (int)count;
// }

// //return the id of specified vocabulary
// /**
//  * Get the number of the specified vocabulary from the tokens table
//  * @param[in] env Architecture that stores the application runtime environment
//  * @param[in] str Vocabulary (UTF-8)
//  * @param[in] insert Do you want to add the specified lexicon to the table when it is not found?
//  * @param[out] docs_count Number of documents with a specified vocabulary
//  */
// //INSERT OR IGNORE INTO tokens (token, docs_count, postings)
// int db_get_token_id2(const wiser_env *env, const char *token, int insert, int *docs_count)
// {

//    const bson_t *doc;
//    bson_t *insert_doc = NULL;
//    bson_t *query = bson_new();
//    mongoc_cursor_t *cursor;
//    char *str = NULL;
//    BSON_APPEND_UTF8(query, "token", token);

//    if (insert)
//    {
//       int64_t _id;
//       //if get the result
//       //INSERT OR IGNORE INTO tokens (token, docs_count, postings)"
//       //           " VALUES (?, 0, ?);",
//       cursor = mongoc_collection_find_with_opts(env->tokens, query, NULL, NULL);
//       if (!mongoc_cursor_next(cursor, &doc))
//       {
//          insert_doc = bson_new();
//          _id = get_id_for_token(env);
//          BSON_APPEND_INT64(insert_doc, "_id", _id);
//          BSON_APPEND_UTF8(insert_doc, "token", token);
//          BSON_APPEND_INT64(insert_doc, "docs_count", 0);
//          BSON_APPEND_BINARY(insert_doc, "postings", BSON_SUBTYPE_BINARY, "", 0);

//          // 将bson文档插入到集合
//          if (!mongoc_collection_insert(env->tokens, MONGOC_INSERT_NONE, insert_doc, NULL, NULL))
//          {

//             fprintf(stderr, "%s\n", "error mongodatabase.c 592");
//          }
//       }
//    }
//    // //SELECT id, docs_count FROM tokens WHERE token = ?
//    // bson_t *opts = BCON_NEW("projection", "{",
//    //                         "docs_count", BCON_BOOL(true),
//    //                         "_id", BCON_BOOL(true), "}");
//    cursor = mongoc_collection_find_with_opts(env->tokens, query, NULL, NULL);
//    if (mongoc_cursor_next(cursor, &doc))
//    {
//       str = bson_as_canonical_extended_json(doc, NULL);

//       cJSON *json = cJSON_Parse(str);
//       int id;
//       int doc_count;

//       id = atoi(cJSON_GetObjectItem(cJSON_GetObjectItem(json, "_id"), "$numberLong")->valuestring);
//       doc_count = atoi(cJSON_GetObjectItem(cJSON_GetObjectItem(json, "docs_count"), "$numberLong")->valuestring);
//       //printf("the value of doc_count is %d\n", doc_count->valueint);
//       if (docs_count)
//       {
//          *docs_count = doc_count;
//       }
//       //printf("the token is %s and his id is %d\n ",token,id);
//       if (insert_doc)
//          bson_destroy(insert_doc);
//       bson_free(str);
//       bson_destroy(query);
//       mongoc_cursor_destroy(cursor);

//       return id;
//    }

//    else
//    {

//       if (docs_count)
//       {
//          *docs_count = 0;
//       }
//       if (insert_doc)
//          bson_destroy(insert_doc);
//       bson_destroy(query);
//       mongoc_cursor_destroy(cursor);
//       return 0;
//    }
// }

// int db_get_token2(const wiser_env *env, int token_id, char **token)
// {
//    bson_t *query;
//    char *str = NULL;
//    const bson_t *doc;
//    mongoc_cursor_t *cursor;

//    query = bson_new();
//    BSON_APPEND_INT64(query, "_id", token_id);
//    cursor = mongoc_collection_find_with_opts(env->tokens, query, NULL, NULL);
//    if (mongoc_cursor_next(cursor, &doc))
//    {

//       str = bson_as_canonical_extended_json(doc, NULL);
//       cJSON *json = cJSON_Parse(str);

//       cJSON *token_str = NULL;

//       token_str = cJSON_GetObjectItem(json, "token");
//       if (NULL == token)
//       {
//          printf("the token  == NULL\n");
//       }
//       else
//       {
//          //printf("the value of toekn_str is %s\n", token_str->valuestring);
//          *token = token_str->valuestring;
//       }
//    }

//    bson_destroy(query);
//    mongoc_cursor_destroy(cursor);
//    if (str)
//       bson_free(str);
//    return 0;
// }

// /**
//  * 根据词元编号从数据库中获取倒排列表
//  * @param[in] env 存储着应用程序运行环境的结构体
//  * @param[in] token_id 词元编号
//  * @param[out] docs_count 倒排列表中的文档数
//  * @param[out] postings 获取到的倒排列表
//  * @param[out] postings_size 获取到的倒排列表的字节数
//  */
// //SELECT docs_count, postings FROM tokens WHERE id = ?;
// int db_get_postings2(const wiser_env *env, int token_id,
//                      int *docs_count, void **postings, int *posting_size)
// {

//    bson_t *query = bson_new();
//    char *str;
//    const bson_t *doc;
//    bson_t *opts;
//    mongoc_cursor_t *cursor;

//    // opts = BCON_NEW("projection", "{",
//    //                 "docs_count", BCON_BOOL(true),
//    //                 "postings", BCON_BOOL(true),
//    //                 "_id", BCON_BOOL(false), "}");
//    BSON_APPEND_INT64(query, "_id", token_id);
//    //int starttime, endtime;
//    //starttime = clock();
//    cursor = mongoc_collection_find_with_opts(env->tokens, query, NULL, NULL);
//    //endtime = clock();
//    //printf("\n\n11 db_get_postings2 mongoc_collection_find_with_opts Time：%d ms\n", endtime - starttime);

//    if (mongoc_cursor_next(cursor, &doc))
//    {
//       //int starttime1, endtime1;
//       //starttime1 = clock();

//       //int starttime2, endtime2;
//       //starttime2 = clock();
//       str = bson_as_canonical_extended_json(doc, NULL);
//       // endtime2 = clock();
//       //printf("\n\n11 bson_as_canonical_extended_json Time：%d ms\n", endtime2 - starttime2);

//       //printf("%s\n", str);

//       //int starttime3, endtime3;
//       //starttime3 = clock();
//       cJSON *json = cJSON_Parse(str);
//       cJSON *docs_count_str = NULL;
//       docs_count_str = cJSON_GetObjectItem(cJSON_GetObjectItem(json, "docs_count"), "$numberLong");
//       //endtime3 = clock();
//       // printf("\n\n11 getitem Time：%d ms\n", endtime3 - starttime3);

//       //int starttime4, endtime4;
//       //starttime4 = clock();
//       bson_iter_t iter;
//       const bson_value_t *value;
//       bson_iter_init(&iter, doc);
//       bson_iter_find_case(&iter, "postings");
//       value = bson_iter_value(&iter);
//       //bson_subtype_t subtype = BSON_SUBTYPE_BINARY;
//       //endtime4 = clock();
//       //printf("\n\n11 decode postings Time：%d ms\n", endtime4 - starttime4);

//       //int starttime5, endtime5;
//       //starttime5 = clock();
//       if (docs_count)
//       {
//          *docs_count = atoi(docs_count_str->valuestring);
//       }

//       if (postings)
//       {
//          *postings = (void *)value->value.v_binary.data;
//       }
//       if (posting_size)
//       {

//          *posting_size = (int)value->value.v_binary.data_len;
//       }
//       //endtime5 = clock();
//       //printf("\n\n11 set value postings Time：%d ms\n", endtime5 - starttime5);

//       //clock_t starttime6, endtime6;
//       //starttime6 = clock();
//       bson_destroy(query);
//       mongoc_cursor_destroy(cursor);
//       bson_free(str);
//       //endtime6 = clock();
//       //printf("\n\n11 destroy Time：%dms\n", endtime6 - starttime6);

//       //endtime1 = clock();
//       //printf("\n\n11 db_get_postings2 if sentence Time：%d ms\n", endtime1 - starttime1);

//       return 0;
//    }
//    else
//    {

//       if (docs_count)
//       {
//          *docs_count = 0;
//       }

//       if (postings)
//       {
//          *postings = NULL;
//       }
//       if (posting_size)
//       {

//          *posting_size = 0;
//       }

//       bson_destroy(query);
//       mongoc_cursor_destroy(cursor);

//       return 0;
//    }
// }

// /**
//  * 将倒排列表存储到数据库中
//  * @param[in] env 存储着应用程序运行环境的结构体
//  * @param[in] token_id 词元编号
//  * @param[in] docs_count 倒排列表中的文档数
//  * @param[in] postings 待存储的倒排列表
//  * @param[in] postings_size 倒排列表的字节数
//  */
// int db_update_postings2(const wiser_env *env, int token_id, int docs_count,
//                         void *postings, int postings_size)
// {
//    bson_t *query = bson_new();
//    bson_t *update = bson_new();
//    bson_error_t error;
//    BSON_APPEND_INT64(query, "_id", token_id);
//    char *token;
//    db_get_token2(env, token_id, &token);
//    // printf("the value of token_id %d\n",token_id);
//    // char buf[postings_size];
//    // memset(buf,0,sizeof(buf));

//    // memcpy(buf,postings,sizeof(char)*);
//    // char *buf = "asdasd";
//    // printf("the value of buf %s\n",buf);
//    // BSON_APPEND_UTF8(update, "postings", (char *)postings);
//    // printf("the size of postings %d\n", postings_size);
//    // update = BCON_NEW("$set", "{"
//    //                      "postings", BCON_BIN(BSON_SUBTYPE_BINARY, (const uint8_t *)postings, (uint32_t)postings_size) /*修改值*/,
//    //                      "docs_count",BCON_INT64(docs_count),
//    //                      "updated", BCON_BOOL(true) /*添加的字段*/,
//    //                      "}");
//    BSON_APPEND_INT64(update, "_id", token_id);
//    BSON_APPEND_UTF8(update, "token", token);
//    BSON_APPEND_BINARY(update, "postings", BSON_SUBTYPE_BINARY, (const uint8_t *)postings, (uint32_t)postings_size);
//    BSON_APPEND_INT64(update, "docs_count", docs_count);

//    // 执行update操作。这个操作将使用update的内容去替换之前插入到数据库中的doc的内容
//    if (!mongoc_collection_update(env->tokens, MONGOC_UPDATE_NONE, query, update, NULL, &error))
//    {
//       fprintf(stderr, "%s\n", error.message);
//    }

//    bson_destroy(query);

//    bson_destroy(update);

//    return 0;
// }
// int db_get_settings2(wiser_env *env, char *key, char *value)
// {

//    int rc;
//    bson_t *query;

//    char *str;
//    const bson_t *doc;
//    mongoc_cursor_t *cursor;
//    // bson_oid_t oid;
//    // bson_oid_init_from_string(&oid, key);
//    // query = BCON_NEW("key", BCON_OID(&oid));
//    query = bson_new();
//    //printf("%s\n", key);
//    BSON_APPEND_UTF8(query, "key", key);
//    cursor = mongoc_collection_find_with_opts(env->settings, query, NULL, NULL);

//    while (mongoc_cursor_next(cursor, &doc))
//    {

//       str = bson_as_canonical_extended_json(doc, NULL);
//       //  printf("%s\n", str);
//       cJSON *json = cJSON_Parse(str);
//       cJSON *node = NULL;
//       node = cJSON_GetObjectItem(json, "value");
//       if (node == NULL)
//       {
//          printf("the value == NULL\n");
//          return 0;
//       }
//       else
//       {
//          //printf("the valuee is %s\n", node->valuestring);
//       }
//       // printf("%s\n", node->valuestring);
//       strcpy(value, node->valuestring);
//       if (str)
//          bson_free(str);
// #if 0
//       // str = bson_as_json(doc, NULL);
//       // printf("%s\n", str);
//       // bson_free(str);
// #endif
//       if (doc)
//          bson_destroy((bson_t *)doc);
//       if (query)
//          bson_destroy(query);
//       if (cursor)
//          mongoc_cursor_destroy(cursor);
//       return 1;
//       // str = bson_as_json(doc, NULL);
//       // printf("%s\n", str);
//       // bson_free(str);
//    }
//    //printf("the value of _id %s\n",_id);

//    return 0;
// }
// /**
//  * 更新存储在数据库中的配置信息
//  * @param[in] env 存储着应用程序运行环境的结构体
//  * @param[in] key 配置项的名称
//  * @param[in] key_size 配置项名称的字节数
//  * @param[in] value 配置项的取值
//  * @param[in] value_size 配置项取值的字节数
//  */
// int db_replace_settings2(wiser_env *env, char *key, char *value)
// {

//    bson_t *query;
//    char *str = NULL;
//    const bson_t *doc;
//    mongoc_cursor_t *cursor;
//    bson_error_t error;
//    query = bson_new();
//    BSON_APPEND_UTF8(query, "key", key);
//    cursor = mongoc_collection_find_with_opts(env->settings, query, NULL, NULL);

//    if (mongoc_cursor_next(cursor, &doc))
//    {

//       str = bson_as_canonical_extended_json(doc, NULL);
//       cJSON *json = cJSON_Parse(str);
//       cJSON *key_value = NULL;

//       key_value = cJSON_GetObjectItem(json, "key");
//       if (key_value == NULL)
//       {
//          printf("the key_value == NULL\n");
//       }
//       else
//       {
//          bson_t *query1;
//          bson_t *update1;
//          // printf("the key_value is %s\n", key_value->valuestring);

//          query1 = BCON_NEW("key", BCON_UTF8(key));
//          update1 = BCON_NEW("$set", "{",
//                             "key", BCON_UTF8(key) /*修改值*/,
//                             "value", BCON_UTF8(value) /*修改值*/,
//                             "updated", BCON_BOOL(true) /*添加的字段*/,
//                             "}");
//          // 执行update操作。这个操作将使用update的内容去替换之前插入到数据库中的doc的内容
//          if (!mongoc_collection_update(env->settings, MONGOC_UPDATE_NONE, query1, update1, NULL, &error))
//          {
//             fprintf(stderr, "%s\n", error.message);
//          }

//          bson_destroy(query1);
//          bson_destroy(update1);
//       }

//       if (str)
//          bson_free(str);

//       mongoc_cursor_destroy(cursor);
//       return 1;
//    }
//    else
//    {

//       //if get the result
//       //INSERT INTO documents (title, body) VALUES (?, ?);
//       bson_t *doc;
//       doc = bson_new();

//       BSON_APPEND_UTF8(doc, "key", key);
//       BSON_APPEND_UTF8(doc, "value", value);

//       // 将bson文档插入到集合
//       if (!mongoc_collection_insert(env->settings, MONGOC_INSERT_NONE, doc, NULL, &error))
//       {
//          fprintf(stderr, "%s\n", error.message);
//       }
//       if (str)
//          bson_free(str);
//       if (doc)
//          bson_destroy(doc);
//       if (query)
//          bson_destroy(query);

//       mongoc_cursor_destroy(cursor);
//       return 1;
//    }
// }

// //generate id for article autoincrement
// int64_t get_id_for_document(const wiser_env *env)
// {

//    int64_t ret = -1;

//    //mongoc_collection_t *pCountCollection = mongoc_client_get_collection(m_pClient, "test_db", "id_generator");

//    bson_error_t error;
//    bson_t *doc = bson_new();

//    bson_t child;
//    bson_append_document_begin(doc, "$inc", -1, &child);
//    BSON_APPEND_INT64(&child, "current_id_value", 1);
//    bson_append_document_end(doc, &child);

//    bson_t query;
//    bson_init(&query);
//    BSON_APPEND_INT64(&query, "_id", 1);

//    bson_t reply;
//    bool r = mongoc_collection_find_and_modify(env->documentcountcollections,
//                                               &query,
//                                               NULL,
//                                               doc,
//                                               NULL,
//                                               false,
//                                               true,
//                                               true,
//                                               &reply,
//                                               &error);
//    if (!r)
//    {
//       printf("GetID Failure: %s\n", error.message);
//    }
//    else
//    {
//       bson_iter_t iter;
//       bson_iter_init(&iter, &reply);
//       if (bson_iter_find(&iter, "value"))
//       {
//          const uint8_t *buf;
//          uint32_t len;
//          bson_iter_document(&iter, &len, &buf);
//          bson_t rec;
//          bson_init_static(&rec, buf, len);

//          bson_iter_init(&iter, &rec);
//          if (bson_iter_find(&iter, "current_id_value"))
//          {
//             ret = bson_iter_int64(&iter);
//          }
//          bson_destroy(&rec);
//       }
//    }

//    bson_destroy(&query);
//    bson_destroy(&reply);
//    bson_destroy(doc);
//    // printf("%ld\n", ret);
//    return ret;
// }

// int64_t get_id_for_token(const wiser_env *env)
// {

//    int64_t ret = -1;

//    //mongoc_collection_t *pCountCollection = mongoc_client_get_collection(m_pClient, "test_db", "id_generator");

//    bson_error_t error;
//    bson_t *doc = bson_new();

//    bson_t child;
//    bson_append_document_begin(doc, "$inc", -1, &child);
//    BSON_APPEND_INT64(&child, "current_id_value", 1);
//    bson_append_document_end(doc, &child);

//    bson_t query;
//    bson_init(&query);
//    BSON_APPEND_INT64(&query, "_id", 1);

//    bson_t reply;
//    bool r = mongoc_collection_find_and_modify(env->tokencountcollections,
//                                               &query,
//                                               NULL,
//                                               doc,
//                                               NULL,
//                                               false,
//                                               true,
//                                               true,
//                                               &reply,
//                                               &error);
//    if (!r)
//    {
//       printf("GetID Failure: %s\n", error.message);
//    }
//    else
//    {
//       bson_iter_t iter;
//       bson_iter_init(&iter, &reply);
//       if (bson_iter_find(&iter, "value"))
//       {
//          const uint8_t *buf;
//          uint32_t len;
//          bson_iter_document(&iter, &len, &buf);
//          bson_t rec;
//          bson_init_static(&rec, buf, len);

//          bson_iter_init(&iter, &rec);
//          if (bson_iter_find(&iter, "current_id_value"))
//          {
//             ret = bson_iter_int64(&iter);
//          }
//          bson_destroy(&rec);
//       }
//    }

//    bson_destroy(&query);
//    bson_destroy(&reply);
//    bson_destroy(doc);
//    // printf("%ld\n", ret);
//    return ret;
// }
=======
#include "mongodatabase.h"
#include <mongoc/mongoc.h>
#include "myclient.h"
#include <mongoc/mongoc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cjson/cJSON.h>
int init_database2(client_env *env, const char *mongo_url)
{

   mongoc_init();

   /*
    * 创建一个新的client实例
    */

   env->client = mongoc_client_new(mongo_url);
   if (!env->client)
   {

      return EXIT_FAILURE;
   }

   /*
    * Register the application name so we can track it in the profile logs
    * on the server. This can also be done from the URI (see other examples).
    */
   mongoc_client_set_appname(env->client, "connect-example");

   /*
    * 获取数据库"db_name"和集合"coll_name"的句柄
    */
   /*
    * Get a handle on the database "db_name" and collection "coll_name"
    */
   env->database = mongoc_client_get_database(env->client, "invertindex");
   env->settings = mongoc_client_get_collection(env->client, "invertindex", "settings");
   env->documents = mongoc_client_get_collection(env->client, "invertindex", "documents");
   env->tokens = mongoc_client_get_collection(env->client, "invertindex", "tokens");
   env->tokencountcollections = mongoc_client_get_collection(env->client, "invertindex", "tokencountcollections");
   env->documentcountcollections = mongoc_client_get_collection(env->client, "invertindex", "documentcountcollections");
   return 0;
}

int fin_database2(client_env *env)
{

   mongoc_collection_destroy(env->settings);
   mongoc_collection_destroy(env->documents);
   mongoc_collection_destroy(env->tokens);
   mongoc_collection_destroy(env->documentcountcollections);
   mongoc_collection_destroy(env->tokencountcollections);
   mongoc_database_destroy(env->database);

   mongoc_client_destroy(env->client);
   mongoc_cleanup();
   return 0;
}

//search  the corresponding article id corresponding article tittle
int db_get_document_id2(client_env *env, char *title, int64_t *_id)
{

   bson_t *query;

   char *str;
   const bson_t *doc;
   mongoc_cursor_t *cursor;
   //set the query condition

   query = bson_new();
   BSON_APPEND_UTF8(query, "title", title);
   cursor = mongoc_collection_find_with_opts(env->documents, query, NULL, NULL);
   bson_iter_t iter;
   while (mongoc_cursor_next(cursor, &doc))
   {

      if (bson_iter_init(&iter, doc) && bson_iter_find(&iter, "_id"))
      {

         // char oidstr[25];
         // const bson_oid_t *oid = bson_iter_oid(&iter);
         // bson_oid_to_string(oid, oidstr);
         // strcpy(_id, oidstr);
         // printf("%s\n", oidstr);

         *(_id) = bson_iter_as_int64(&iter);
         printf("the value of _id %ld\n", *(_id));
      }
      bson_destroy((bson_t *)doc);
      bson_destroy(query);
      mongoc_cursor_destroy(cursor);
      return 1;
      // str = bson_as_json(doc, NULL);
      // printf("%s\n", str);
      // bson_free(str);
   }
   //printf("the value of _id %s\n",_id);

   return 0;
}

//根据指定的文档编号获取文档标题
//SELECT title FROM documents WHERE id = ?
void db_get_document_title2(const client_env *env, int64_t document_id, char *title)
{
   bson_t *query;

   char *str;
   const bson_t *doc;
   mongoc_cursor_t *cursor;
   //set the query condition
   // bson_oid_t oid;
   // bson_oid_init_from_string(&oid, document_id);
   // query = BCON_NEW("_id", BCON_OID(&oid));

   query = BCON_NEW("_id", BCON_INT64(document_id));
   cursor = mongoc_collection_find_with_opts(env->documents, query, NULL, NULL);

   bson_iter_t iter;
   bson_type_t type;
   const bson_value_t *value;
   while (mongoc_cursor_next(cursor, &doc))
   {
      if (bson_iter_init(&iter, doc) && bson_iter_find(&iter, "title"))
      {
         //printf("Found field name key: %s\n", bson_iter_key(&iter));

         // type = bson_iter_type(&iter);
         // printf("The type: %d\n", (int)type);

         value = bson_iter_value(&iter);
         strcpy(title, value->value.v_utf8.str);
         //rintf("String value is: %s", value->value.v_utf8.str);
      }

      // str = bson_as_json(doc, NULL);
      // printf("%s\n", str);
      // bson_free(str);
   }

   bson_destroy((bson_t *)doc);
   bson_destroy(query);
   mongoc_cursor_destroy(cursor);
   return;
}

/**
 * 将文档添加到documents表中
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] title 文档标题
 * @param[in] title_size 文档标题的字节数
 * @param[in] body 文档正文
 * @param[in] body_size 文档正文的字节数
 */
int db_add_document2(client_env *env,
                     char *title,
                     char *body)
{
   bson_t *doc;
   bson_error_t error;
   bson_t *update = NULL;
   bson_t *query = NULL;
   int64_t document_id;
   //memset(document_id, 0, sizeof(document_id));
   if (!db_get_document_id2(env, title, &document_id))
   {

      //if get the result
      //INSERT INTO documents (title, body) VALUES (?, ?);
      doc = bson_new();
      int64_t _id = get_id_for_document(env);
      BSON_APPEND_UTF8(doc, "title", title);
      BSON_APPEND_UTF8(doc, "body", body);
      BSON_APPEND_INT64(doc, "_id", _id);

      // 将bson文档插入到集合
      if (!mongoc_collection_insert(env->documents, MONGOC_INSERT_NONE, doc, NULL, &error))
      {
         fprintf(stderr, "%s\n", error.message);
         goto exit;
      }
   }
   else
   {
      //if didn't get the result
      //UPDATE documents set body = ? WHERE id = ?;
      // bson_oid_t oid;
      // bson_oid_init_from_string(&oid, document_id);
      // query = BCON_NEW("_id", BCON_OID(&oid));

      query = BCON_NEW("_id", BCON_INT64(document_id));
      update = BCON_NEW("$set", "{",
                        "title", BCON_UTF8(title) /*修改值*/,
                        "body", BCON_UTF8(body) /*修改值*/,
                        "updated", BCON_BOOL(true) /*添加的字段*/,
                        "}");
      // 执行update操作。这个操作将使用update的内容去替换之前插入到数据库中的doc的内容
      if (!mongoc_collection_update(env->documents, MONGOC_UPDATE_NONE, query, update, NULL, &error))
      {
         fprintf(stderr, "%s\n", error.message);
         goto exit;
      }
   }
exit:
   if (doc)
      bson_destroy(doc);
   if (query)
      bson_destroy(query);
   if (update)
      bson_destroy(update);
   // printf("%s\n","hello");
   return 1;
}

//generate id autoincrement
int64_t get_id_for_document(client_env *env)
{

   int64_t ret = -1;

   //mongoc_collection_t *pCountCollection = mongoc_client_get_collection(m_pClient, "test_db", "id_generator");

   bson_error_t error;
   bson_t *doc = bson_new();

   bson_t child;
   bson_append_document_begin(doc, "$inc", -1, &child);
   BSON_APPEND_INT64(&child, "current_id_value", 1);
   bson_append_document_end(doc, &child);

   bson_t query;
   bson_init(&query);
   BSON_APPEND_INT64(&query, "_id", 1);

   bson_t reply;
   bool r = mongoc_collection_find_and_modify(env->documentcountcollections,
                                              &query,
                                              NULL,
                                              doc,
                                              NULL,
                                              false,
                                              true,
                                              true,
                                              &reply,
                                              &error);
   if (!r)
   {
      printf("GetID Failure: %s\n", error.message);
   }
   else
   {
      bson_iter_t iter;
      bson_iter_init(&iter, &reply);
      if (bson_iter_find(&iter, "value"))
      {
         const uint8_t *buf;
         uint32_t len;
         bson_iter_document(&iter, &len, &buf);
         bson_t rec;
         bson_init_static(&rec, buf, len);

         bson_iter_init(&iter, &rec);
         if (bson_iter_find(&iter, "current_id_value"))
         {
            ret = bson_iter_int64(&iter);
         }
         bson_destroy(&rec);
      }
   }

   bson_destroy(&query);
   bson_destroy(&reply);
   bson_destroy(doc);
   printf("%ld\n", ret);
   return ret;
}

int64_t get_id_for_token(client_env *env)
{

   int64_t ret = -1;

   //mongoc_collection_t *pCountCollection = mongoc_client_get_collection(m_pClient, "test_db", "id_generator");

   bson_error_t error;
   bson_t *doc = bson_new();

   bson_t child;
   bson_append_document_begin(doc, "$inc", -1, &child);
   BSON_APPEND_INT64(&child, "current_id_value", 1);
   bson_append_document_end(doc, &child);

   bson_t query;
   bson_init(&query);
   BSON_APPEND_INT64(&query, "_id", 1);

   bson_t reply;
   bool r = mongoc_collection_find_and_modify(env->tokencountcollections,
                                              &query,
                                              NULL,
                                              doc,
                                              NULL,
                                              false,
                                              true,
                                              true,
                                              &reply,
                                              &error);
   if (!r)
   {
      printf("GetID Failure: %s\n", error.message);
   }
   else
   {
      bson_iter_t iter;
      bson_iter_init(&iter, &reply);
      if (bson_iter_find(&iter, "value"))
      {
         const uint8_t *buf;
         uint32_t len;
         bson_iter_document(&iter, &len, &buf);
         bson_t rec;
         bson_init_static(&rec, buf, len);

         bson_iter_init(&iter, &rec);
         if (bson_iter_find(&iter, "current_id_value"))
         {
            ret = bson_iter_int64(&iter);
         }
         bson_destroy(&rec);
      }
   }

   bson_destroy(&query);
   bson_destroy(&reply);
   bson_destroy(doc);
   printf("%ld\n", ret);
   return ret;
}

/**
 * 获取已添加到数据库中的文档数
 * @param[in] env 存储着应用程序运行环境的结构体
 */
int db_get_document_count2(client_env *env)
{

   int64_t count;
   bson_error_t error;
   bson_t *doc;
   // 进行统计操作
   bson_t *filter = BCON_NEW(NULL, NULL);

   count = mongoc_collection_count_documents(env->documents, filter, 0, 0, NULL, &error);

   if (count < 0)
   {
      fprintf(stderr, "%s\n", error.message);
   }
   else
   {
      printf("%" PRId64 "\n", count);
   }
   bson_destroy(filter);
   bson_destroy(doc);
   return count;
}

int db_get_settings2(client_env *env, char *key, char *value)
{

   int rc;
   bson_t *query;

   char *str;
   const bson_t *doc;
   mongoc_cursor_t *cursor;
   // bson_oid_t oid;
   // bson_oid_init_from_string(&oid, key);
   // query = BCON_NEW("key", BCON_OID(&oid));
   query = bson_new();
   printf("%s\n", key);
   BSON_APPEND_UTF8(query, "key", key);
   cursor = mongoc_collection_find_with_opts(env->settings, query, NULL, NULL);

   while (mongoc_cursor_next(cursor, &doc))
   {

      str = bson_as_canonical_extended_json(doc, NULL);
      cJSON *json = cJSON_Parse(str);
      cJSON *node = NULL;
      node = cJSON_GetObjectItem(json, "value");
      if (node == NULL)
      {
         printf("the value == NULL\n");
         return 0;
      }
      else
      {
         printf("the valuee is %s\n", node->valuestring);
      }
      strcpy(value, node->valuestring);
      bson_free(str);
#if 0
      // str = bson_as_json(doc, NULL);
      // printf("%s\n", str);
      // bson_free(str);
#endif
      bson_destroy((bson_t *)doc);
      bson_destroy(query);
      mongoc_cursor_destroy(cursor);
      return 1;
      // str = bson_as_json(doc, NULL);
      // printf("%s\n", str);
      // bson_free(str);
   }
   //printf("the value of _id %s\n",_id);

   return 0;
}
/**
 * 更新存储在数据库中的配置信息
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] key 配置项的名称
 * @param[in] key_size 配置项名称的字节数
 * @param[in] value 配置项的取值
 * @param[in] value_size 配置项取值的字节数
 */
int db_replace_settings2(client_env *env, char *key, char *value)
{

   bson_t *query;
   char *str = NULL;
   const bson_t *doc;
   mongoc_cursor_t *cursor;
   bson_error_t error;
   query = bson_new();
   BSON_APPEND_UTF8(query, "key", key);
   cursor = mongoc_collection_find_with_opts(env->settings, query, NULL, NULL);

   if (mongoc_cursor_next(cursor, &doc))
   {

      str = bson_as_canonical_extended_json(doc, NULL);
      cJSON *json = cJSON_Parse(str);
      cJSON *key_value = NULL;

      key_value = cJSON_GetObjectItem(json, "key");
      if (key_value == NULL)
      {
         printf("the key_value == NULL\n");
      }
      else
      {
         bson_t *query1;
         bson_t *update1;
         printf("the key_value is %s\n", key_value->valuestring);

         query1 = BCON_NEW("key", BCON_UTF8(key));
         update1 = BCON_NEW("$set", "{",
                            "key", BCON_UTF8(key) /*修改值*/,
                            "value", BCON_UTF8(value) /*修改值*/,
                            "updated", BCON_BOOL(true) /*添加的字段*/,
                            "}");
         // 执行update操作。这个操作将使用update的内容去替换之前插入到数据库中的doc的内容
         if (!mongoc_collection_update(env->settings, MONGOC_UPDATE_NONE, query1, update1, NULL, &error))
         {
            fprintf(stderr, "%s\n", error.message);
         }

         if (query1)
            bson_destroy(query1);
         if (update1)
            bson_destroy(update1);
      }

      if (str)
         bson_free(str);
      bson_destroy((bson_t *)doc);
      mongoc_cursor_destroy(cursor);
      return 1;
   }
   else
   {

      //if get the result
      //INSERT INTO documents (title, body) VALUES (?, ?);
      bson_t *doc;
      doc = bson_new();

      BSON_APPEND_UTF8(doc, "key", key);
      BSON_APPEND_UTF8(doc, "value", value);

      // 将bson文档插入到集合
      if (!mongoc_collection_insert(env->settings, MONGOC_INSERT_NONE, doc, NULL, &error))
      {
         fprintf(stderr, "%s\n", error.message);
      }
      if (str)
         bson_free(str);
      if (doc)
         bson_destroy(doc);
      if (query)
         bson_destroy(query);
      if (cursor)
         mongoc_cursor_destroy(cursor);
      return 1;
   }
}

/**
 * 从tokens表中获取指定词元的编号
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] str 词元（UTF-8）
 * @param[in] str_size 词元的字节数
 * @param[in] insert 当找不到指定词元时，是否要将该词元添加到表中
 * @param[out] docs_count 出现过指定词元的文档数
 */

int db_get_token_id2(client_env *env,
                     char *token, int insert,
                     int *docs_count)
{

   bson_t *doc;
   bson_t *insert_doc;
   bson_error_t error;
   doc = bson_new();
   insert_doc = bson_new();
   bson_t *query;
   mongoc_cursor_t *cursor;
   char *str;
   query = bson_new();
   BSON_APPEND_UTF8(query, "token", token);

   if (insert)
   {
      //if get the result
      //INSERT INTO documents (title, body) VALUES (?, ?);
      cursor = mongoc_collection_find_with_opts(env->tokens, query, NULL, NULL);
      if (!mongoc_cursor_next(cursor, (const bson_t **)&doc))
      {
         int64_t _id = get_id_for_token(env);
         BSON_APPEND_INT64(insert_doc, "_id", _id);
         BSON_APPEND_UTF8(insert_doc, "token", token);
         BSON_APPEND_INT64(insert_doc, "docs_count", 0);
         BSON_APPEND_UTF8(insert_doc, "postings", "");

         // 将bson文档插入到集合
         if (!mongoc_collection_insert(env->tokens, MONGOC_INSERT_NONE, insert_doc, NULL, &error))
         {
            fprintf(stderr, "%s\n", error.message);
         }
      }
   }

   cursor = mongoc_collection_find_with_opts(env->tokens, query, NULL, NULL);
   if (mongoc_cursor_next(cursor, (const bson_t **)&doc))
   {
      str = bson_as_canonical_extended_json(doc, NULL);
      cJSON *json = cJSON_Parse(str);
      cJSON *_id = NULL;
      cJSON *doc_count = NULL;
      _id = cJSON_GetObjectItem(json, "_id");
      doc_count = cJSON_GetObjectItem(json, "docs_count");
      if (NULL == _id || NULL == doc_count)
      {
         printf("the token and _id == NULL\n");
      }
      else
      {
         printf("the value of doc_count is %d\n", doc_count->valueint);
         if (docs_count)
         {
            *docs_count = doc_count->valueint;
         }

         if (doc)
            bson_destroy(doc);
         if (insert_doc)
            bson_destroy(insert_doc);
         if (query)
            bson_destroy(query);
         return _id->valueint;
      }
   }
   else
   {

      if (docs_count)
      {
         *docs_count = 0;
      }
      if (insert_doc)
         bson_destroy(insert_doc);
      if (doc)
         bson_destroy(doc);
      if (query)
         bson_destroy(query);
      return 0;
   }
}

int db_get_token2(client_env *env,
                  int token_id,
                  char **token)
{
   bson_t *query;
   char *str;
   bson_t *doc;
   mongoc_cursor_t *cursor;

   query = bson_new();
   BSON_APPEND_INT64(query, "_id", token_id);
   cursor = mongoc_collection_find_with_opts(env->tokens, query, NULL, NULL);
   if (mongoc_cursor_next(cursor, (const bson_t **)&doc))
   {

      str = bson_as_canonical_extended_json(doc, NULL);
      cJSON *json = cJSON_Parse(str);

      cJSON *token_str = NULL;

      token_str = cJSON_GetObjectItem(json, "token");
      if (NULL == token)
      {
         printf("the token  == NULL\n");
      }
      else
      {
         printf("the value of toekn_str is %s\n", token_str->valuestring);
         *token = token_str->valuestring;
      }
   }

   if (query)
      bson_destroy(query);
   if (doc)
      bson_destroy(doc);
   if (cursor)
      mongoc_cursor_destroy(cursor);
   if (str)
      bson_free(str);
   return 1;
}

/**
 * 根据词元编号从数据库中获取倒排列表
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] token_id 词元编号
 * @param[out] docs_count 倒排列表中的文档数
 * @param[out] postings 获取到的倒排列表
 * @param[out] postings_size 获取到的倒排列表的字节数
 */
int db_get_postings2(client_env *env, int token_id,
                     int *docs_count, void **postings)
{

   bson_t *query;
   char *str;
   bson_t *doc;
   mongoc_cursor_t *cursor;

   query = bson_new();
   BSON_APPEND_INT64(query, "_id", token_id);
   cursor = mongoc_collection_find_with_opts(env->tokens, query, NULL, NULL);
   if (mongoc_cursor_next(cursor, (const bson_t **)&doc))
   {
      str = bson_as_canonical_extended_json(doc, NULL);
      cJSON *json = cJSON_Parse(str);

      cJSON *postings_str = NULL;
      cJSON *docs_count_str = NULL;

      docs_count_str = cJSON_GetObjectItem(json, "docs_count");
      postings_str = cJSON_GetObjectItem(json, "postings");
      if (NULL == docs_count_str || NULL == postings_str)
      {
         printf("the docs_count_str or postings_str  == NULL\n");
      }
      else
      {
         printf("the value of toekn_str is %s\n", postings_str->valuestring);
         if (docs_count)
         {
            *docs_count = docs_count_str->valueint;
         }

         if (postings)
         {
            *postings = (void *)postings_str->valuestring;
         }
      }
      if (query)
         bson_destroy(query);
      if (doc)
         bson_destroy(doc);
      if (cursor)
         mongoc_cursor_destroy(cursor);
      if (str)
         bson_free(str);
   }
   else
   {

      if (docs_count)
      {
         *docs_count = 0;
      }

      if (postings)
      {
         *postings = NULL;
      }
      if (query)
         bson_destroy(query);
      if (doc)
         bson_destroy(doc);
      if (cursor)
         mongoc_cursor_destroy(cursor);
      if (str)
         bson_free(str);
   }
}

/**
 * 将倒排列表存储到数据库中
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] token_id 词元编号
 * @param[in] docs_count 倒排列表中的文档数
 * @param[in] postings 待存储的倒排列表
 * @param[in] postings_size 倒排列表的字节数
 */
int db_update_postings2(client_env *env, int token_id, int docs_count,
                       void *postings)
{
   bson_t *query = bson_new();
   bson_t *update = bson_new();
   bson_error_t error;
   BSON_APPEND_INT64(query, "_id", token_id);

 
   BSON_APPEND_UTF8(update, "postings", postings);
   BSON_APPEND_INT64(update, "docs_count", docs_count);
   BSON_APPEND_INT64(update, "_id", token_id);
   // 执行update操作。这个操作将使用update的内容去替换之前插入到数据库中的doc的内容
   if (!mongoc_collection_update(env->tokens, MONGOC_UPDATE_NONE, query, update, NULL, &error))
   {
      fprintf(stderr, "%s\n", error.message);
   }

   if (query)
      bson_destroy(query);
   if (update)
      bson_destroy(update);

   return 0;
}
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
