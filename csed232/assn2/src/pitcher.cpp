#include "pitcher.h"
#include <sstream>

inline std::wstring ftos(float f) {
    std::wstringstream wss;
    wss.precision(3);
    wss << std::fixed << f;
    return wss.str();
}

pitcher::pitcher(std::wstring const& _name, std::wstring const& _club, std::size_t _inning, std::size_t _hit, std::size_t _bb, std::size_t _er) noexcept
    : name(_name), club(_club), inning(_inning), hit(_hit), bb(_bb), er(_er) {}
option<float> pitcher::era() const noexcept {
    return inning > 0 ? some<float>((float) (er * 9) / inning) : none<float>();
}
option<float> pitcher::whip() const noexcept {
    return inning > 0 ? some<float>((float) (hit + bb) / inning) : none<float>();
}
bool pitcher::operator==(pitcher const& other) const noexcept {
    return era() == other.era();
}
bool pitcher::operator!=(pitcher const& other) const noexcept {
    return !(*this == other);
}
bool pitcher::operator<(pitcher const& other) const noexcept {
    return era() > other.era();
}
bool pitcher::operator>(pitcher const& other) const noexcept {
    return other < *this;
}
bool pitcher::operator<=(pitcher const& other) const noexcept {
    return !(*this > other);
}
bool pitcher::operator>=(pitcher const& other) const noexcept {
    return !(*this < other);
}

constexpr std::size_t N = 8;
std::size_t pitcher::num_stats() const noexcept {
    return N;
}
std::wstring pitcher::title() const noexcept {
    return L"";
}
std::wstring const* pitcher::stat_names() const noexcept {
    static std::wstring const key[N] = {};
    return key;
}
std::wstring const* pitcher::stats() const noexcept {
    static std::wstring value[N];
    value[0] = name;
    value[1] = club;
    value[2] = era().map_or<std::wstring>(L"-", ftos);
    value[3] = inning;
    value[4] = hit;
    value[5] = bb;
    value[6] = er;
    value[7] = whip().map_or<std::wstring>(L"-", ftos);
    return value;
}
bool pitcher::ranked() const noexcept {
    return inning > 0;
}