#include "StartApp.hpp"
#include "Global.hpp"

int main(int argc, char *argv[])
{
    global::initGlobal();
    app::start(argc, argv);
    global::releaseGlobal();
}