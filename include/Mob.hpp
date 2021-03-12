#pragma once

#include <string>

namespace Defender {
    class MobConfig {
    public:
        MobConfig(const std::string &name) noexcept;
        const std::string &name() const noexcept;
        void health(float health) noexcept;
        float health() const noexcept;
        void speed(float speed) noexcept;
        float speed() const noexcept;
    private:
        std::string _name;
        float _health;
        float _speed;
    };
}