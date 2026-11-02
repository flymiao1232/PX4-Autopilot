# 第 3 课完成;用户展现出源码验证习惯

用户完成第 3 课(Gazebo SITL 与数据调试),并在课程勘误中指出 mavlink_shell 应使用 `udpout:` 前缀——经查 pymavlink 源码确认用户正确(裸 `udp:` 为 legacy 监听模式,与 PX4 在 18570 的监听冲突)。

**Why:** (1) 第 3 课技能(Gz 架构、uorb/listener 调试、MAVLink shell、HEADLESS)视为已知;(2) 用户能通过推理 UDP 方向性质质疑并证实文档错误,说明具备"读源码验证"的工程师直觉——教学可更放手,让其多独立排错。

**Evidence:** 用户主动提出 udpout 质疑(2026-11-01);勘误已修正第 3 课两处并记于 NOTES.md。

**Implications:** 第 4 课发布前,我用 compile_commands.json 的真实编译参数对课程代码做了 -Werror 语法验证(发现并修复 errno.h 缺失)——此后发布含代码的课程前都应执行此验证(教训来自 udpout 勘误)。
