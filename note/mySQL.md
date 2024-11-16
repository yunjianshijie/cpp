# 常用数据结构
``` cpp
MYSQL mysql;
//此结构表示一个数据库连接的处理程序。
MYSQL_RES 
//此结构表示返回行 ( SELECT, SHOW, DESCRIBE, EXPLAIN)的查询结果。从查询返回的信息称为结果集。
MYSQL_ROW
//这是一行数据的类型安全表示。它目前被实现为一个计数字节字符串数组。
//（如果字段值可能包含二进制数据，则不能将它们视为以空字符结尾的字符串，因为此类值在内部可能包含空字节。）通过调用 mysql_fetch_row()获取。
MYSQL_FIELD
//此结构包含元数据：有关字段的信息，例如字段的名称、类型和大小。
//您可以MYSQL_FIELD通过mysql_fetch_field() 重复调用来获取每个字段的结构。
//字段值不是这个结构的一部分；它们包含在一个MYSQL_ROW结构中。
```

# 常用函数

``` cpp
#include <iostream>
#include "mysql.h"
mysql_init(MYSQL * mysql);

```
