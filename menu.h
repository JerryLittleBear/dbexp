#ifndef __MENU_H__
#define __MENU_H__

/*----------Add Command to Menu----------*/
int MenuConfig(char* cmd, char* desc, int (*handler)(int argc, char** argv));

/*----------Menu Engine Execute----------*/
int ExecuteMenu();

int Help();
int Quit(int argc, char **argv);

#endif
