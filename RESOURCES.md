# PX4 学习资源

> **主线资源:PX4 官方文档 v1.17** — https://docs.px4.io/v1.17/(与本地仓库 v1.17 分支完全对应)。
> 课程按官方 "Getting Started → Concepts → Simulation → Middleware → Modules → Debugging" 的脉络设计,每课标注对应官方页面。

## Knowledge(按课程模块分组,均为 v1.17 版本链接)

### 入门主线(对应第 1–2 课)
- [Toolchain Installation → Ubuntu Setup](https://docs.px4.io/v1.17/en/dev_setup/dev_env.html) — 开发环境。用于:环境出问题(缺依赖、编译器版本)时对照。
- [Building the Code](https://docs.px4.io/v1.17/en/dev_setup/building_px4.html) — `make <target>` 构建体系。用于:理解 build 目录结构、烧录/启动命令。
- [Writing your First Application (Hello Sky)](https://docs.px4.io/v1.17/en/modules/hello_sky.html) — **第一个应用的权威教程**。用于:第 2 课逐节对照。
- [Application/Module Template](https://docs.px4.io/v1.17/en/modules/module_template.html) — 正式模块模板(start/stop、命令行参数)。用于:第 4 课。
- [PX4 Flight Stack Architecture](https://docs.px4.io/v1.17/en/concept/architecture.html) — 系统架构图。用于:第 1 课数据流心智模型。

### Middleware(对应第 3、5 课)
- [uORB Messaging](https://docs.px4.io/v1.17/en/middleware/uorb.html) — uORB 机制权威说明。用于:topic 定义、发布/订阅语义。
- [uORB Graph](https://docs.px4.io/v1.17/en/middleware/uorb_graph.html) — 模块间数据流全图。用于:改代码前查"谁订阅/发布谁"。
- [uORB Message Reference](https://docs.px4.io/v1.17/en/msg_docs/) — 每个 topic 的字段定义速查。

### Simulation(对应第 3 课)
- [Gazebo Simulation](https://docs.px4.io/v1.17/en/sim_gazebo_gz/) — SITL 标准仿真器。用于:`make px4_sitl gz_x500` 及调试。

### Concepts(对应第 5–6 课)
- [Parameters & Configs](https://docs.px4.io/v1.17/en/advanced/parameters_and_configurations.html) — 参数系统。用于:给自定义模块加可配置参数。
- [System Startup](https://docs.px4.io/v1.17/en/concept/system_startup.html) — rcS 启动脚本流程。用于:让模块开机自启。

### 阶段三(对应第 8–11 课)
- [Control Allocation](https://docs.px4.io/v1.17/en/concept/control_allocation.html) — 控制分配数学。用于:第 8 课、改机型/混控。
- [uORB Graph](https://docs.px4.io/v1.17/en/middleware/uorb_graph.html) — 模块间数据流可交互全图。用于:改代码前查"谁订阅/发布谁"。
- [Gazebo Vehicles](https://docs.px4.io/v1.17/en/sim_gazebo_gz/vehicles.html) — 自定义仿真机型/世界。用于:第 9 课仿真深入。
- [Flight Log Analysis](https://docs.px4.io/v1.17/en/log/flight_log_analysis.html) — ULog 与 Flight Review。用于:第 10 课日志分析。
- [Out-of-Tree Modules](https://docs.px4.io/v1.17/en/advanced/out_of_tree_modules.html) — 不动主仓库发布模块。用于:第 11 课。
- [pyulog 文档](https://pyulog.readthedocs.io/) — ULog 解析库。用于:第 10 课编程式读日志。

### Debugging(贯穿全程)
- [Sensor/uORB Topic Debugging](https://docs.px4.io/v1.17/en/debug/sensor_uorb_topic_debugging.html) — uorb/listener 调试命令。
- [Consoles/Shells](https://docs.px4.io/v1.17/en/debug/consoles.html) — PX4 shell / MAVLink shell 的区别与用法。
- [Logging & ULog](https://docs.px4.io/v1.17/en/dev_log/logging.html) — 飞行日志。

### 本地资源(与线上文档同源,可离线查阅)
- 本仓库 `docs/en/` — v1.17 文档源码,**完全与代码同步,最高信任**。
- 本仓库源码 `src/` — 文档可能滞后,源码是最终真相(`src/examples/px4_simple_app/`、`src/templates/template_module/`)。

## Wisdom (Communities)

- [PX4 Discuss 论坛](https://discuss.px4.io/) — 官方论坛。用于:改代码遇到的具体问题、设计讨论。
- [PX4 Discord](https://discord.gg/dronecode) — 实时讨论。用于:快速提问、关注开发动态。
- [PX4 GitHub Issues / PR](https://github.com/PX4/PX4-Autopilot/issues) — 改代码前先看有没有人做过。
- 中文社区:阿木实验室社区等 — 资料质量参差,谨慎采信,以官方文档为准。

(用户暂未表示拒绝社区。)

## Gaps

- 暂无系统性的"从改代码角度讲解 PX4 模块设计"的高质量中文资源——课程由 v1.17 官方文档 + 本仓库源码支撑。
