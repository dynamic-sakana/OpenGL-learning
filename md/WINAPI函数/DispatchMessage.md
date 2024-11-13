# 函数原型

```cpp
BOOL DispatchMessage (CONST MSG* lpMsg)
```

# 参数

`lpMsg`：需要处理的消息对象

# 功能

调用该消息中的`hwnd`消息所指向的窗口的消息处理函数`lpfnWndProc`
此外，如果 `MSG` 结构指向的是一个 `WM_TIMER` 消息，并且 `WM_TIMER` 消息的 `lParam` 参数不为 `NULL`，则 `DispatchMessage` 会调用 `lParam` 指向的函数，而不是调用窗口程序

# 特别说明

此函数不会删除消息队列中的消息对象！！！

***
#消息处理 #消息分发