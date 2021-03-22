#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Wave.hpp"
#include "Mob.hpp"

namespace Defender
{
    class Settings {
    public:
        int fps() const noexcept;
        void fps(uint32_t fps) noexcept;
        const std::string &windowName() const noexcept;
        void windowName(const std::string &name) noexcept;
        bool verbose() const noexcept;
        void verbose(bool state) noexcept;
        const std::vector<WaveConfig> &getWaves() const noexcept;
        const std::vector<MobConfig> &getMobs() const noexcept;
        int parse(int ac, const char **av) noexcept;
        int loadMobs(const std::string &filepath) noexcept;
        bool addMob(const std::string &name) noexcept;
        bool setMobHealth(float health) noexcept;
        bool setMobSpeed(float speed) noexcept;
        int loadWaves(const std::string &filepath) noexcept;
        bool addWave(const std::string &name) noexcept;
        bool setDifficulty(size_t difficulty) noexcept;
        bool addMobs(const std::string &mobId, size_t count) noexcept;
    private:
        uint32_t _fps = 30;
        std::string _window_name = "MyDefender";
        std::vector<WaveConfig> _waves;
        std::vector<MobConfig> _mobs;
        bool _verbose = false;
    };
    std::ostream &operator<<(std::ostream &os, const Settings &s) noexcept;
}