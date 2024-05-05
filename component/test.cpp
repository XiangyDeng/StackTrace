/*
 * @Author: XiangyDeng 158812420@qq.com
 * @Date: 2024-05-03 20:29:28
 * @LastEditors: XiangyDeng 158812420@qq.com
 * @LastEditTime: 2024-05-04 20:55:46
 * @FilePath: /signal_processor/test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <functional>
#include <vector>
#include <iostream>
#include <type_traits>

int add1(int a, int b) {
  char *p = nullptr;
  *p = 0;
  return a + *p;
}