#include "batter.h"
#include <sstream>

inline std::wstring ftos(float f) {
    std::wstringstream wss;
    wss.precision(3);
    wss << std::fixed << f;
    return wss.str();
}

batter::batter(std::wstring const& _name, std::wstring const& _club, std::size_t _ab, std::size_t _hit, std::size_t _bb, std::size_t _db, std::size_t _sf) noexcept
    : name(_name), club(_club), ab(_ab), hit(_hit), bb(_bb), db(_db), sf(_sf) {}
option<float> batter::ba() const noexcept {
    return ab > 0 ? some<float>((float) hit / ab) : none<float>();
}
option<float> batter::obp() const noexcept {
    return ab + bb + db + sf > 0 ? some<float>((float) (hit + bb + db) / (ab + bb + db + sf)) : none<float>();
}
bool batter::operator==(batter const& other) const noexcept {
    return ba() == other.ba();
}
bool batter::operator!=(batter const& other) const noexcept {
    return !(*this == other);
}
bool batter::operator<(batter const& other) const noexcept {
    return ba() < other.ba();
}
bool batter::operator>(batter const& other) const noexcept {
    return other < *this;
}
bool batter::operator<=(batter const& other) const noexcept {
    return !(*this > other);
}
bool batter::operator>=(batter const& other) const noexcept {
    return !(*this < other);
}

constexpr std::size_t N = 9;
std::size_t batter::num_stats() const noexcept {
    return N;
}
std::wstring batter::title() const noexcept {
    return L"";
}
std::wstring const* batter::stat_names() const noexcept {
    static std::wstring const key[N] = {};
    return key;
}
std::wstring const* batter::stats() const noexcept {
    static std::wstring value[N];
    value[0] = name;
    value[1] = club;
    value[2] = ba().map_or<std::wstring>(L"-", ftos);
    value[3] = ab;
    value[4] = hit;
    value[5] = bb;
    value[6] = db;
    value[7] = sf;
    value[8] = obp().map_or<std::wstring>(L"-", ftos);
    return value;
}
bool batter::ranked() const noexcept {
    return ab > 0;
}