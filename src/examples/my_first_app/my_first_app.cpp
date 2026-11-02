#include "my_first_app.hpp"

#include <px4_platform_common/log.h>
#include <px4_platform_common/posix.h>

#include <poll.h>
#include <errno.h>

#include <uORB/uORB.h>
#include <uORB/topics/sensor_combined.h>

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

	while (!should_exit()) {          // stop 命令会把它变为 true
		px4_poll(fds, 1, 1000);

		if (fds[0].revents & POLLIN) {
			struct sensor_combined_s raw;
			orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &raw);
			PX4_INFO("Accel:\t%8.4f\t%8.4f\t%8.4f",
				 (double)raw.accelerometer_m_s2[0],
				 (double)raw.accelerometer_m_s2[1],
				 (double)raw.accelerometer_m_s2[2]);
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
