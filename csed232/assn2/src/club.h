#ifndef CLUB_H
#define CLUB_H

#include "stat.h"
#include "option.hpp"

class club : public stat {
    option<club const*> leading;

public:
    std::wstring name;
    std::size_t won;
    std::size_t lost;
    std::size_t tied;

    club(std::wstring const& _name, std::size_t _won, std::size_t _lost, std::size_t _tied) noexcept;
    club& set_leading_club(club const& _leading) noexcept;
    std::size_t game() const noexcept;
    option<float> gb() const noexcept;
    option<float> pct() const noexcept;
    bool operator==(club const& other) const noexcept;
    bool operator!=(club const& other) const noexcept;
    bool operator<(club const& other) const noexcept;
    bool operator>(club const& other) const noexcept;
    bool operator<=(club const& other) const noexcept;
    bool operator>=(club const& other) const noexcept;

    std::size_t num_stats() const noexcept override;
    std::wstring title() const noexcept override;
    std::wstring const* stat_names() const noexcept override;
    std::wstring const* stats() const noexcept override;
    bool ranked() const noexcept override;
};

#endif // ifndef CLUB_H