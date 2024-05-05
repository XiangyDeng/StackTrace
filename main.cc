/*
 * @Author: XiangyDeng 158812420@qq.com
 * @Date: 2024-05-02 13:22:59
 * @LastEditors: XiangyDeng 158812420@qq.com
 * @LastEditTime: 2024-05-05 16:54:24
 * @FilePath: /signal_processor/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * 
 */

#include <iostream>
#include <thread>
#include <mutex>

#include <signal.h>

#include "./component/stacktrace.hpp"
#include "./component/test.hpp"

class OnceTask {
 public:
 	OnceTask() {}
 	~OnceTask() {}

 	void Init() {
		std::call_once(task_flag_, [&]() {
			std::cout << "Task init" << std::endl;
		});
 	}

 private:
 	std::once_flag task_flag_;
};


int main() {
	signal(SIGABRT, SigProc);
	signal(SIGSEGV, SigProc);
	std::shared_ptr<OnceTask> task_ptr = std::make_shared<OnceTask>();
	
	std::thread t1([&]() {
		task_ptr->Init();
	});

	std::thread t2([&]() {
		task_ptr->Init();
	});

	t1.join();
	t2.join();

	add1(1, 2);
	return 0;
}