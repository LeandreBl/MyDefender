#include "Wave.hpp"

namespace Defender
{
    WaveConfig::WaveConfig(const std::string &name) noexcept
        : _name(name), _difficulty(0)
    {}

    void WaveConfig::setDifficulty(size_t n) noexcept
    {
        _difficulty = n;
    }

    void WaveConfig::addMobsetting(const std::string &mobId, size_t count) noexcept
    {
        try {
            _mobSettings.emplace_back(mobId, count);
        }
        catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    const std::string &WaveConfig::getName() const noexcept
    {
        return _name;
    }

    const std::vector<MobWave> &WaveConfig::getMobs() const noexcept
    {
        return _mobSettings;
    }

    size_t WaveConfig::getDifficulty() const noexcept
    {
        return _difficulty;
    }
}