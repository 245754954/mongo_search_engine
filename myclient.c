<<<<<<< HEAD
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
=======

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

#include "wiser.h"
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
#include "myclient.h"
#include "util.h"
#include "token.h"
#include "search.h"
#include "postings.h"
<<<<<<< HEAD
#include "mongodatabase.h"
#include "wikiload.h"
=======
#include "database.h"
#include "wikiload.h"
#include "mongodatabase.h"
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f

/* 判断从地址t开始的、长度为l的二进制序列是否与字符串c一致 */
#define MEMSTRCMP(t, l, c) (l == (sizeof(c) - 1) && !memcmp(t, c, l))
/**
 * 将文档添加到数据库中，建立倒排索引
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] title 文档标题，为NULL时将会清空缓冲区
 * @param[in] body 文档正文
 */
<<<<<<< HEAD
static void
add_document(wiser_env *env, const char *title, const char *body)
=======
void add_document1(wiser_env *env, const char *title, const char *body)
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
{
  if (title && body)
  {
    UTF32Char *body32;
<<<<<<< HEAD
    int body32_len;
    int64_t document_id;
=======
    int body32_len, document_id;
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
    unsigned int title_size, body_size;

    title_size = strlen(title);
    body_size = strlen(body);
<<<<<<< HEAD
    if (NULL != title && NULL != body)
    {
      /* 将文档存储到数据库中并获取该文档对应的文档编号 */
      document_id =  db_add_document2(env, title, body);
     // db_get_document_id2(env, title, &document_id);

      /* 转换文档正文的字符编码 */
      if (!utf8toutf32(body, body_size, &body32, &body32_len))
      {
        /* 为文档创建倒排列表 */
        text_to_postings_lists(env, document_id, body32, body32_len,
                               env->token_len, &env->ii_buffer);
        env->ii_buffer_count++;
        free(body32);
      }
      env->indexed_count++;
      print_error("count:%d title: %s", env->indexed_count, title);
    }
  }
=======

    /* 将文档存储到数据库中并获取该文档对应的文档编号 */
    db_add_document(env, title, title_size, body, body_size);
    document_id = db_get_document_id(env, title, title_size);

    /* 转换文档正文的字符编码 */
    if (!utf8toutf32(body, body_size, &body32, &body32_len))
    {
      /* 为文档创建倒排列表 */
      text_to_postings_lists(env, document_id, body32, body32_len, env->token_len, &env->ii_buffer);
      env->ii_buffer_count++;
      free(body32);
    }
    env->indexed_count++;
    print_error("count:%d title: %s", env->indexed_count, title);
  }

>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
  /* 存储在缓冲区中的文档数量达到了指定的阈值时，更新存储器上的倒排索引 */
  if (env->ii_buffer &&
      (env->ii_buffer_count > env->ii_buffer_update_threshold || !title))
  {
    inverted_index_hash *p;

    print_time_diff();

    /* 更新所有词元对应的倒排项 */
<<<<<<< HEAD
    for (p = env->ii_buffer; p != NULL; p = (inverted_index_hash *)p->hh.next)
    {

=======
    for (p = env->ii_buffer; p != NULL; p = p->hh.next)
    {
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
      update_postings(env, p);
    }
    free_inverted_index(env->ii_buffer);
    print_error("index flushed.");
    env->ii_buffer = NULL;
    env->ii_buffer_count = 0;

    print_time_diff();
  }
}

/**
 * 设定应用程序的运行环境
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] ii_buffer_update_threshold 清空（Flush）倒排索引缓冲区的阈值
 * @param[in] enable_phrase_search 是否启用短语检索
 * @param[in] db_path 数据库的路径
 * @return 错误代码
 * @retval 0 成功
 */
<<<<<<< HEAD
static int
init_env(wiser_env *env,
         int ii_buffer_update_threshold, int enable_phrase_search,
         const char *db_path)
{
  int rc;
  memset(env, 0, sizeof(wiser_env));
  rc = init_database2(env, db_path);
=======
int init_env1(wiser_env *env,
              int ii_buffer_update_threshold, int enable_phrase_search,
              const char *db_path)
{
  int rc;
  memset(env, 0, sizeof(wiser_env));
  rc = init_database(env, db_path);
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
  if (!rc)
  {
    env->token_len = N_GRAM;
    env->ii_buffer_update_threshold = ii_buffer_update_threshold;
    env->enable_phrase_search = enable_phrase_search;
  }
  return rc;
}

<<<<<<< HEAD
=======

int init_env2(client_env *env, int ii_buffer_update_threshold, int enable_phrase_search, const char *mongo_url)
{

  int rc;
  memset(env, 0, sizeof(env));
  rc = init_database2(env,mongo_url);
  if (!rc)
  {

    env->ii_buffer_update_threshold = ii_buffer_update_threshold;
    env->enable_phrase_search = enable_phrase_search;
    env->token_len = N_GRAM;
  }
  return rc;
}

>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
/**
 * 释放应用程序的运行环境
 * @param[in] env 存储着应用程序运行环境的结构体
 */
<<<<<<< HEAD
static void
fin_env(wiser_env *env)
{
  fin_database2(env);
}

=======
void fin_env1(wiser_env *env)
{
  fin_database(env);
}


void fin_env2(client_env *env){

  fin_database2(env);
}
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
/**
 * 进行全文检索
 * @param[in] env 存储着应用程序运行环境的结构体
 * @param[in] method 压缩倒排列表的方法
 * @param[in] method_size 压缩方法名称的字节数
 */
static void
<<<<<<< HEAD
parse_compress_method(wiser_env *env, const char *method,
                      int method_size)
=======
parse_compress_method1(wiser_env *env, const char *method,
                       int method_size)
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
{
  if (method && method_size < 0)
  {
    method_size = strlen(method);
  }
<<<<<<< HEAD

=======
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
  if (!method || !method_size || MEMSTRCMP(method, method_size, "golomb"))
  {
    env->compress = compress_golomb;
  }
  else if (MEMSTRCMP(method, method_size, "none"))
  {
    env->compress = compress_none;
  }
  else
  {
    print_error("invalid compress method(%.*s). use golomb instead.",
                method_size, method);
    env->compress = compress_golomb;
  }
  switch (env->compress)
  {
  case compress_none:
<<<<<<< HEAD
    db_replace_settings2(env, "compress_method", "none");

    break;
  case compress_golomb:
    db_replace_settings2(env, "compress_method", "golomb");
=======
    db_replace_settings(env,
                        "compress_method", sizeof("compress_method") - 1,
                        "none", sizeof("none") - 1);
    break;
  case compress_golomb:
    db_replace_settings(env,
                        "compress_method", sizeof("compress_method") - 1,
                        "golomb", sizeof("golomb") - 1);
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
    break;
  }
}

<<<<<<< HEAD
/**
 * 入口
 * @param[in] argc 参数的个数
 * @param[in] argv 参数指针的数组
 */





void query_reply(char *term,search_results1 *results)
{
  wiser_env env;
 
  int max_index_count = -1;                                            // 不限制参与索引构建的文档数量 /
  int ii_buffer_update_threshold = DEFAULT_II_BUFFER_UPDATE_THRESHOLD; //2048
  int enable_phrase_search = TRUE;
  const char *compress_method_str = NULL, *wikipedia_dump_file = NULL,
             *query = NULL;
 


  {
    int rc = init_env(&env, ii_buffer_update_threshold, enable_phrase_search,
                      "zfc.db");
  

      // 进行检索
      if (term)
      {
        int cm_size;
        char cm[512];
        char* method="compress_method";
        db_get_settings2(&env, method, cm);
        parse_compress_method(&env, cm,strlen(cm) );
        env.indexed_count = db_get_document_count2(&env);
       
        search(&env, query);
      }
      fin_env(&env);

      
    }
  return ;
  
}
=======
void query1(char *term)
{

  wiser_env env;
  extern int optind;
  int max_index_count = -1; // 不限制参与索引构建的文档数量 /
  int ii_buffer_update_threshold = DEFAULT_II_BUFFER_UPDATE_THRESHOLD;
  int enable_phrase_search = TRUE;
  const char *compress_method_str = NULL, *wikipedia_dump_file = NULL,
             *query = NULL;

  int rc = init_env1(&env, ii_buffer_update_threshold, enable_phrase_search, "zfc.db");
  if (!rc)
  {

    // 进行检索
    // print_time_diff();

    if (term)
    {
      int cm_size;
      const char *cm;
      db_get_settings(&env,
                      "compress_method", sizeof("compress_method") - 1,
                      &cm, &cm_size);
      parse_compress_method1(&env, cm, cm_size);
      env.indexed_count = db_get_document_count(&env);

      search(&env, term);
    }

    fin_env1(&env);
    // print_time_diff();
    return;
  }
  return;
}
/*

int main(int argc, char  *argv[])
{

 
  wiser_env env;
  extern int optind;
  int max_index_count = -1; // 不限制参与索引构建的文档数量 /
  int ii_buffer_update_threshold = DEFAULT_II_BUFFER_UPDATE_THRESHOLD;
  int enable_phrase_search = TRUE;
  const char *compress_method_str = NULL, *wikipedia_dump_file = NULL,
             *query = NULL;
  // 解析参数字符串 
  {
    int ch;
    extern int opterr;
    extern char *optarg;

    while ((ch = getopt(argc, argv, "c:x:q:m:t:s")) != -1)
    {
      switch (ch)
      {
      case 'c':
        compress_method_str = optarg;
        break;
      case 'x':
        wikipedia_dump_file = optarg;
        break;
      case 'q':
        query = optarg;
        break;
      case 'm':
        max_index_count = atoi(optarg);
        break;
      case 't':
        ii_buffer_update_threshold = atoi(optarg);
        break;
      case 's':
        enable_phrase_search = FALSE;
        break;
      }
    }
  }

  //使用解析过的参数运行wiser 
  if (argc != optind + 1)
  {
    printf(
        "usage: %s [options] db_file\n"
        "\n"
        "options:\n"
        "  -c compress_method            : compress method for postings list\n"
        "  -x wikipedia_dump_xml         : wikipedia dump xml path for indexing\n"
        "  -q search_query               : query for search\n"
        "  -m max_index_count            : max count for indexing document\n"
        "  -t ii_buffer_update_threshold : inverted index buffer merge threshold\n"
        "  -s                            : don't use tokens' positions for search\n"
        "\n"
        "compress_methods:\n"
        "  none   : don't compress.\n"
        "  golomb : Golomb-Rice coding(default).\n",
        argv[0]);
    return -1;
  }

  //在构建索引时，若指定的数据库已存在则报错 
  {
    struct stat st;
    if (wikipedia_dump_file && !stat(argv[optind], &st))
    {
      printf("%s is already exists.\n", argv[optind]);
      return -2;
    }
  }

  {
    int rc = init_env1(&env, ii_buffer_update_threshold, enable_phrase_search,
                      argv[optind]);
    if (!rc)
    {
      print_time_diff();

      // 加载Wikipedia的词条数据
      if (wikipedia_dump_file)
      {
        parse_compress_method1(&env, compress_method_str, -1);
        begin(&env);
        if (!load_wikipedia_dump(&env, wikipedia_dump_file, add_document1,
                                 max_index_count))
        {
          // 清空缓冲区 
          add_document1(&env, NULL, NULL);
          commit(&env);
        }
        else
        {
          rollback(&env);
        }
      }

      // 进行检索 
      if (query)
      {
        int cm_size;
        const char *cm;
        db_get_settings(&env,
                        "compress_method", sizeof("compress_method") - 1,
                        &cm, &cm_size);
        parse_compress_method1(&env, cm, cm_size);
        env.indexed_count = db_get_document_count(&env);
        search(&env, query);
      }
      fin_env1(&env);

      print_time_diff();
    }
    return rc;
  }
}
*/
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
