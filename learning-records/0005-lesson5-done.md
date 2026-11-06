# 第 5 课完成(凭仓库改动推断);发布第 6 课

2026-11-04 查仓库:my_first_app.cpp/.hpp 已加入 `uORB::Publication<lesson_report_s>` 发布逻辑,`build/px4_sitl_default/bin/px4` 于 11-04 22:57 重新构建成功。第 5 课核心技能(定义 msg → 注册 → 生成 → 发布)视为掌握。

**Why:** 阶段二第 1 课完成。用户把订阅端从 C++ `SubscriptionBlocking` 换回了 C 风格 `orb_subscribe/poll/orb_copy`(更接近第 5 课原始示例),无害,说明能两种写法互换。

**Evidence:** `grep lesson_report` 命中 hpp:62-63、cpp:75-79;bin/px4 mtime 2026-11-04 22:57。

**已知瑕疵(不阻塞,转入第 6 课热身):** `report.sample_count++` 配合循环内 `lesson_report_s report{}` 零初始化,导致 sample_count 永远为 1;hpp 中的 `_sample_count` 成员留了没用上。第 6 课第 0 步让学员用 `listener` 亲眼观察该 bug 并修复(复用已有成员,一行改动)。

**Implications:** 发布第 6 课《参数系统》。发布前已核实 v1.17 参数机制的三个非显然事实(详见 NOTES.md 2026-11-04 条目),课程 C++ 片段经 compile_commands.json 真实参数 + `-Werror` 语法验证。
