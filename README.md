# ClipboardHistory

基于 Qt 6 / C++ 开发的 Windows 剪贴板历史管理工具。程序监听系统剪贴板文本变化，将历史内容持久化到本地 SQLite 数据库，并支持搜索、单条删除和清空记录。

## 功能

- 自动监听系统剪贴板文本变化
- 自动过滤空内容与完全重复内容
- 最新记录置顶显示
- 关键词实时搜索，支持忽略大小写
- 删除单条历史记录
- 清空全部记录并提供二次确认
- 使用 SQLite 本地持久化，程序重启后自动恢复历史记录

## 技术实现

- `QClipboard`：监听系统剪贴板变化
- `QListWidget`：展示与过滤历史记录
- Qt Signals & Slots：响应剪贴板和界面事件
- Qt SQL / SQLite：本地持久化存储
- 参数绑定：执行插入和删除 SQL，避免手工拼接数据

## 开发环境

- C++17
- Qt 6.5+
- Qt Widgets / Qt SQL
- SQLite
- CMake
- MSVC 2022
- Windows

## 构建

使用 Qt Creator 打开项目根目录中的 `CMakeLists.txt`，选择包含 Qt SQL / SQLite 驱动的 Qt 6 MSVC Kit 后配置并构建项目即可。

运行后会在程序工作目录创建 `clipboard.db`，该文件属于本地运行数据，不纳入版本控制。
