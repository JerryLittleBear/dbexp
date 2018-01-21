#include<mysql/mysql.h>
#include<stdio.h>
#include"initdb.h"

int initdb()
{
    MYSQL mysql;//create space for data struct of MYSQL
    
    int res;
    
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
	    fprintf(stderr, "db doesn't exist, now create it\n");
        mysql_query(&mysql, "CREATE DATABASE travel_system");//if db doesn't ,create it. wu can set(DEFAULT CHARSET=UTF8)
        printf("create db success\n");
        mysql_query(&mysql, "USE travel_system");
        printf("select db success\n");
        if(mysql_errno(&mysql))
        {
            fprintf(stderr, "mysql error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        }
    }

// create all tables
    mysql_query(&mysql, "CREATE TABLE FLIGHTS(flightNum VARCHAR(100) NOT NULL, price INT, numSeats INT, numAvail INT, FromCity VARCHAR(100), ArivCity VARCHAR(100), PRIMARY KEY (flightNum))");
    mysql_query(&mysql, "DELETE FROM FLIGHTS");
    mysql_query(&mysql, "LOAD DATA LOCAL INFILE \"/home/jerry/dbexp/dbfiles/FLIGHTS.txt\"INTO TABLE FLIGHTS");
    if(mysql_errno(&mysql))
        {
             fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        }
        
    mysql_query(&mysql, "CREATE TABLE HOTELS(name VARCHAR(100), location VARCHAR(100) NOT NULL, price INT, numRooms INT, numAvail INT, PRIMARY KEY (location))");
    mysql_query(&mysql, "DELETE FROM HOTELS");
    mysql_query(&mysql, "LOAD DATA LOCAL INFILE \"/home/jerry/dbexp/dbfiles/HOTELS.txt\"INTO TABLE HOTELS");
    if(mysql_errno(&mysql))
        {
             fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        }
        
    mysql_query(&mysql, "CREATE TABLE CARS(type VARCHAR(100), location VARCHAR(100) NOT NULL, price INT, numCars INT, numAvail INT, PRIMARY KEY(location))");
    mysql_query(&mysql, "DELETE FROM CARS");
    mysql_query(&mysql, "LOAD DATA LOCAL INFILE \"/home/jerry/dbexp/dbfiles/CARS.txt\"INTO TABLE CARS");
    if(mysql_errno(&mysql))
        {
             fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        }
        
    mysql_query(&mysql, "CREATE TABLE CUSTOMERS(custName VARCHAR(100) NOT NULL PRIMARY KEY)");
    mysql_query(&mysql, "DELETE FROM CUSTOMERS");
    mysql_query(&mysql, "LOAD DATA LOCAL INFILE \"/home/jerry/dbexp/dbfiles/CUSTOMERS.txt\"INTO TABLE CUSTOMERS");
    if(mysql_errno(&mysql))
        {
             fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        }
        
    mysql_query(&mysql, "CREATE TABLE RESERVATIONS(custName VARCHAR(100) NOT NULL, resvType INT, resvKey VARCHAR(100) NOT NULL, location VARCHAR(100), FromCity VARCHAR(100), ArivCity VARCHAR(100), PRIMARY KEY (resvKey), FOREIGN KEY (custName) REFERENCES CUSTOMERS(custName))");
    mysql_query(&mysql, "DELETE FROM RESERVATIONS");
    mysql_query(&mysql, "LOAD DATA LOCAL INFILE \"/home/jerry/dbexp/dbfiles/RESERVATIONS.txt\"INTO TABLE RESERVATIONS");
    if(mysql_errno(&mysql))
        {
             fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        }

    mysql_close(&mysql);
    return 0;
}
