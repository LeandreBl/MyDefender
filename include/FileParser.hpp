#pragma once

#include <string>
#include <functional>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <iostream>

namespace Defender {
    class FileParser {
        public:
            struct ParserEntry {
                std::string pattern;
                std::function<bool (size_t lineno, const std::string &line, std::istringstream &ss)> callback;
            };
            FileParser(const std::string &filepath, const ParserEntry *entries, size_t count) noexcept;
            int parse(char delimiter = '\n') const noexcept;
        private:
            int findCallback(size_t lineno, const std::string &line) const noexcept;
            std::vector<ParserEntry> _labels;
            std::string _filepath;
    };
}