# Kernel_driver_hook_ioctl
> Android/Linux Kernel driver read and write memory.

##### ~~暂时无法读取bss段内存~~

##### ~~读取内存过长时会出现错误~~

使用相应型号的内核源码编译驱动文件

使用`insmod xxx`命令即可加载驱动

使用`rmmod xxx`命令即可卸载驱动

使用`dmesg`查看驱动日志

Google官方编译内核教程(只提供GKI内核编译)：`https://source.android.com/docs/setup/build/building-kernels?hl=zh-cn`

本项目参考：https://github.com/Jiang-Night/Kernel_driver_hack

### **原理**
1. **`ioctl` 的作用**  
`ioctl`（Input/Output Control）是 Linux 内核中用于设备控制的系统调用。用户态程序通过 `ioctl` 向驱动程序发送特定命令，例如配置设备参数或获取内核数据（如进程列表、网络连接信息等）。

2. **Hook 机制**  
**拦截目标**：Hook 的目标通常是以下两类函数：  
内核中处理 `ioctl` 的系统调用（如 `sys_ioctl`）。  
特定设备驱动中实现的 `ioctl` 方法（如 `struct file_operations` 中的 `.unlocked_ioctl`）。  
**Hook 方法**：  
**修改系统调用表**：直接替换 `sys_call_table` 中的 `sys_ioctl` 函数指针。  
**修改驱动函数指针**：替换目标驱动的 `file_operations->unlocked_ioctl` 函数。  
**动态追踪工具**：使用 `kprobes`、`ftrace` 等内核工具动态注入代码。

3. **隐藏痕迹的实现**  
篡改 `ioctl` 的输入输出数据：  
若用户态工具（如 `ps`、`netstat`）通过 `ioctl` 获取系统信息，Hook 可以过滤或伪造返回结果。  
例如：隐藏某个进程的 PID，使工具无法列出该进程。  
绕过安全检查：  
拦截权限验证相关的 `ioctl` 命令，绕过内核的安全策略。

### **优点**
1. **高度隐蔽性**  
直接在内核层操作，用户态工具难以检测到篡改行为。  
无需修改用户态程序，对现有工具透明。

2. **灵活性**  
可针对特定 `ioctl` 命令定制过滤逻辑，例如仅隐藏特定文件或进程。  
支持动态加载/卸载（通过内核模块），便于调试。

3. **高效性**  
内核层操作避免了用户态与内核态的上下文切换开销。

请勿拿本项目用作非法用途或商用，本项目开源仅供学习交流