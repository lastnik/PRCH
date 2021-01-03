#include "StartApp.hpp"
#include "Logger.hpp"
#include "Generator.hpp"
#include "Sceduler.hpp"
#include <nlohmann/json.hpp>
#include <sstream>
#include <memory>
#include "Memory.hpp"
using json = nlohmann::json;
using namespace prch;
using namespace memory;

namespace app
{

struct Config
{
    bool     isValue = false;
    ValueCfg cfgVal;

    bool    isFile = false;
    FileCfg cfgFile;

    bool        isColoring = false;
    ColoringCfg cfgColoring;
};

void decode(std::stringstream& stream, Config& cfg)
{
    auto j = json::parse(stream.str());
    auto mode = j["mode"].get<std::string>();
    auto level = j["level"].get<std::string>();
    if(level == "debug")
    {
        setLevel(logger::Level::debug);
    }
    else if(level == "info")
    {
        setLevel(logger::Level::info);
    }
    else if(level == "waring")
    {
        setLevel(logger::Level::waring);
    }
    else if(level == "error")
    {
        setLevel(logger::Level::error);
    }
    else if(level == "critical")
    {
        setLevel(logger::Level::critical);
    }
    LOG_DBG("JSON: \n %s", stream.str().c_str());

    if(mode == "value")
    {
        cfg.isValue = true;
        cfg.cfgVal.size = j["size"].get<uint64_t>();
        cfg.cfgVal.alignBit = j["alignBit"].get<uint64_t>();
        cfg.cfgVal.str = j["value"].get<std::string>();
        return;
    }
    if(mode == "file")
    {

    }
    if(mode == "coloring")
    {

    }
}

void start(std::stringstream& stream)
{
    Config cfg;
    decode(stream, cfg);
    std::unique_ptr<BaseSceduler> sceduler;
    if(cfg.isValue)
    {
        ValueScedulerCfg setup{mem_align(cfg.cfgVal.size * cfg.cfgVal.alignBit, 8) / 8, 1};
        sceduler = std::make_unique<ValSceduler>(setup);
        sceduler->recieve(&cfg.cfgVal);
    }
}
}