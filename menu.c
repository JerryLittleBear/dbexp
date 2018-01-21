#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "linktable.h"

int Help();
int Quit(int argc, char** argv);
int ExecuteMenu();
int ExecuteMenu1();
int MenuConfig(char* cmd, char* desc, int (*handler)(int argc, char** argv));

#define CMD_MAX_LEN 128
#define DESC_LEN    1024
#define CMD_NUM     10
#define CMD_MAX_ARGV_NUM 128


/* data struct and its operations */

typedef struct DataNode
{
    tLinkTableNode * pNext;
    char*   cmd;
    char*   desc;
    int     (*handler)(int argc, char** argv);
} tDataNode;

int SearchCondition(tLinkTableNode * pLinkTableNode, void * cmd)
{
    tDataNode * pNode = (tDataNode *)pLinkTableNode;
    if(strcmp(pNode->cmd, cmd) == 0)
    {
        return  SUCCESS;
    }
    return FAILURE;
}

/* show all cmd in listlist */
int ShowAllCmd(tLinkTable * head)
{
    tDataNode * pNode = (tDataNode*)GetLinkTableHead(head);
    while(pNode != NULL)
    {
        printf(" > %s - %s\n", pNode->cmd, pNode->desc);
        pNode = (tDataNode*)GetNextLinkTableNode(head,(tLinkTableNode *)pNode);
    }
    return 0;
}

tLinkTable * head = NULL;

int Help()
{
    puts("/------------------Command List-----------------/");
    ShowAllCmd(head);
    puts("/------------------Command List-----------------/");
    return 0;
}

int Quit(int argc, char* argv[])
{
    exit(0);
}

int ExecuteMenu()
{
    while(1)
    {
	int argc = 0;
	char *argv[CMD_MAX_ARGV_NUM];
        char cmd[CMD_MAX_LEN];
        char *pcmd = NULL;
        printf("Input a cmd number > ");
        /*scanf("%s", cmd);*/
        pcmd = fgets(cmd, CMD_MAX_LEN, stdin);
        if(pcmd == NULL)
        {
            continue;
        }
        /* convert cmd to argc/argv */
        pcmd = strtok(pcmd, " ");
        while(pcmd != NULL && argc < CMD_MAX_ARGV_NUM)
        {
            argv[argc] = pcmd;
            argc++;
            pcmd = strtok(NULL, " ");
        }
        if(argc == 1)
        {
            int len = strlen(argv[0]);
            *(argv[0] + len - 1) = '\0';
        }
        tDataNode *p = (tDataNode*)SearchLinkTableNode(head, SearchCondition, (void*)argv[0]);
        if(p == NULL)
        {
            printf("This is a wrong cmd!\n");
            continue;
        }
        if(p->handler != NULL)
        {
            p->handler(argc, argv);
        }
    }
    
    return 0;
}

/*int ExecuteMenu1()
{
    while(1)
    {
	int argc = 0;
	char *argv[CMD_MAX_ARGV_NUM];
        char cmd[CMD_MAX_LEN];
        char *pcmd = NULL;
        printf("Input a cmd number > ");
        scanf("%s", cmd);
        pcmd = fgets(cmd, CMD_MAX_LEN, stdin);
        if(pcmd == NULL)
        {
            continue;
        }
         convert cmd to argc/argv 
        pcmd = strtok(pcmd, " ");
        while(pcmd != NULL && argc < CMD_MAX_ARGV_NUM)
        {
            argv[argc] = pcmd;
            argc++;
            pcmd = strtok(NULL, " ");
        }
        if(argc == 1)
        {
            int len = strlen(argv[0]);
            *(argv[0] + len - 1) = '\0';
        }
        tDataNode *p = (tDataNode*)SearchLinkTableNode(head, SearchCondition, (void*)argv[0]);
        if(p == NULL)
        {
            printf("This is a wrong cmd!\n");
            continue;
        }
        if(p->handler != NULL)
        {
            p->handler(argc, argv);
        }
    }
    return 0;
}*/

int MenuConfig(char* cmd, char* desc, int (*handler)(int argc, char** argv))
{
    tDataNode* pNode = NULL;
    if(head == NULL)
    {
        head = CreateLinkTable();
        pNode = (tDataNode*)malloc(sizeof(tDataNode));
        pNode->cmd = "help";
        pNode->desc = "Show this command list again ";
        pNode->handler = Help;
        AddLinkTableNode(head, (tLinkTableNode*)pNode);
    }
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = cmd;
    pNode->desc = desc;
    pNode->handler = handler;
    AddLinkTableNode(head, (tLinkTableNode*)pNode);
    return 0;
}
