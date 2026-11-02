# 第 2 课完成:能从零创建并编译运行一个 PX4 模块

用户直接进入"next lesson"(2026-11-01),视为报告第 2 课《手写你的第一个应用》完成:创建 `src/examples/my_first_app/`(C 文件 + CMakeLists.txt + Kconfig)、在 `boards/px4/sitl/default.px4board` 加 `CONFIG_EXAMPLES_MY_FIRST_APP=y`、增量编译、shell 运行,并升级为订阅 `sensor_combined` 打印加速度计。

**Why:** 用户已掌握"模块三件套 + 编译开关接线"这条改 PX4 代码的最短路径,可在此基础上叠加长期运行模块、自定义 topic 等内容。

**Evidence:** 用户口头推进(未见到输出/Quiz 成绩)。若第 3 课实操发现 gap,回滚。

**Implications:**
- 第 3 课(Gazebo SITL)可直接引用 `my_first_app` 作为观察对象。
- 用户仓库现有未提交改动:`src/examples/my_first_app/`(新建)+ `default.px4board`(加一行)。未来注意区分教学改动与用户自己的开发改动。
