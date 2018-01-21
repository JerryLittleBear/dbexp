#include<stdio.h>
#include<mysql/mysql.h>
#include<string.h>
int main()
{
    MYSQL mysql;
    int res;
    mysql_init(&mysql);
    char *query="CREATE TABLE ";
    //char *query="1111";
    //char query1[]="1111";
    //printf("%lu\n%lu\n", sizeof(query), sizeof(query1));

    if(mysql_real_connect(&mysql, "localhost", "root", "daijiangxiong1", "", 0, NULL,CLIENT_FOUND_ROWS))//if success return the value of &mysql,else return 0
    {
        printf("Connection success!\n");
        /*res = mysql_real_query(&mysql, "CREATE DATABASE test", strlen("CREATE DATABASE test"));//if success return 0,else return sql sentence
        if(res)
        {
            printf("affected %lu rows\n", (long unsigned int)mysql_affected_rows(&mysql));
        }
        else
        {
            fprintf(stderr, "affection error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        }*/
    }
    else
    {
        fprintf(stderr, "Connection failed\n");
        
        
        if(mysql_errno(&mysql))
        {
             fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        } 
    }
    mysql_select_db(&mysql, "jerry");
    printf("1111\n");
    mysql_real_query(&mysql, query, strlen(query));
    printf("2222\n");
    mysql_query(&mysql, "SELECT * FROM mybooks");
    printf("2222\n");
    mysql_close(&mysql);
    //printf("%s\n", mysql_get_client_info());
    return 0;
}
