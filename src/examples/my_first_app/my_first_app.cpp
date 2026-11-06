#include <parameters/param.h>
#include "my_first_app.hpp"

#include <px4_platform_common/log.h>
#include <px4_platform_common/posix.h>

#include <poll.h>
#include <errno.h>

#include <uORB/uORB.h>
#include <uORB/topics/sensor_combined.h>

#include <math.h>

int MyFirstApp::print_status()
{
	PX4_INFO("Running");
	return 0;
}

int MyFirstApp::custom_command(int argc, char *argv[])
{
	return print_usage("unknown command");
}

int MyFirstApp::task_spawn(int argc, char *argv[])
{
	_task_id = px4_task_spawn_cmd("my_first_app",
				      SCHED_DEFAULT,
				      SCHED_PRIORITY_DEFAULT,
				      2000,
				      (px4_main_t)&run_trampoline,
				      (char *const *)argv);

	if (_task_id < 0) {
		_task_id = -1;
		return -errno;
	}

	return 0;
}

MyFirstApp *MyFirstApp::instantiate(int argc, char *argv[])
{
	MyFirstApp *instance = new MyFirstApp();

	if (instance == nullptr) {
		PX4_ERR("alloc failed");
	}

	return instance;
}

void MyFirstApp::run()
{
	int sensor_sub_fd = orb_subscribe(ORB_ID(sensor_combined));
	orb_set_interval(sensor_sub_fd, 1000);  // 限制到 1 Hz

	px4_pollfd_struct_t fds[1];
	fds[0].fd = sensor_sub_fd;
	fds[0].events = POLLIN;

	param_t pub_en = param_find("LR5_PUB_EN");  // 新增

	if(pub_en == PARAM_INVALID) {
		PX4_ERR("param LR5_PUB_EN not found");
		return;
	}
	while (!should_exit()) {          // stop 命令会把它变为 true
		px4_poll(fds, 1, 1000);
		int32_t pub_en_val = 0;
		param_get(pub_en, &pub_en_val);  // 新增
		if((fds[0].revents & POLLIN) && (pub_en_val != 0)) {  // 新增
			struct sensor_combined_s raw;
			orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &raw);
			PX4_INFO("Accel:\t%8.4f\t%8.4f\t%8.4f",
				 (double)raw.accelerometer_m_s2[0],
				 (double)raw.accelerometer_m_s2[1],
				 (double)raw.accelerometer_m_s2[2]);
			float mag = sqrtf(raw.accelerometer_m_s2[0] * raw.accelerometer_m_s2[0]
					  + raw.accelerometer_m_s2[1] * raw.accelerometer_m_s2[1]
					  + raw.accelerometer_m_s2[2] * raw.accelerometer_m_s2[2]);
			lesson_report_s report{};
			report.timestamp = hrt_absolute_time();
			report.accel_magnitude = mag;
			report.sample_count=++_sample_count;
			_lesson_report_pub.publish(report);    // 首次 publish 时自动 advertis
		}
	}

	orb_unsubscribe(sensor_sub_fd);
}

int MyFirstApp::print_usage(const char *reason)
{
	if (reason) {
		PX4_WARN("%s\n", reason);
	}

	PRINT_MODULE_DESCRIPTION(
		R"DESCR_STR(
### Description
Lesson example: subscribe sensor_combined, print accel at 1 Hz.

### Examples
CLI usage example:
$ my_first_app start

)DESCR_STR");

	PRINT_MODULE_USAGE_NAME("my_first_app", "example");
	PRINT_MODULE_USAGE_COMMAND("start");
	PRINT_MODULE_USAGE_DEFAULT_COMMANDS();

	return 0;
}

int my_first_app_main(int argc, char *argv[])
{
	return MyFirstApp::main(argc, argv);   // start/stop/status 都在这里面
}
