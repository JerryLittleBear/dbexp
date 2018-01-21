#include<stdio.h>
#include<string.h>
#include"showtable.h"
#include<mysql/mysql.h>

int show_table()
{
    MYSQL mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int num_of_col;
    
    char query[128]="SELECT * FROM ", table[128];

    
    while(1)//to get the correct SQL sentence
    {
        printf("Input the table name you want to show?\n----FLIGHTS\n----HOTELS\n----CARS\n----CUSTOMERS\n----RESERVATIONS\nPlease input table name --> ");
        fgets(table, sizeof(table), stdin);
        if(strlen(table)!=sizeof(table)-1)
            table[strlen(table)-1] = '\0';//set last position of the char array from '\r' to '\0',
        puts(table);
        
        if(!strcmp(table, "FLIGHTS") || !strcmp(table, "CARS") || !strcmp(table, "HOTELS") || !strcmp(table, "CUSTOMERS") || !strcmp(table, "RESERVATIONS"))
        {
            strcat(query, table);
            //puts(query);
            break;
        }
        else
        {
            fprintf(stderr, "Please reinput the right table names --> ");
        }  
    }


    //start to operate DB using query sentence we generate above
    mysql_init(&mysql);
    if(mysql_real_connect(&mysql, "localhost", "root", "daijiangxiong1", "", 0, NULL, 0))
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
    //start to query
    if(!mysql_real_query(&mysql, query, strlen(query)))
    {
        printf("query table successfully!\n");
    }
    else
    {
        fprintf(stderr, "query failed\n");        
        if(mysql_errno(&mysql))
        {
             fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        }
        return -1;
    }
    //using variable result to store the returned result we queried just above
    result = mysql_store_result(&mysql);
    //mysql_fetch_row function is to fetch the next line of the result
    while(row=mysql_fetch_row(result))
    {
        //mysql_num_fields function is to return the number of the column of each row of the result
        for(num_of_col=0; num_of_col < mysql_num_fields(result); num_of_col++)
        {
            fprintf(stdout, "%s\t", row[num_of_col]);
        }
        printf("\n");
    }
    mysql_free_result(result);
    mysql_close(&mysql);
    return 0;
}
