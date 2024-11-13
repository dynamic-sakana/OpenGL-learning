# 函数原型

```cpp
B00L SendMessage（HWND hWnd，UINT Msg，WPARAM wParam，LPARAM lParam）
```

# 参数说明

- `hWnd`：哪一个窗口将接受这个消息
- `Msg`：指定被发送的消息
- `wParam`：消息的附加信息
- `IParam`：消息的附加信息
其实就是消息的数据结构中的一些数据，只是少了触发时间和触发时鼠标位置[[消息]].

# 功能

**注意**：与[[PostMessage]]不同的是，这个函数会直接调用该窗口的消息处理函数，并等待该消息处理完成后，该函数返回。

***
#消息处理  #发出消息