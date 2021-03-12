#include "Mob.hpp"

namespace Defender
{
    MobConfig::MobConfig(const std::string &name) noexcept
    : _name(name), _health(100.f), _speed(10.f)
    {}

    const std::string &MobConfig::name() const noexcept
    {
        return _name;
    }

    void MobConfig::health(float health) noexcept
    {
        _health = health;
    }

    float MobConfig::health() const noexcept
    {
        return _health;
    }

    void MobConfig::speed(float speed) noexcept
    {
        _speed = speed;
    }

    float MobConfig::speed() const noexcept
    {
        return _speed;
    }
}