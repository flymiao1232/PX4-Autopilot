# 教学笔记(教师用草稿)

- 2026-10-31:用户通过问答确定——主题:PX4 飞控系统;目标:能独立改 PX4 代码(加功能、跑通 SITL 验证)。
- 环境:WSL2 Ubuntu 24.04,仓库分支 `local/v1.17.0`(基于 PX4 v1.17),已有 `build/px4_sitl_default` 完整构建,`px4_simple_app`、`hello` 等示例已在默认 SITL 配置中启用。
- 用户的 PX4 基础水平尚未确认——第 1 课结尾应询问实操结果,据此判断起点。
- 授课语言:中文;术语保留英文原文。
- 2026-10-31(用户反馈):**课程主线对齐 PX4 官方文档 v1.17(https://docs.px4.io/v1.17/)**——与用户仓库分支版本一致。所有课程引用优先用 v1.17 版本链接(而非 main),并标注对应官方章节。已建 `reference/roadmap.html` 课程地图(阶段一:跑起来 4 课;阶段二:改得动 3 课;阶段三:进阶按需)。
- 截至 2026-11-01:第 1、2 课用户报告完成(LR-0001/0002);第 3 课《Gazebo SITL 与数据调试》已发布,等待反馈。已核实:WSL 内 gz 8.14(Harmonic)已装;SITL GCS 端口 18570;gz 目标由 gz_bridge/CMakeLists.txt 生成。
- 2026-11-01(勘误,用户发现):第 3 课中 mavlink_shell 命令原写 `udp:127.0.0.1:18570`,已改为 `udpout:127.0.0.1:18570`。根因:pymavlink 裸 `udp:` 前缀=input 监听模式(默认 input=True),与 PX4 mavlink 在 18570 的监听冲突;`udpout:` 才是主动发送到 PX4。**教训:课程里所有命令类内容应在发布前对照源码验证,不能凭惯例写。**
- 2026-11-01:第 4 课《正式模块与调度》发布。发布前已用 compile_commands.json 真实编译参数(-Werror)对课程 C++ 代码做语法验证,发现并修复 errno.h 缺失。**今后所有含代码的课程发布前必须做此验证。** 新参考文档:reference/module-anatomy.html(模块骨架速查)。LR-0003 已记录。
- 2026-11-01(晚):用户 /teach next lesson。查仓库确认第 4 课已完成(my_first_app 已重写为 .cpp/.hpp 的 ModuleBase 模块,用户自行把头文件改成 .hpp)——用户以 repo 状态为完成信号,判断进度先查仓库。LR-0004 已记录,进入阶段二。
- 第 5 课《自定义 uORB topic》发布。发布前源码核实两个 v1.17 非显然事实:(1) msg 文件已 PascalCase 命名,topic 名由 px_generate_uorb_topic_files.py 自动转 snake_case;(2) msg/CMakeLists.txt 是显式列表,新 .msg 必须手动注册(LessonReport.msg 插在 LedControl.msg 与 LoggerStatus.msg 之间)。课程 C++ 片段(含 math.h/sqrtf)已用真实参数 + -Werror 通过。注:本机默认 WSL 发行版是 RflySim-20.04,跑 Ubuntu 命令必须 `wsl -d Ubuntu-24.04`。
