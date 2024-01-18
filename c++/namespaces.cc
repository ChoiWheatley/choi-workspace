/**
 * @file namespaces.cc
 * @author ChoiWheatley (chltmdgus604@gmail.com)
 * @brief 네임스페이스와 인라인 네임스페이스의 차이를 구분하기 위해 만든 파일
 * @version 0.1
 * @date 2024-01-18
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>

namespace Lib {
inline namespace Lib_1 {
void new_function() { std::cout << "I'm new function from Lib::Lib_1\n"; }
} // namespace Lib_1
void old_function() { std::cout << "I'm old function from Lib\n"; }
} // namespace Lib

int main(int argc, char const *argv[]) {
    Lib::old_function();
    Lib::new_function(); // 사용가능! 자동으로 Lib_1가 포함된다.

    using namespace Lib;
    old_function();
    new_function(); // 사용가능!
    return 0;
}
