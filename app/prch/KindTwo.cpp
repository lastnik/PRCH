#include "KindTwo.hpp"
#include "Operator.hpp"
#include <cmath>
#include <tuple>
#include <functional>
using namespace prch;
KindTwo::KindTwo(SetupReq const& req)
    : divider(req.size, req.align)
    , residue(req.size, req.align)
    , collect(req.size, req.align)
    , variable(req.size, req.align)
    , zero(req.size, req.align)
    , table({0, 3, 5, 6, 8, 9, 10, 11, 13})
{
}

uint64_t KindTwo::mod(uint64_t sizeBit, uint64_t sizeDivider)
{
    // be careful divider started from ones
    uint64_t length = 0;
    auto zeroSkipper = [](uint64_t const* ptr, uint64_t sizeBit) -> std::tuple<uint64_t, uint64_t>
    {
        uint64_t size64 = sizeBit >> 6;
        uint64_t end    = sizeBit & (64 - 1);
        ptr += size64;
        while(((*ptr) & (1 << end)) == 0)
        {
            if(end == 0)
            {
                if(size64 == 0)
                {
                    std::make_tuple<uint64_t, uint64_t>(0, 1);
                }
                end = 63;
                size64--;
                ptr = ptr - 1;
            }else
            {
                end--;
            }
        }
        return {size64, end + 1};
    };
    auto* ptr1 = residue.data();
    auto[size64Back, endBack] = zeroSkipper(ptr1, sizeBit);
    length = size64Back * 64 + endBack - sizeDivider;
    LOG_DBG("STARTING div %d %d %d %llx %llx", sizeBit, size64Back, endBack, *ptr1, *(divider.data()));
    while(residue > divider || residue == divider)
    {
        //left
        auto* ptr = residue.data();
        auto[size64, end] = zeroSkipper(ptr, size64Back * 64 + endBack);
        LOG_DBG("size64 %d %d", size64, end);
        
        size64Back = size64;
        endBack    = end;
        collect.zero();
        
        concatination(zero, divider, collect, size64 * 64 + end - sizeDivider, sizeDivider);
        if(collect > residue)
        {
            collect.zero();
            concatination(zero, divider, collect, size64 * 64 + end - sizeDivider - 1, sizeDivider);
        }
        LOG_DBG("collect = %llx", *(collect.data()));
        LOG_DBG("residue = %llx", *(residue.data()));
        //div
        while(!(collect == zero))
        {
            for(uint64_t i = 0; i <= size64; i++)
            {
                auto a = *(residue.data() + i);
                auto b = *(collect.data() + i);
                residue.set(a ^ b, i, 1);
                collect.set(~a & b, i, 1);
            }
            LOG_DBG("LOOP: collect = %llx", *(collect.data()));
            LOG_DBG("LOOP: residue = %llx", *(residue.data()));
            variable.zero();
            concatination(zero, collect, variable, 1, sizeDivider - 1);
            collect.set(variable.data(), 0, variable.getSize());
        }
    }
    return length;
}

DecodeInd KindTwo::decode(DecodeReq const& req)
{
    uint64_t sizeBit = req.size * req.alignBit;
    DecodeInd ind;
    ind.isDecoded = false;
    ind.efficiency = 0;
    for(uint64_t sizeDivider = sizeBit; sizeDivider > 1; sizeDivider--)
    {
        for(uint16_t type = 0; type < table.size(); type++)
        {
            LOG_DBG("___________sizeDivider=%d______type=%d_______________",sizeDivider,table[type]);
            generate(table[type], divider, sizeDivider);
            LOG_DBG("generate = %llx", *(divider.data()));
            residue.zero();
            residue.set(req.val.data(), 0, req.val.getSize());
            auto length = mod(sizeBit, sizeDivider);
            if(residue == zero)
            {
                ind.isDecoded = true;
                ind.efficiency = sizeBit / (4 + length + 2 * std::ceil(std::log2f(sizeBit)));
                return ind;
            }
        }
    }
    return ind;
}