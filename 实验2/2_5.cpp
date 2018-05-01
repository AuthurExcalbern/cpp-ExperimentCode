#include <csignal>
#include <iostream>
 
struct div_0_exception {};
 
void handle_div_0(int)
{
    throw div_0_exception();
}
 
int main()
{
    if (SIG_ERR == signal(SIGFPE, handle_div_0)) {
        std::cerr << "fail to setup handler." << std::endl;
        return 1;
    }
    try {
        int x, y;
        std::cin >> x >> y;
        std::cout << x / y << std::endl;
    } catch (div_0_exception) {
        std::cerr << "attempt to divide integer by 0." << std::endl;
    }
    return 0;
}