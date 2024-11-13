`GetMessage`函数总的来说和`PeekMessage`函数差不多，但在函数原型和默认行为上有差异
# 函数原型

``` cpp
BOOL GetMessage(        
    LPMSG lpMsg,      
    HWND hWnd,        
    UINT wMsgFilterMin,
    UINT wMsgFilterMax
);
```

# 参数

同`PeekMessage`，但是不能指定在执行函数后是否将消息从消息队列中删除，[[PeekMessage#参数]]

# 功能

同`PeekMessage`，[[PeekMessage#功能]]

# 返回值

同`PeekMessage`, [[PeekMessage#返回值]]

# 说明

该函数在获取消息队列中的消息后**会将该消息删除**
如果**没有获取到指定要求的消息**，此函数**会阻塞这个窗口程序**，**直到消息队列中出现符合要求的消息**

***
#消息处理 #获取消息