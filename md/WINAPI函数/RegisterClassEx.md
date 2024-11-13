# 函数原型

```cpp
ATOM RegisterClassEx（CONST WNDCLASSEX *Ipwcx)
```

该函数接受一个`WNDCLASSEX`[[窗口类]]对象的指针，将窗口类的信息写入操作系统中，并返回窗口类的句柄。**在调用该函数以前，务必将`Ipwcx`中的`lpfnWndProc`属性初始化为一个可用的函数。否则会出现`Segmentation fault`错误。**

***
#窗口程序 #注册窗口类