#include "Generator.hpp"

namespace prch
{
Prch<PrchType::one>      TypeOne;
Prch<PrchType::two>      TypeTwo;
Prch<PrchType::three>    TypeThree;
Prch<PrchType::four>     TypeFour;
Prch<PrchType::five>     TypeFive;
Prch<PrchType::six>      TypeSix;
Prch<PrchType::seven>    TypeSeven;
Prch<PrchType::eight>    TypeEight;
Prch<PrchType::nine>     TypeNine;
Prch<PrchType::ten>      TypeTen;
Prch<PrchType::eleven>   TypeEleven;
Prch<PrchType::twelve>   TypeTwelve;
Prch<PrchType::thirteen> TypeThirteen;
Prch<PrchType::fourteen> TypeFourteen;
Prch<PrchType::fivteen>  TypeFivteen;

std::array<PrchBase const*, static_cast<uint32_t>(PrchType::num)> allTypes = 
{
      &TypeOne
    , &TypeTwo
    , &TypeThree
    , &TypeFour
    , &TypeFive
    , &TypeSix
    , &TypeSeven
    , &TypeEight
    , &TypeNine
    , &TypeTen
    , &TypeEleven
    , &TypeTwelve
    , &TypeThirteen
    , &TypeFourteen
    , &TypeFivteen
};

template<>
Prch<PrchType::num> const& get<PrchType::num>()
{
    LOG_ERR("This prch is out of scope");
    static Prch<PrchType::num> oofs;
    return oofs;
}

template<>
void generate(const Prch<PrchType::one>&, BigBinary& val, uint64_t bitSize)
{
    uint64_t size64 = bitSize >> 6;
    uint64_t end    = bitSize & (64 - 1);
    val.zero();
    if(bitSize == 0)
        return;
    constexpr uint64_t valA = 0xaaaaaaaaaaaaaaaa; //1010101
    constexpr uint64_t val5 = 0x5555555555555555; //0101010
    uint64_t setter = (end & 1) ? val5 : valA;
    val.set(setter, 0, size64);
    if(end == 0)
        return;
    setter = val5 >> (64 - end - 1);
    val.set(setter, size64, 1);
}

template<>
void generate(const Prch<PrchType::two>&, BigBinary& val, uint64_t bitSize)
{
    if(bitSize == 0)
        return;
    generate(get<PrchType::one>(), val, bitSize - 1);
}

template<>
void generate(const Prch<PrchType::three>&, BigBinary& val, uint64_t bitSize)
{
    uint64_t size64 = bitSize >> 6;
    uint64_t end    = bitSize & (64 - 1);
    val.zero();
    if(bitSize == 0)
        return;
    constexpr uint64_t valF = 0xffffffffffffffff;
    val.set(valF, 0, size64);
    if(end == 0)
    {
        size64--;
        end = 64;
    }
    constexpr uint64_t lastF = 0x7fffffffffffffff;
    val.set(lastF >> (64 - end), size64, 1);
}

template<>
void generate(const Prch<PrchType::four>&, BigBinary& val, uint64_t bitSize)
{
    uint64_t size64 = bitSize >> 6;
    uint64_t end    = bitSize & (64 - 1);
    val.zero();
    if(bitSize == 0)
        return;
    if(end == 0)
    {
        size64--;
        end = 64;
    }
    val.set(uint64_t(1) << (end - 1), size64, 1);
}

template<>
void generate(const Prch<PrchType::five>&, BigBinary& val, uint64_t bitSize)
{
    generate(get<PrchType::seven>(), val, (bitSize + 1) / 2);
}

template<>
void generate(const Prch<PrchType::six>&, BigBinary& val, uint64_t bitSize)
{
    uint64_t startSize64 = (bitSize / 2) >> 6;
    uint64_t start       = (bitSize / 2) & (64 - 1);
    generate(get<PrchType::seven>(), val, bitSize);
    if(bitSize == 0)
        return;
    uint64_t valF = 0xffffffffffffffff;
    if(bitSize < 64)
    {
        valF = valF >> (64 - bitSize);
    }
    if(start == 0 && startSize64 != 0)
    {
        start = 64;
        startSize64--;
    }
    val.set(uint64_t(0), 0, startSize64);
    val.set(valF << start, startSize64, 1);

}

template<>
void generate(const Prch<PrchType::seven>&, BigBinary& val, uint64_t bitSize)
{
    uint64_t size64 = bitSize >> 6;
    uint64_t end    = bitSize & (64 - 1);
    val.zero();
    if(bitSize == 0)
        return;
    constexpr uint64_t valF = 0xffffffffffffffff;
    val.set(valF, 0, size64);
    if(end == 0)
        return;
    constexpr uint64_t lastF = 0x7fffffffffffffff;
    val.set(lastF >> (64 - end - 1), size64, 1);
}

template<>
void generate(const Prch<PrchType::eight>&, BigBinary& val, uint64_t bitSize)
{
    val.zero();
    if(bitSize == 0)
        return;
    val.set(1, 0, 1);
}

template<>
void generate(const Prch<PrchType::nine>&, BigBinary& val, uint64_t bitSize)
{
    uint64_t size64 = bitSize >> 6;
    uint64_t end    = bitSize & (64 - 1);
    val.zero();
    if(bitSize == 0)
        return;
    if(size64 == 0)
    {

        constexpr uint64_t lastF = 0x7fffffffffffffff;
        uint64_t setter = (lastF >> (64 - end - 1)) ^ uint64_t(1);
        val.set(setter, 0, 1);
        return;
    }
    generate(get<PrchType::seven>(), val, bitSize);
    constexpr uint64_t valFe = 0xfffffffffffffffe;
    val.set(valFe, 0, 1);
}

template<>
void generate(const Prch<PrchType::ten>&, BigBinary& val, uint64_t bitSize)
{
    uint64_t size64 = bitSize >> 6;
    uint64_t end    = bitSize & (64 - 1);
    generate(get<PrchType::four>(), val, bitSize);
    if(bitSize == 0)
        return;
    if(end == 0)
    {
        size64--;
        end = 64;
    }
    auto* ptr = val.data() + size64;
    val.set((uint64_t(1) << (end - 1)) & *ptr, size64, 1);
}

template<>
void generate(const Prch<PrchType::eleven>&, BigBinary& val, uint64_t bitSize)
{
    uint64_t size64 = bitSize >> 6;
    uint64_t end    = bitSize & (64 - 1);
    generate(get<PrchType::four>(), val, bitSize);
    if(bitSize == 0)
        return;
    if(end == 0)
    {
        size64--;
        end = 64;
    }
    auto* ptr = val.data() + size64;
    val.set((uint64_t(11) << (end - 2)) & *ptr, size64, 1);
}

template<>
void generate(const Prch<PrchType::twelve>&, BigBinary& val, uint64_t bitSize)
{
    uint64_t size64 = bitSize >> 6;
    uint64_t end    = bitSize & (64 - 1);
    generate(get<PrchType::seven>(), val, bitSize);
    if(bitSize == 0)
        return;
    if(end == 0)
    {
        size64--;
        end = 64;
    }
    auto* ptr = val.data() + size64;
    val.set((uint64_t(10) << (end - 2)) | *ptr, size64, 1);
}

template<>
void generate(const Prch<PrchType::thirteen>&, BigBinary& val, uint64_t bitSize)
{
    generate(get<PrchType::ten>(), val, bitSize - 1);
}

template<>
void generate(const Prch<PrchType::fourteen>&, BigBinary& val, uint64_t bitSize)
{
    generate(get<PrchType::seven>(), val, bitSize);
    if(bitSize == 0)
        return;
    auto* ptr = val.data();
    val.set(uint64_t(01) | (*ptr << 2), 0, 1);
}

template<>
void generate(const Prch<PrchType::fivteen>&, BigBinary& val, uint64_t bitSize)
{
    val.zero();
}

void generate(uint64_t number, BigBinary& val, uint64_t bitSize)
{
    switch (number)
    {
    case 0:
        generate(get<PrchType::one>(), val, bitSize);
        break;
    case 1:
        generate(get<PrchType::two>(), val, bitSize);
        break;
    case 2:
        generate(get<PrchType::three>(), val, bitSize);
        break;
    case 3:
        generate(get<PrchType::four>(), val, bitSize);
        break;
    case 4:
        generate(get<PrchType::five>(), val, bitSize);
        break;
    case 5:
        generate(get<PrchType::six>(), val, bitSize);
        break;
    case 6:
        generate(get<PrchType::seven>(), val, bitSize);
        break;
    case 7:
        generate(get<PrchType::eight>(), val, bitSize);
        break;
    case 8:
        generate(get<PrchType::nine>(), val, bitSize);
        break;
    case 9:
        generate(get<PrchType::ten>(), val, bitSize);
        break;
    case 10:
        generate(get<PrchType::eleven>(), val, bitSize);
        break;
    case 11:
        generate(get<PrchType::twelve>(), val, bitSize);
        break;
    case 12:
        generate(get<PrchType::thirteen>(), val, bitSize);
        break;
    case 13:
        generate(get<PrchType::fourteen>(), val, bitSize);
        break;
    case 14:
        generate(get<PrchType::fivteen>(), val, bitSize);
        break;
    default:
        return;
    }
}

}