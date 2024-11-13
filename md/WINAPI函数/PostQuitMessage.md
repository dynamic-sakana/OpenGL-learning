# 函数原型

```cpp
VOID PostQuitMessage (int nExitCode)
```

# 参数说明

`nExitCode`：构造的`WM_QUIT`消息的`wParam`参数，返回到系统的退出值必须是`WM_QUIT`消息的`wParam`参数。

# 功能

构造一个`WM_QUIT`消息并将其放到此程序的消息队列中，**然后立即返回，不等待此消息的处理完成**

***
#消息处理 #发出消息 