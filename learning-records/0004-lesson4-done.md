# 第 4 课完成(凭仓库改动推断);进入阶段二

用户未口头报告,但仓库状态证实第 4 课实操已完成:`src/examples/my_first_app/my_first_app.c` 已删除,替换为 `my_first_app.cpp` + `my_first_app.hpp`,内容正是课程要求的 ModuleBase 重写(subscribe sensor_combined → 1 Hz 打印)。用户把头文件后缀从课程示例的 `.h` 自行改成了 `.hpp`——无害的小偏离,说明不是照抄。

**Why:** 第 4 课技能(ModuleBase 五槽、start/stop/status、task 调度)视为已知;阶段一(跑起来)四课全部完成,2026-11-01 起进入阶段二"改得动"。用户仍以 repo 状态为完成信号而非口头汇报——判断进度时先查仓库。

**Evidence:** `ls src/examples/my_first_app/` → CMakeLists.txt、Kconfig、my_first_app.cpp、my_first_app.hpp(2026-11-01)。

**Implications:** 第 5 课(自定义 uORB topic)发布。发布前核实了 v1.17 的两个非显然事实并写进课程:(1) 本仓库 msg 文件已是 PascalCase 命名(`SensorCombined.msg`),topic 名由生成器自动转 snake_case(`px_generate_uorb_topic_files.py:101`),生成结构体 `<topic>_s`;(2) msg/CMakeLists.txt 是**显式列表**,新 .msg 必须手动注册,插到 LedControl.msg 与 LoggerStatus.msg 之间。课程代码片段已用 compile_commands.json 真实参数 + `-Werror` 通过语法验证(沿用 LR-0003 教训)。
