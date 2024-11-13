# 函数原型

```cpp
BOOL TranslateMessage (CONST MSG* lpMsg)
```

# 参数

`lpMsg`：需要翻译的消息对象

# 功能

将**虚拟键消息**转换为**字符消息**。字符消息**被送到调用线程的消息队列**中，在**下一次线程调用函数[[GetMessage]]或[[PeekMessage]]时被读出**。

***
#消息处理 #翻译消息