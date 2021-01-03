#pragma once
#include "BigBinary.hpp"
#include "Logger.hpp"
#include <array>
namespace prch
{
using namespace binary;
enum class PrchType : uint32_t
{
      one = 0
    , two
    , three
    , four
    , five
    , six
    , seven
    , eight
    , nine
    , ten
    , eleven
    , twelve
    , thirteen
    , fourteen
    , fivteen
    , num
};

struct PrchBase
{
};

template<PrchType T>
struct Prch : PrchBase
{};

extern std::array<PrchBase const*, static_cast<uint32_t>(PrchType::num)> allTypes;

template<PrchType T>
void generate(const Prch<T>&, BigBinary& , uint64_t bitSize);

template<PrchType T>
Prch<T> const& get();

template<>
Prch<PrchType::num> const& get<PrchType::num>();

template<PrchType T>
Prch<T> const& get()
{
    return *reinterpret_cast<Prch<T> const*>(allTypes[static_cast<uint32_t>(T)]);
}

extern Prch<PrchType::one> TypeOne;
template<>
void generate(const Prch<PrchType::one>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::two> TypeTwo;
template<>
void generate(const Prch<PrchType::two>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::three> TypeThree;
template<>
void generate(const Prch<PrchType::three>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::four> TypeFour;
template<>
void generate(const Prch<PrchType::four>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::five> TypeFive;
template<>
void generate(const Prch<PrchType::five>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::six> TypeSix;
template<>
void generate(const Prch<PrchType::six>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::seven> TypeSeven;
template<>
void generate(const Prch<PrchType::seven>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::eight> TypeEight;
template<>
void generate(const Prch<PrchType::eight>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::nine> TypeNine;
template<>
void generate(const Prch<PrchType::nine>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::ten> TypeTen;
template<>
void generate(const Prch<PrchType::ten>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::eleven> TypeEleven;
template<>
void generate(const Prch<PrchType::eleven>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::twelve> TypeTwelve;
template<>
void generate(const Prch<PrchType::twelve>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::thirteen> TypeThirteen;
template<>
void generate(const Prch<PrchType::thirteen>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::fourteen> TypeFourteen;
template<>
void generate(const Prch<PrchType::fourteen>&, BigBinary& , uint64_t bitSize);

extern Prch<PrchType::fivteen> TypeFivteen;
template<>
void generate(const Prch<PrchType::fivteen>&, BigBinary& , uint64_t bitSize);

template<PrchType T>
void generate(const Prch<T>&, BigBinary& , uint64_t bitSize)
{
    LOG_ERR("This prch is out of scope");
}

void generate(uint64_t number, BigBinary& val, uint64_t bitSize);
};