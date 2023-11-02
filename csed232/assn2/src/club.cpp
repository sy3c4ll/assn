#include "club.h"
#include <sstream>

inline std::wstring ftos(float f) {
    std::wstringstream wss;
    wss.precision(3);
    wss << std::fixed << f;
    return wss.str();
}

club::club(std::wstring const& _name, std::size_t _won, std::size_t _lost, std::size_t _tied) noexcept
    : leading(none<club const*>()), name(_name), won(_won), lost(_lost), tied(_tied) {}
club& club::set_leading_club(club const& _leading) noexcept {
    leading = some<club const*>(&_leading);
    return *this;
}
std::size_t club::game() const noexcept {
    return won + lost + tied;
}
option<float> club::gb() const noexcept {
    if (leading.is_none())
        return none<float>();
    ptrdiff_t diff = leading.unwrap()->won - won + lost - leading.unwrap()->lost;
    return diff > 0 ? some<float>(diff / 2.f) : none<float>();
}
option<float> club::pct() const noexcept {
    return won + lost > 0 ? some<float>((float) won / (won + lost)) : none<float>();
}
bool club::operator==(club const& other) const noexcept {
    return pct() == other.pct();
}
bool club::operator!=(club const& other) const noexcept {
    return !(*this == other);
}
bool club::operator<(club const& other) const noexcept {
    return pct() < other.pct();
}
bool club::operator>(club const& other) const noexcept {
    return other < *this;
}
bool club::operator<=(club const& other) const noexcept {
    return !(*this > other);
}
bool club::operator>=(club const& other) const noexcept {
    return !(*this < other);
}

constexpr std::size_t N = 7;
std::size_t club::num_stats() const noexcept {
    return N;
}
std::wstring club::title() const noexcept {
    return L"";
}
std::wstring const* club::stat_names() const noexcept {
    static std::wstring const key[N] = {};
    return key;
}
std::wstring const* club::stats() const noexcept {
    static std::wstring value[N];
    value[0] = name;
    value[1] = game();
    value[2] = won;
    value[3] = lost;
    value[4] = tied;
    value[5] = gb().map_or<std::wstring>(L"-", ftos);
    value[6] = pct().map_or<std::wstring>(L"-", ftos);
    return value;
}
bool club::ranked() const noexcept {
    return won + lost > 0;
}