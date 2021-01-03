#include "KindThree.hpp"
#include "Operator.hpp"
#include <cmath>

namespace prch
{
KindThree::KindThree(SetupReq const& req)
    : part1(req.size, req.align)
    , part2(req.size, req.align)
    , part3(req.size, req.align)
{
}

DecodeInd KindThree::decode(DecodeReq const& req)
{
    uint64_t sizeBit = req.size * req.alignBit;
    DecodeInd ind;
    ind.isDecoded = false;

    for(uint64_t length = 1; length < sizeBit; length++)
    {
        for(uint64_t i = 0; i < static_cast<uint64_t>(PrchType::num); i++)
        {
            generate(i, part1, length);
            for(uint64_t j = 0; j < static_cast<uint64_t>(PrchType::num); j++)
            {
                generate(j, part2, sizeBit - length);
                // LOG_DBG("___________i=%d______j=%d_______________",i,j);
                // LOG_DBG("sizeA %d sizeB %d", length, sizeBit - length);
                // auto* ptr1 = part1.data();
                // LOG_DBG("size1 %d", part1.getSize());
                // for(uint32_t i = 0; i < part1.getSize(); i++)
                // {
                //     LOG_DBG("index1 %d = %llx", i, *(ptr1 + i));
                // }
                // auto* ptr2 = part2.data();
                // LOG_DBG("size2 %d", part2.getSize());
                // for(uint32_t i = 0; i < part2.getSize(); i++)
                // {
                //     LOG_DBG("index2 %d = %llx", i, *(ptr2 + i));
                // }
                concatination(part1, part2, part3, length, sizeBit - length);
                // auto* ptr = part3.data();
                // LOG_DBG("size %d", part3.getSize());
                // for(uint32_t k = 0; k < part3.getSize(); k++)
                // {
                //     LOG_DBG("index %d = %llx", k, *(ptr + k));
                // }
                if(part3 == req.val)
                {
                    ind.isDecoded = true;
                    ind.efficiency = sizeBit / (4 * 2 + 2 * std::ceil(std::log2f(sizeBit)));
                }
            }
        }
    }

    // for(uint64_t i = 0; i < static_cast<uint64_t>(PrchType::num); i++)
    // {
    //     generate(i, data[i], sizeBit);
    //     if(data[i] == req.val)
    //     {
    //         ind.isDecoded = true;
    //         break;
    //     }
    // }
    // if(ind.isDecoded)
    // {
    //     ind.efficiency = sizeBit / (4 + std::ceil(std::log2f(sizeBit)));
    // }
    return ind;

}


}