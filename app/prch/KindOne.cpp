#include "KindOne.hpp"
#include "Operator.hpp"
#include <cmath>
namespace prch
{

KindOne::KindOne(SetupReq const& req)
    : data{
          BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
        , BigBinary(req.size, req.align)
    }
{
}

DecodeInd KindOne::decode(DecodeReq const& req)
{
    uint64_t sizeBit = req.size * req.alignBit;
    DecodeInd ind;
    ind.isDecoded  = false;
    ind.efficiency = 0.0;
    for(uint64_t i = 0; i < static_cast<uint64_t>(PrchType::num); i++)
    {
        generate(i, data[i], sizeBit);
        if(data[i] == req.val)
        {
            ind.isDecoded = true;
            break;
        }
    }
    if(ind.isDecoded)
    {
        ind.efficiency = sizeBit / (4 + std::ceil(std::log2f(sizeBit)));
    }
    return ind;
}

}