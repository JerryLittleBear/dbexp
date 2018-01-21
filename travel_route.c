#include<mysql/mysql.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>     

#include"travel_route.h"

int travel_route()
{
    MYSQL mysql;
    MYSQL_RES *mysql_res;
    MYSQL_ROW mysql_row;
    int this_row = 0, num_row = 0, num_col = 0;
    char query[128]="select FromCity, ArivCity from RESERVATIONS where custName=\'";
    char customer[50];

    //get the customer's name to build the SQL sentence
    puts("Please intput the customer's name ---> ");
    fgets(customer, sizeof(customer), stdin);
    customer[strlen(customer)-1] = '\0';
    strcat(query, customer);
    strcat(query, "\' order by resvKey asc");
    
    
    //init&conncet&select db 
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
        printf("query successfully!\n");
    }
    else
    {
        fprintf(stderr, "query failed!\n");
        if(mysql_errno(&mysql))
        {
            fprintf(stderr, "error NO.%d : %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        }
    }
    
    putchar('\n');
    mysql_res = mysql_store_result(&mysql);
    num_row = mysql_num_rows(mysql_res);
    while(mysql_row = mysql_fetch_row(mysql_res))
    {
        this_row++;
        fprintf(stdout, " %s---->", mysql_row[0]);
        if(this_row == num_row)
        {
            fprintf(stdout, " %s\n\n", mysql_row[1]);
        }
    }
    return 0;
}
