1、安装mysql数据库：sudo apt install mysql-server，（数据库的root帐号的密码为daijiangxiong1)
2、安装链接库:sudo apt install libmysqlclient-dev
3、编译的命令：gcc -o testmain bptree.c initdb.c linktable.c menu.c range_query.c reserve.c -l mysqlclient showtable.c testmain.c updatedb.c
4、进入数据库，创建数据库和表:mysql -u root -p然后输入密码
5、显示数据库列表：SHOW DATABASES;
6、创建数据库：CREATE DATABASE 数据库名;
7、删除数据库:DROP DATABASE 数据库名;
8、创建表：CREATE TABLE 表名;
9、使用数据库：USE 数据库名;
10、编译不通过时，要链接相关库，其中，-l表示在/lib和/usr/lib和/usr/local/lib里搜索库的.so文件然后链接该库，-L是在后面制定的任意目录里查找.so文件，链接该库;-I用来指定头文件目录，让gcc除了去/usr/include里找，还去指定的目录里找：gcc -o test test.c -l mysqlclient -I /usr/local/mysql/include/mysql/ -L /usr/local/mysql/lib/mysql
11、常用库函数：
----mysql_real_connect（）;成功返回非0, 失败返回0
----int mysql_errno(MYSQL *);返回错误号
----mysql_error(MYSQL*);
----mysql_select_db(MYSQL* mysql, char* dbname);
----mysql_real_query(MYSQL*, char* query, int strlen(query));成功返回0, 失败返回非0
12、为解决mysql数据库中文乱码问题，要在创建数据库时设置字符集utf-8:CREATE DATABASE travel_system DEFAULT CHARSET=UTF8
13、为RESERVATIONS表添加里3个字段：location&FromCity&ArivCity, 其中FromCity和ArivCity用触发器关联于FLIGHTS表中的FromCity和ArivCity字段（外键），这样，用户做预订的时候可以输入, 并把用户名字custName设为CUSTOMERS表的外键。
14、预订的功能上，如果是resvType是2或3， 预订当地的酒店或车辆，会要求输入
