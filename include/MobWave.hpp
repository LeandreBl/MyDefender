#pragma once

#include <string>

namespace Defender {
    class MobWave {
        public:
            MobWave(const std::string &mobId, size_t count) noexcept;
            const std::string &getId() const noexcept;
            size_t getCount() const noexcept;
        private:
            std::string _mobId;
            size_t _count;
    };
}