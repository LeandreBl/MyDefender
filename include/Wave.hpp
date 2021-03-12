#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "MobWave.hpp"

namespace Defender {
    class WaveConfig {
    public:
        WaveConfig(const std::string &name) noexcept;
        void setDifficulty(size_t n) noexcept;
        void addMobsetting(const std::string &mobId, size_t count) noexcept;
        const std::string &getName() const noexcept;
        const std::vector<MobWave> &getMobs() const noexcept;
        size_t getDifficulty() const noexcept;
    private:
        std::string _name;
        std::vector<MobWave> _mobSettings;
        size_t _difficulty;
    };
}