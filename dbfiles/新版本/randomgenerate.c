#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ROW_NUM 50
#define COL_NUM 5
int genFLIGHTS()
{
    int flightNum=1;
    int price[]={600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050};
    int numSeats[]={200, 190, 180, 170, 160, 150,140, 130, 120, 110, 100};
    int numAvail[]={100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0};
    char city1[][10]={"厦门", "沈阳", "苏州", "北京", "广州","太原", "西安"};
    char city2[][10]={"漳州", "大连", "上海", "石家庄", "深圳","大同", "兰州"};
    int cityNum1=0, cityNum2 = 1;
    
    int col, row, i1=0, i2=0, i3=0, i4=0, i5=0;
    srand((int)time(0));
    FILE *fp=fopen("FLIGHTS", "w+");
    if(fp == NULL)
    {
        fprintf(stderr, "open file error!\n");
    }
    else
    {
        for(row = 0; row < ROW_NUM; row++)
        {
        
            fprintf(fp, "%d\t%d\t%d\t%d\t%s\t%s\n", flightNum, price[(int)rand()%(sizeof(price)/sizeof(int))], numSeats[(int)rand()%(sizeof(numSeats) / sizeof(int))], numAvail[(int)rand()%(sizeof(numAvail) / sizeof(int))], city1[cityNum1++ % (sizeof(city1) / 10)], city2[cityNum2 % (sizeof(city2) / 10)]);
            if(cityNum1%7 == 0)
                cityNum2++;
          
            flightNum++;   
        }
    }
    fclose(fp);

    return 0;
}


int genCARS()
{
    int flightNum=1;
    int price[]={600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050};
    int numSeats[]={200, 190, 180, 170, 160, 150,140, 130, 120, 110, 100};
    int numAvail[]={100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0};
    char city1[][10]={"厦门", "沈阳", "苏州", "北京", "广州","太原", "西安"};
    char city2[][10]={"漳州", "大连", "上海", "石家庄", "深圳","大同", "兰州"};
    int cityNum1=0, cityNum2 = 1;
    
    int col, row, i1=0, i2=0, i3=0, i4=0, i5=0;
    srand((int)time(0));
    FILE *fp=fopen("CARS", "w+");
    if(fp == NULL)
    {
        fprintf(stderr, "open file error!\n");
    }
    else
    {
        for(row = 0; row < ROW_NUM; row++)
        {
        
            fprintf(fp, "%d\t%d\t%d\t%d\t%s\t%s\n", flightNum, price[(int)rand()%(sizeof(price)/sizeof(int))], numSeats[(int)rand()%(sizeof(numSeats) / sizeof(int))], numAvail[(int)rand()%(sizeof(numAvail) / sizeof(int))], city1[cityNum1++ % (sizeof(city1) / 10)], city2[cityNum2 % (sizeof(city2) / 10)]);
            if(cityNum1%7 == 0)
                cityNum2++;
          
            flightNum++;   
        }
    }
    fclose(fp);
    return 0;
}
int main()
{
    genFLIGHTS();
    //gen
    
    return 0;
}
