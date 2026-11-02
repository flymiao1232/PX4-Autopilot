# Mission: PX4 飞控系统——能独立改 PX4 代码

## Why

用户(amiao)需要在 PX4-Autopilot 仓库中独立添加、修改功能,并通过 SITL 仿真验证改动能跑通。驱动力是实际开发能力,不是理论:最终要能动手改,而不是只知道概念。

## Success looks like

- 能新建一个 PX4 模块/应用,编译进固件或 SITL,并通过 nsh shell 运行验证
- 能读懂现有模块(如 mc_att_control、ekf2)的数据流:订阅什么 topic、发布什么 topic
- 能定义新的 uORB topic 并在两个模块之间传递自定义数据
- 能启动 SITL,用 uorb/listener 等命令观察、调试数据流
- 改动出问题时,知道从哪里入手定位(日志、uorb top、模块文档)

## Constraints

- 工作环境:WSL2 (Ubuntu 24.04) 内的 PX4-Autopilot v1.17 分支,已有 `build/px4_sitl_default` 构建产物
- 课程用中文授课,代码与术语保留原文
- 单课要短,能快速完成;用户时间碎片化

## Out of scope

- 飞行动力学/控制理论本身的深入数学推导
- 具体硬件焊接、装机、实飞调参
- ROS 2 / DDS 上层生态(除非改代码任务需要)
- NuttX 内核 internals(除非调试需要)
