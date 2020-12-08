#include "Global.hpp"
#include "Logger.hpp"

namespace global
{

void initGlobal()
{
    logger::open();
}

void releaseGlobal()
{
    logger::close();
}

}