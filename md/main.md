# `wWinMain` 是什么

我们都知道 `main` 函数是程序的入口，但有时我们也会看到 `wmain()`,`wWinMain()`,`_tmain`,`_tWinMain()`之类的函数入口


| 函数名  |   `main`    |       `wmain`        |    `WinMain`    |        `wWinMain`        |
| :--: | :---------: | :------------------: | :-------------: | :----------------------: |
| 程序类型 | console程序入口 | Unicode下的console程序入口 | Application程序入口 | Unicode下的Application程序入口 |

在不知道编译器使用的是什么字符集的时候可以使用`_tmain()`或`_tWinMain()`来代替`main()/wmian()`或者`winMain()/wWinMain()`，因为`_tmain()`和`_tWinMain()`函数会根据**当前编译环境**来决定调用对应的入口函数（实际上就是**宏定义**）

``` cpp
#ifdef _UNICODE
   #define _tmain     wmain
   #define _tWinMain  wWinMain
#else
   #define _tmain     main
   #define _tWinMain  winMain
#endif
```
