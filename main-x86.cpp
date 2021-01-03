#include "StartApp.hpp"
#include "Global.hpp"
#include <fstream>
int main(int argc, char *argv[])
{
    global::initGlobal();
    std::ifstream i("cfg.json");
    std::stringstream buffer;
    buffer << i.rdbuf();
    app::start(buffer);
    global::releaseGlobal();
}