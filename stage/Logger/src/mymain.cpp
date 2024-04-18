#include <../include/mylogger.hpp>


int main(int argc, const char * argv[])
{
    logger("/home/ilya/logger/inf.log", true, true);

    for (std::size_t i = 0; i < 10; ++i){
        LOG_DEBUG("Hello");

    }

    return 0;
}
