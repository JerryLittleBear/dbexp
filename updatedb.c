#include"updatedb.h"
#include<stdio.h>
#include<mysql/mysql.h>
#include<string.h>

int updatedb()
{
    MYSQL mysql;
    int res;
    char tempStr[STRLEN];
    
    mysql_init(&mysql);
    
    if(mysql_real_connect(&mysql, "localhost", "root", "daijiangxiong1", "",0,NULL,CLIENT_FOUND_ROWS))//to connect to the dbms,but not select db to use
    {
        printf("Connection success!\n");
    
    }
    else
    {
        fprintf(stderr, "Connection failed\n");
        
        
        if(mysql_errno(&mysql))
        {
             fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        }
        
    }
    
    if(!mysql_select_db(&mysql, "travel_system"))//select db to use
    {
        printf("select db success\n");
    }
    else
    {
        fprintf(stderr, "Please initialize the db, you can use \"initdb\" command\n");
        return -1;
    }
    
    printf("Please input an SQL sentence: -->");
    fgets(tempStr, STRLEN, stdin);//should not use scanf
    //getchar();
    //puts(tempStr);
    mysql_real_query(&mysql, tempStr, strlen(tempStr));
    //getchar();
    if(mysql_errno(&mysql))
    {
        fprintf(stderr, "error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
    }
    return 0;
}
