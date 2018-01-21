#include"reserve.h"
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<mysql/mysql.h>

int reserve()
{
    char custName[128], location[128], fromCity[128], arivCity[128], resvKey[128], sql1[256]="INSERT INTO RESERVATIONS VALUES(", *dot=",";
    int resvType;
    MYSQL mysql;
    MYSQL_RES *mysql_res;
    MYSQL_ROW mysql_row;
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
    
    puts("Need 3 things to reserve: yourname, reservaion type, reservation key\n");
    
    
    printf("input your name, press ENTER to confirm  -->");
    
    fgets(custName, sizeof(custName), stdin);
    if(strlen(custName)!=sizeof(custName)-1)
        custName[strlen(custName)-1] = '\0';//set last position of the char array from '\r' to '\0',
        
    while(1)
    {
        printf("input reservation type: \n----input 1 is flight\n----input 2 is hotel\n----input 3 is car\npress ENTER to confirm  -->");
        scanf("%d", &resvType);
        getchar();
    
        if(resvType==1 || resvType==2 || resvType==3)
        {
            break;
        }
	    else
	    {
	        fprintf(stderr, "Please input the right number:1 or 2 or 3 --> ");
	    }
    }
    /*
    printf("input reservation key, press ENTER to confirm  -->");
    fgets(resvKey, sizeof(resvKey), stdin);
    if(strlen(resvKey)!=sizeof(resvKey)-1)
        resvKey[strlen(resvKey)-1] = '\0';   //change last position of string from '\r' to '\0' 
    */


    //get the max of resvKey(primary key), add 1 to it
    mysql_query(&mysql, "SELECT MAX(resvKey) FROM RESERVATIONS");
    mysql_res = mysql_store_result(&mysql);
    mysql_row = mysql_fetch_row(mysql_res);
    int maxKey = atoi(mysql_row[0]);
    char maxKey_str[30];
    //printf("%d\n", maxKey);
    sprintf(maxKey_str, "%d", maxKey+1);
//insert into RESERVATIONS VALUES('dai', 1, 9, 'location', 'from', 'arive')
    strcat(sql1, "'");
    strcat(sql1, custName);
    strcat(sql1, "'");
    strcat(sql1, ",");
    switch(resvType)
    {
        case 1:strcat(sql1, " 1 ");
                strcat(sql1, " , ");
                strcat(sql1, maxKey_str);
                strcat(sql1, ",\'\',\'");
                printf("input your FromCity, press ENTER to confirm  -->");//get fromCity string
                fgets(fromCity, sizeof(fromCity), stdin);
                fromCity[strlen(fromCity)-1] = '\0';
                strcat(sql1, fromCity);
                strcat(sql1, "\',\'");
                printf("input your AriveCity, press ENTER to confirm  -->");//get arivCity string
                fgets(arivCity, sizeof(arivCity), stdin);
                arivCity[strlen(arivCity)-1] = '\0';
                strcat(sql1, arivCity);
                strcat(sql1, "\')");
                break;
        case 2:strcat(sql1, "2");
                strcat(sql1, ",");
                strcat(sql1, maxKey_str);
                strcat(sql1, ",\'");
                printf("input your location, press ENTER to confirm  -->");//get location string
                fgets(location, sizeof(location), stdin);
                location[strlen(location)-1] = '\0';
                strcat(sql1, location);
                strcat(sql1, "\',\'\',\'\')");
                break;
        case 3:strcat(sql1, "3");
                strcat(sql1, ",");
                strcat(sql1, maxKey_str);
                strcat(sql1, ",\'");
                printf("input your location, press ENTER to confirm  -->");//get location string
                fgets(location, sizeof(location), stdin);
                location[strlen(location)-1] = '\0';
                strcat(sql1, location);
                strcat(sql1, "\',\'\',\'\')");
                break;      
    }


    puts(sql1);
    if(!mysql_real_query(&mysql, sql1, strlen(sql1)))
    {
        printf("reserve successfully!\n");
    }
    else
    {
        fprintf(stderr, "reservation failed\n");        
        if(mysql_errno(&mysql))
        {
             fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        }
        return -1;
    }
    
    return 0;
}
