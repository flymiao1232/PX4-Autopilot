# 第 6 课完成(凭仓库改动推断);发布第 7 课

2026-11-05 查仓库:`src/examples/my_first_app/my_first_app_params.c` 已建(186B,11-05 00:46),`my_first_app.cpp:63/66/72` 有 param_find/param_get 与 PARAM_INVALID 检查;`build/px4_sitl_default/bin/px4` 于 11-05 01:05 重建。第 6 课核心技能(定义参数 → 强制重配 → 运行时拨动)视为掌握。

**Why:** 阶段二第 2 课完成。至此用户已具备"数据(topic)→ 配置(param)"两项核心机制,第 7 课补最后一块"启动(rcS)",阶段二闭环。

**Evidence:** grep 命中 my_first_app.cpp:63 `param_find("LR5_PUB_EN")`、:66 PX4_ERR、:72 `param_get(pub_en, &pub_en_val)`;bin/px4 mtime 2026-11-05 01:05;params.c 内容与本课模板一致(@boolean、@group My First App)。

**未验证项(不阻塞):** 第 0 步热身 bug(sample_count 永为 1)是否已修——cpp 今天 01:01 有改动,但该 bug 的修复需要 hpp/cpp 配合,不确证;第 7 课动手前让用户顺手确认 listener 里 sample_count 是否每秒 +1。

**Implications:** 发布第 7 课《启动流程》。发布前已核实 v1.17 启动机制的五个非显然事实(详见 NOTES.md 2026-11-05 条目):rcS 由宿主机 /bin/sh 执行(main.cpp:546);px4-* 一模块一进程;机架文件名即 autostart ID(4001_gz_x500);rcS `set +e` 失败不中止;extras.txt 钩子在 NuttX rcS:599。
