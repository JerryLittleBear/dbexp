#include"menu.h"
#include"initdb.h"
#include"reserve.h"
#include"updatedb.h"
#include"showtable.h"
#include"range_query.h"
#include"travel_route.h"

#include<string.h>
#include<stdio.h>
#include<unistd.h>


int main(int argc, char** argv)
{
    //initdb();
    //char s[50][50];
    //MenuConfig("help", "This is help cmd", Help);
    MenuConfig("quit", "Quit the program", Quit);
    MenuConfig("initdb", "Initialize db with original datas", initdb);
    MenuConfig("updatedb", "Using SQL sentence to update data", updatedb);
    MenuConfig("reserve", "Make an reservation ", reserve);
    MenuConfig("show_table", "Show a table you want to see ", show_table);
    MenuConfig("range_query", "Query data with a certain range", range_query);
    MenuConfig("print_bpt", "Print the bptree constructed by the data we selected", print_bpt);
    MenuConfig("travel_route", "Print the travel route of one customer", travel_route);
    Help();
    ExecuteMenu();
    return 0;
}
