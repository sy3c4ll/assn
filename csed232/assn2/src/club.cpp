#include "club.h"

club::club(std::wstring const& _name, std::size_t _won, std::size_t _lost, std::size_t _tied): name(_name), won(_won), lost(_lost), tied(_tied) {}
std::size_t club::games() {
    return won + lost + tied;
}
option<float> club::gb(club const& leading) {
    ssize_t diff = leading.won - won + lost - leading.lost;
    return diff > 0 ? some<float>(diff / 2.f) : none<float>();
}
option<float> club::pct() {
    return won + lost > 0 ? some<float>((float) won / (won + lost)) : none<float>();
}