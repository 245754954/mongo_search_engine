<<<<<<< HEAD
// #ifndef __MONGODATABASE_H__
// #define __MONGODATABASE_H__

// #include "wiser.h"

// int  init_database2( wiser_env *env,const char *dbpath);
// void  fin_database2(  wiser_env *env);
// //search  the corresponding article id corresponding article tittle
// int db_get_document_id2(const  wiser_env *env,const char *title,int64_t *_id);


// //根据指定的文档编号获取文档标题
// int  db_get_document_title2(const wiser_env *env, int64_t document_id,
//                            char *title);

// /**
//  * 将文档添加到documents表中
//  * @param[in] env 存储着应用程序运行环境的结构体
//  * @param[in] title 文档标题
//  * @param[in] title_size 文档标题的字节数
//  * @param[in] body 文档正文
//  * @param[in] body_size 文档正文的字节数
//  */


// int db_add_document2( wiser_env *env,
//                      const char *title,
//                    const char *body);





// //generate primary key for documents collections
// int64_t get_id_for_document(const  wiser_env* env);


// //generate primary key for tokens collections
// int64_t get_id_for_token(const  wiser_env* env);
// /**
//  * 获取已添加到数据库中的文档数
//  * @param[in] env 存储着应用程序运行环境的结构体
//  */
// int db_get_document_count2(const  wiser_env *env);

// /**
//  * 从数据库中获取配置信息
//  * @param[in] env 存储着应用程序运行环境的结构体
//  * @param[in] key 配置项的名称
//  * @param[in] key_size 配置项名称的字节数
//  * @param[out] value 配置项的取值
//  * @param[out] value_size 配置项取值的字节数
//  */
// int db_get_settings2( wiser_env *env,  char *key, char *value );


// /**
//  * 更新存储在数据库中的配置信息
//  * @param[in] env 存储着应用程序运行环境的结构体
//  * @param[in] key 配置项的名称
//  * @param[in] key_size 配置项名称的字节数
//  * @param[in] value 配置项的取值
//  * @param[in] value_size 配置项取值的字节数
//  */
// int db_replace_settings2( wiser_env *env, char *key,char *value);


// /**
//  * 从tokens表中获取指定词元的编号
//  * @param[in] env 存储着应用程序运行环境的结构体
//  * @param[in] str 词元（UTF-8）
//  * @param[in] str_size 词元的字节数
//  * @param[in] insert 当找不到指定词元时，是否要将该词元添加到表中
//  * @param[out] docs_count 出现过指定词元的文档数
//  */

// int db_get_token_id2( const  wiser_env *env,
//                      const char *str,  int insert,
//                     int *docs_count);


// /**
//  * 根据词元编号从tokens表获取词元
//  * @param[in] env 存储着应用程序运行环境的结构体
//  * @param[in] token_id 词元编号
//  * @param[out] token 词元（UTF-8）
//  * @param[out] token_size 词元的字节数
//  */
// int db_get_token2(const  wiser_env *env,
//                   int token_id,
//                   char ** token);
// /**
//  * 根据词元编号从数据库中获取倒排列表
//  * @param[in] env 存储着应用程序运行环境的结构体
//  * @param[in] token_id 词元编号
//  * @param[out] docs_count 倒排列表中的文档数
//  * @param[out] postings 获取到的倒排列表
//  * @param[out] postings_size 获取到的倒排列表的字节数
//  */

// int db_get_postings2(const wiser_env *env, int token_id,
//                     int *docs_count, void **postings,int *posting_size);



// /**
//  * 将倒排列表存储到数据库中
//  * @param[in] env 存储着应用程序运行环境的结构体
//  * @param[in] token_id 词元编号
//  * @param[in] docs_count 倒排列表中的文档数
//  * @param[in] postings 待存储的倒排列表
//  * @param[in] postings_size 倒排列表的字节数
//  */
// int db_update_postings2(const wiser_env *env, int token_id, int docs_count,
//                        void *postings, int postings_size);
// #endif
=======
#ifndef __MONGODATABASE_H__
#define __MONGODATABASE_H__

#include "myclient.h"

int  init_database2(client_env *env,const char *dbpath);
int  fin_database2(client_env *env);
//search  the corresponding article id corresponding article tittle
int db_get_document_id2( client_env *env,char *title,int64_t *_id);


//根据指定的文档编号获取文档标题
void  db_get_document_title2(const client_env *env, int64_t document_id,
                           char *title);

/**
 * 将文档添加到documents表中
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] title 文档标题
 * @param[in] title_size 文档标题的字节数
 * @param[in] body 文档正文
 * @param[in] body_size 文档正文的字节数
 */


int db_add_document2( client_env *env,
                     char *title,
                    char *body);





//generate primary key for documents collections
int64_t get_id_for_document(client_env* env);


//generate primary key for tokens collections
int64_t get_id_for_token(client_env* env);
/**
 * 获取已添加到数据库中的文档数
 * @param[in] env 存储着应用程序运行环境的结构体
 */
int db_get_document_count2(client_env *env);

/**
 * 从数据库中获取配置信息
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] key 配置项的名称
 * @param[in] key_size 配置项名称的字节数
 * @param[out] value 配置项的取值
 * @param[out] value_size 配置项取值的字节数
 */
int db_get_settings2(client_env *env,  char *key, char *value );


/**
 * 更新存储在数据库中的配置信息
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] key 配置项的名称
 * @param[in] key_size 配置项名称的字节数
 * @param[in] value 配置项的取值
 * @param[in] value_size 配置项取值的字节数
 */
int db_replace_settings2(client_env *env, char *key,char *value);


/**
 * 从tokens表中获取指定词元的编号
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] str 词元（UTF-8）
 * @param[in] str_size 词元的字节数
 * @param[in] insert 当找不到指定词元时，是否要将该词元添加到表中
 * @param[out] docs_count 出现过指定词元的文档数
 */

int db_get_token_id2(client_env *env,
                     char *str,  int insert,
                    int *docs_count);


/**
 * 根据词元编号从tokens表获取词元
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] token_id 词元编号
 * @param[out] token 词元（UTF-8）
 * @param[out] token_size 词元的字节数
 */
int db_get_token2(client_env *env,
                  int token_id,
                  char ** token);
/**
 * 根据词元编号从数据库中获取倒排列表
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] token_id 词元编号
 * @param[out] docs_count 倒排列表中的文档数
 * @param[out] postings 获取到的倒排列表
 * @param[out] postings_size 获取到的倒排列表的字节数
 */

int db_get_postings2(client_env *env, int token_id,
                    int *docs_count, void **postings);



/**
 * 将倒排列表存储到数据库中
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] token_id 词元编号
 * @param[in] docs_count 倒排列表中的文档数
 * @param[in] postings 待存储的倒排列表
 * @param[in] postings_size 倒排列表的字节数
 */
int db_update_postings2(client_env *env, int token_id, int docs_count,
                       void *postings);
#endif
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
