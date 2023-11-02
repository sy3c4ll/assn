#ifndef PITCHER_H
#define PITCHER_H

#include "stat.h"
#include "option.hpp"

class pitcher : public stat {
public:
    std::wstring name;
    std::wstring club;
    std::size_t inning;
    std::size_t hit;
    std::size_t bb;
    std::size_t er;

    pitcher(std::wstring const& _name, std::wstring const& _club, std::size_t _inning, std::size_t _hit, std::size_t _bb, std::size_t _er) noexcept;
    option<float> era() const noexcept;
    option<float> whip() const noexcept;
    bool operator==(pitcher const& other) const noexcept;
    bool operator!=(pitcher const& other) const noexcept;
    bool operator<(pitcher const& other) const noexcept;
    bool operator>(pitcher const& other) const noexcept;
    bool operator<=(pitcher const& other) const noexcept;
    bool operator>=(pitcher const& other) const noexcept;

    std::size_t num_stats() const noexcept override;
    std::wstring title() const noexcept override;
    std::wstring const* stat_names() const noexcept override;
    std::wstring const* stats() const noexcept override;
    bool ranked() const noexcept override;
};

#endif // ifndef PITCHER_H