# 第 7 课完成(凭仓库改动推断);发布第 8 课,进入阶段三

2026-11-05 查仓库:`ROMFS/px4fmu_common/init.d-posix/rcS:375` 有 `my_first_app start`,且 `build/px4_sitl_default/etc/init.d-posix/rcS:375` 副本一致(说明改后重跑过 make,ROMFS 已重新打包);第 6 课遗留 bug 也已修:`my_first_app.cpp:86` 为 `report.sample_count=++_sample_count`,配合 hpp:63 成员 `_sample_count`。第 7 课核心技能(找到挂载点 → 改 ROMFS 源 → 重建 → 验证自启)视为掌握。

**Why:** 阶段二三课(topic → param → rcS)全部闭环,用户具备"往 PX4 加功能"的完整能力。用户主动要求进入阶段三,且明确四个方向都要学:控制链路、日志分析、Out-of-Tree、仿真深入。阶段三规划为 4 课(见 roadmap)。

**Evidence:** rcS 源与 build 副本同步;`px4-my_first_app` 独立进程二进制存在于 build/bin(印证课程非显然事实 2)。

**Implications:** 第 8 课选控制链路——它最贴合 mission(改 PX4 代码),且直接复用第 5 课 topic 心智模型和第 4 课 ModuleBase Run() 槽。发布前源码核实 v1.17 控制链事实:(1) mc_rate_control 输出为 vehicle_thrust_setpoint + vehicle_torque_setpoint 双 topic(MulticopterRateControl.hpp:110-111),老资料的 actuator_controls_0 已过时;(2) 控制环由 SubscriptionCallbackWorkItem 以上游 topic 到达唤醒(MulticopterRateControl.cpp:126),频率是量出来的不是配的;(3) control_allocator 订阅推力/力矩设定点、发布 actuator_motors(ControlAllocator.hpp:178-187);(4) 悬停推力 ≈ MPC_THR_HOVER(x500 机架文件设 0.60),可作实测对答案。
