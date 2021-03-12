#include "MobWave.hpp"

namespace Defender
{
    MobWave::MobWave(const std::string &mobId, size_t count) noexcept
    {
        _mobId = mobId;
        _count = count;
    }

    const std::string &MobWave::getId() const noexcept
    {
        return _mobId;
    }

    size_t MobWave::getCount() const noexcept
    {
        return _count;
    }
}