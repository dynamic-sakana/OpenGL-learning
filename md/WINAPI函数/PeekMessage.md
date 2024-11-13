# 函数原型

``` cpp
BOOL PeekMessage(        
    LPMSG lpMsg,      
    HWND hWnd,        
    UINT wMsgFilterMin,
    UINT wMsgFilterMax,
    UINT wRemoveMsg
);
```

# 参数

- `lpMsg`：指向一个`MSG`结构的指针，该结构中保存着从**线程消息队列中取得的消息信息**。
- `hWnd`：指定**返回的消息（`lpMsg`指向的消息）的窗口句柄。该窗口必须属于正在调用的线程**。
	- 如果`hWnd`值为`NULL`：`PeekMessage`检索**所有任务消息队列中的消息（此程序每个窗口的消息）**。
	- 如果`hWnd`值为`INVALID_HANDLE_VALUE`，`PeekMessage`会检索那些`hWnd`值为`NULL`的消息，并作为由`PostThreadMessage`投递的消息来对待。
- `wMsgFilterMin`：指定被检索的最小消息值的整数
	如：使用`WM_KEYFIRST`指定第一个键盘消息或`WM_MOUSEFIRST`指定第一个鼠标消息。
- `wMsgFilterMax`：指定被检索的最大消息值的整数
	如：使用`WM_KEYLAST`指定最后的键盘消息或`WM_MOUSEFIRST`指定最后的鼠标消息。
- 如果将`wMsgFilterMin`和`wMsgFilterMax`**都指定为0**，`GetMessage`函数会**返回所有可用的消息**。
- `wRemoveMsg`：指定消息的处理方式。该参数的值可以为下列的值之一（此处只列出两个，因为其他值适用的系统过于古老）
	1. `WM_NOREMOVE`：消息经过此函数后**不删除**
	2. `WM_REMOVW`：消息经过此函数后**删除**

# 功能

从消息队列中获取满足要求的消息，并将消息写入传入的`MSG`对象中

# 返回值

`BOOL`类型（其实是C++中的整数类型），只在获取到`WM_QUIT`后返回`false`，其他情况均返回`true`

如果消息队列中没有符合要求的消息，那么`PeekMessage`会将`lpMsg`的`message`属性设置为`WM_NULL`（空消息）。

***
#消息处理 #获取消息