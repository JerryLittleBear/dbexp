#include<mysql/mysql.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>     
 
#include"bptree.h"

int print_bpt()
{

    
    MYSQL mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[128];
    int nonsense[100][100];
    char table[16];
    char attribute[16];
    int r1, r2;
    char r1_tmp[16], r2_tmp[16];
    int tmp_num;
    node * root;

    //to get the correct SQL sentence
    while(1)
    {
        printf("\nWhich table do you want to query about the range?\n----FLIGHTS\n----HOTELS\n----CARS\n----CUSTOMERS\n----RESERVATIONS\nPlease input table name --> ");
        fgets(table, sizeof(table), stdin);
        if(strlen(table)!=sizeof(table)-1)
            table[strlen(table)-1] = '\0';//set last position of the char array from '\r' to '\0',
        puts(table);
        
        if(!strcmp(table, "FLIGHTS") || !strcmp(table, "CARS") || !strcmp(table, "HOTELS") || !strcmp(table, "CUSTOMERS") || !strcmp(table, "RESERVATIONS"))
        {
            puts("\n<  Following arrtibutes you can select as key  >\n");
            if(!strcmp(table, "FLIGHTS"))
            {
                puts("<flightNum>  <price>  <numSeats>  <numAvail>  <FromCity>  <ArivCity>\n");
                
            }
            else if(!strcmp(table, "CARS"))
            {
                puts("<type>  <location>  <price>  <numCars>  <numAvail>\n");
            }
            else if(!strcmp(table, "HOTELS"))
            {
                puts("<name>  <location>  <price>  <numRooms>  <numAvail>\n");
            }
            else if(!strcmp(table, "CUSTOMERS"))
            {
                puts("<custName>\n");
            }
            else if(!strcmp(table, "RESERVATIONS"))
            {
                puts("<custName>  <resvType>  <resvKey>\n");
            }
            
            fgets(attribute, sizeof(attribute), stdin);
            if(strlen(attribute)!=sizeof(attribute)-1)
                attribute[strlen(attribute)-1] = '\0';
            puts("\n<  Input 2 integers as upper and lower limits, a SPACE between  >\n");
            scanf("%d%d", &r1, &r2);
            getchar();
            sprintf(r1_tmp, "%d", r1);
            sprintf(r2_tmp, "%d", r2);
            sprintf(query, "SELECT "); 
            strcat(query, attribute);
            strcat(query, " FROM ");           
            strcat(query, table);
            strcat(query, " WHERE ");
            strcat(query, attribute);
            strcat(query, " > ");
            strcat(query, r1_tmp);
            strcat(query, " AND ");
            strcat(query, attribute);
            strcat(query, " < ");
            strcat(query, r2_tmp);
            
            //puts(query);
            break;
        }
        else
        {
            fprintf(stderr, "Please reinput the right table names --> ");
            return -1;
        }  
    }


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

    
    //output the B+ tree of the selected attribute
    result = mysql_store_result(&mysql); 
    int num_row = 0;
    while(row=mysql_fetch_row(result))
    {
        num_row++;
        tmp_num=atoi(row[0]);
        //printf("%d\n", tmp_num);
        root = insert(root, tmp_num, tmp_num);
    }    
    //fprintf(stdout, "\n%d tuples selected!\n", num_row);
    puts("<--------------------BPTree------------------->");
    print_tree(root);
    puts("<--------------------BPTree------------------->");
    root = destroy_tree(root);
    mysql_free_result(result);
    mysql_close(&mysql);
    return 0;
}
    
    
    
int range_query()
{   
    MYSQL mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[128];
    char table[16];
    char attribute[16];
    int r1, r2;
    char r1_tmp[16], r2_tmp[16];
    int tmp_num;
    node * root;

    //to get the correct SQL sentence
    while(1)
    {
        printf("\nWhich table do you want to query about the range?\n----FLIGHTS\n----HOTELS\n----CARS\n----CUSTOMERS\n----RESERVATIONS\nPlease input table name --> ");
        fgets(table, sizeof(table), stdin);
        if(strlen(table)!=sizeof(table)-1)
            table[strlen(table)-1] = '\0';//set last position of the char array from '\r' to '\0',
        puts(table);
        
        if(!strcmp(table, "FLIGHTS") || !strcmp(table, "CARS") || !strcmp(table, "HOTELS") || !strcmp(table, "CUSTOMERS") || !strcmp(table, "RESERVATIONS"))
        {
            puts("\n<  Following arrtibutes you can select as key  >\n");
            if(!strcmp(table, "FLIGHTS"))
            {
                puts("<flightNum>  <price>  <numSeats>  <numAvail>  <FromCity>  <ArivCity>\n");
                
            }
            else if(!strcmp(table, "CARS"))
            {
                puts("<type>  <location>  <price>  <numCars>  <numAvail>\n");
            }
            else if(!strcmp(table, "HOTELS"))
            {
                puts("<name>  <location>  <price>  <numRooms>  <numAvail>\n");
            }
            else if(!strcmp(table, "CUSTOMERS"))
            {
                puts("<custName>\n");
            }
            else if(!strcmp(table, "RESERVATIONS"))
            {
                puts("<custName>  <resvType>  <resvKey>\n");
            }
            
            fgets(attribute, sizeof(attribute), stdin);
            if(strlen(attribute)!=sizeof(attribute)-1)
                attribute[strlen(attribute)-1] = '\0';
            puts("\n<  Input 2 integers as upper and lower limits, a SPACE between  >\n");
            scanf("%d%d", &r1, &r2);
            getchar();
            sprintf(r1_tmp, "%d", r1);
            sprintf(r2_tmp, "%d", r2);
            sprintf(query, "SELECT * FROM ");            
            strcat(query, table);
            strcat(query, " WHERE ");
            strcat(query, attribute);
            strcat(query, " > ");
            strcat(query, r1_tmp);
            strcat(query, " AND ");
            strcat(query, attribute);
            strcat(query, " < ");
            strcat(query, r2_tmp);
            
            //puts(query);
            break;
        }
        else
        {
            fprintf(stderr, "Please reinput the right table names --> ");
        }  
    }


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
    //output all selected tuples
    result = mysql_store_result(&mysql); 
    
    
    //output the B+ tree of the selected attribute
    int num_row = 0;
    while(row=mysql_fetch_row(result))
    {
        num_row++;
        for(int columns=0; columns < mysql_num_fields(result); columns++)
        {
            fprintf(stdout, "%s\t", row[columns]);
        }
        putchar('\n');
    }    
    fprintf(stdout, "\n%d tuples selected!\n", num_row);
    mysql_free_result(result);
    mysql_close(&mysql);
    return 0;
}
      
