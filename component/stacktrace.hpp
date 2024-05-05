/*
 * @Author: XiangyDeng 158812420@qq.com
 * @Date: 2024-05-02 12:21:23
 * @LastEditors: XiangyDeng 158812420@qq.com
 * @LastEditTime: 2024-05-04 21:29:21
 * @FilePath: /test/test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include <cxxabi.h>       
#include <dlfcn.h>       
#include <execinfo.h>
#include <signal.h>
#include <link.h>
#include <sys/types.h>
#include <unistd.h>
#include "regex"

#define STACK_BUF_LEN 40

// 将地址转换为VMA地址
size_t ConvertToVMA(size_t addr)
{
  Dl_info info;
  link_map* link_map;
  dladdr1((void*)addr,&info,(void**)&link_map, RTLD_DL_LINKMAP);
  return addr-link_map->l_addr;
}

// 打印堆栈信息
void ShowStack() {
  int i;
  void *buffer[STACK_BUF_LEN];
  int n = backtrace(buffer, STACK_BUF_LEN);
  char **symbols = backtrace_symbols(buffer, n);
  std::regex re("\\[(.+)\\]");

  std::cout << "============= call stack begin: ================" << std::endl;
  for (i = 2; i < n - 2; i++) {
    std::smatch match;
    std::string symbol = symbols[i];
    std::regex_search(symbol, match, re);
    std::string addr = match[1];
    size_t VMA_addr = ConvertToVMA((size_t)buffer[i]);

    void* handle = dlopen("libstdc++.so.6", RTLD_LAZY);
    if (handle == nullptr) {
        perror("dlopen");
        return;
    }
    Dl_info info;
    if (dladdr(buffer[i], &info) == 0) {
        perror("dladdr error");
        return;
    }
    char command[256];
    snprintf(command, sizeof(command),"addr2line -e %s -Ci -f %zx",info.dli_fname,VMA_addr);

    FILE* pipe = popen(command, "r");
    if (pipe == NULL) {
        perror("popen");
        return;
    }

    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("function:\t%s", buffer);
    }

    if (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("file line:\t%s", buffer);
    }
    dlclose(handle);

    pclose(pipe);
    std::cout << "[" << i - 2 << "] addr: " << symbols[i] << std::endl;
    std::cout << "----------------------------------------" << std::endl;
  }
  std::cout << "============= call stack end: ===================" << std::endl;
}

// 信号处理函数
void SigProc(int signo) {
	std::cout << "\nSignal: " << signo << std::endl;

	ShowStack();
	exit(1);
}