#include"menu.h"
#include"initdb.h"
#include"range_query.h"

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
    MenuConfig("range_query", "Query data with a certain range", range_query);
    MenuConfig("print_bpt", "Print the bptree constructed by the data we selected", print_bpt);
    Help();
    ExecuteMenu();
    return 0;
}
