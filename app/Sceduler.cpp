#include "Sceduler.hpp"
#include "Memory.hpp"
#include "Logger.hpp"
#include <cstdlib>
#include <string>

using namespace memory;
namespace app
{
ValSceduler::ValSceduler(ValueScedulerCfg const& cfg)
    : BaseSceduler()
    , value(cfg.maxSize, cfg.alignByte)
{
    SetupReq req{cfg.maxSize, cfg.alignByte};
    one   = std::make_unique<KindOne>(req);
    two   = std::make_unique<KindTwo>(req);
    three = std::make_unique<KindThree>(req);
}

void ValSceduler::recieve(BaseCfg const* _cfg)
{
    auto const* cfg = reinterpret_cast<ValueCfg const*>(_cfg);
    uint64_t size = value.getSize();
    uint64_t strSize = cfg->str.size();
    char* end;
    for(uint64_t i = 0; i < size - 1; i++)
    {
        std::string sub = cfg->str.substr(strSize - 16, 16);
        value.set(std::strtoull(sub.c_str(), &end, 16), i, 1);
        strSize -= 16;
    }
    std::string sub = cfg->str.substr(0, strSize);
    value.set(std::strtoull(sub.c_str(), &end, 16), size - 1, 1);
    DecodeReq req1{cfg->size, cfg->alignBit, value};
    auto ind1 = one->decode(req1);
    LOG_INF("Kind one: %d %f", ind1.isDecoded, ind1.efficiency);

    DecodeReq req2{cfg->size, cfg->alignBit, value};
    auto ind2 = three->decode(req2);
    LOG_INF("Kind three: %d %f", ind2.isDecoded, ind2.efficiency);

    DecodeReq req3{cfg->size, cfg->alignBit, value};
    auto ind3 = two->decode(req3);
    LOG_INF("Kind two: %d %f", ind3.isDecoded, ind3.efficiency);
}

}