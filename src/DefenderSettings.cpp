#include <iostream>
#include <algorithm>

#include "DefenderSettings.hpp"
#include "MiniParseArg.hpp"
#include "FileParser.hpp"
#include "colors.h"

namespace Defender
{
    int Settings::fps() const noexcept
    {
        return _fps;
    }

    void Settings::fps(uint32_t fps) noexcept
    {
        _fps = fps;
    }

    const std::string &Settings::windowName() const noexcept
    {
        return _window_name;
    }

    void Settings::windowName(const std::string &name) noexcept
    {
        _window_name = name;
    }

    bool Settings::verbose() const noexcept
    {
        return _verbose;
    }

    void Settings::verbose(bool state) noexcept
    {
        _verbose = state;
    }

    const std::vector<WaveConfig> &Settings::getWaves() const noexcept
    {
        return _waves;
    }

    const std::vector<MobConfig> &Settings::getMobs() const noexcept
    {
        return _mobs;
    }

    bool Settings::addWave(const std::string &name) noexcept
    {
        try {
            _waves.emplace_back(name);
            return true;
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }
    }


    bool Settings::setDifficulty(size_t difficulty) noexcept
    {
        if (_waves.size() == 0) {
            std::cerr << "Error: difficulty set without a previous wavename." << std::endl;
            return false;
        }
        _waves.back().setDifficulty(difficulty);
        return true;
    }

    bool Settings::addMobs(const std::string &mobId, size_t count) noexcept
    {
        if (_waves.size() == 0) {
            std::cerr << "Error: mobs set without a previous wavename." << std::endl;
            return false;
        }
        _waves.back().addMobsetting(mobId, count);
        return true;
    }

    int Settings::parse(int ac, const char **av) noexcept
    {
        static const MiniParseArg::MiniParseOption OPTIONS[] = {
            {
                .opt = "-f",
                .optlong = "--framerate",
                .callback = [&](int, const char **av) -> bool {
                    try
                    {
                        _fps = std::stoul(av[1]);
                        return _fps != 0;
                    }
                    catch (const std::exception &)
                    {
                        return false;
                    }
                },
                .help = "Set a custom framerate.",
                .argType = "UINT",
            },
            {
                .opt = "-n",
                .optlong = "--name",
                .callback = [&](int, const char **av) -> bool {
                    _window_name = av[1];
                    return _window_name.length() != 0;
                },
                .help = "Set a custom window's name.",
                .argType = "STRING",
            },
            {
                .opt = "-wc",
                .optlong = "--waves-config",
                .callback = [&](int, const char **av) -> bool {
                    int res = loadWaves(av[1]);
                    if (res < 0) {
                        std::cerr << "Error: Invalid file: " << av[1] << std::endl;
                        return false;
                    }
                    return res == 0;
                },
                .help = "Defender waves configuration file.",
                .argType = "FILEPATH",
            },
            {
                .opt = "-mc",
                .optlong = "--mobs-config",
                .callback = [&](int, const char **av) -> bool {
                    return false;
                },
                .help = "Defender mobs configuration file.",
                .argType = "FILEPATH",
            },
            {
                .opt = "-v",
                .optlong = "--verbose",
                .callback = [&](int, const char **) -> bool {
                    _verbose = true;
                    return true;
                },
                .help = "Turn on the verbose mode.",
                .argType = ""
            },
        };
        MiniParseArg parser(av[0], OPTIONS, sizeof(OPTIONS) / sizeof(*OPTIONS));
        return parser.parse(ac, av);
    }

    int Settings::loadMobs(const std::string &filepath) noexcept
    {
        static const FileParser::ParserEntry BINDS[] = {
            {
                .pattern = "mobname ",
                .callback = [&](size_t lineno, const std::string &s, std::istringstream &ss) -> bool {
                    return false;
                },
            },
            {
                .pattern = "health ",
                .callback = [&](size_t lineno, const std::string &s, std::istringstream &ss) -> bool {
                    return false;
                }
            },
            {
                .pattern = "speed ",
                .callback = [&](size_t lineno, const std::string &s, std::istringstream &ss) -> bool {
                    return false;
                }
            },
        };
        FileParser parser(filepath, BINDS, sizeof(BINDS) / sizeof(*BINDS));
        return parser.parse();
    }

    int Settings::loadWaves(const std::string &filepath) noexcept
    {
        static const FileParser::ParserEntry BINDS[] = {
            {
                .pattern = "wavename ",
                .callback = [&](size_t lineno, const std::string &s, std::istringstream &ss) -> bool {
                    std::string name;

                    if (!(ss >> name) || name.length() == 0) {
                        std::cerr << "Error: line " << RED << lineno << RESET << ": " << "invalid wave name." << std::endl;
                        return false;
                    }
                    return addWave(name);
                }
            },
            {
                .pattern = "difficulty ",
                .callback = [&](size_t lineno, const std::string &s, std::istringstream &ss) -> bool {
                    size_t difficulty;

                    if (!(ss >> difficulty)) {
                        std::cerr << "Error: line " << RED << lineno << RESET << ": " << "invalid difficulty." << std::endl;
                        return false;
                    }
                    return setDifficulty(difficulty);
                }
            },
            {
                .pattern = "-",
                .callback = [&](size_t lineno, const std::string &s, std::istringstream &ss) -> bool {
                    std::string mobId;
                    size_t count;

                    if (!(ss >> mobId) || mobId.length() == 0) {
                        std::cerr << "Error: line " << RED << lineno << RESET << ": " << "invalid mobId." << std::endl;
                        return false;
                    }
                    if (!(ss >> count) || count == 0) {
                        std::cerr << "Error: line " << RED << lineno << RESET << ": " << "invalid '" << mobId << "' count." << std::endl;
                        return false;
                    }
                    return addMobs(mobId, count);
                }
            },
        };
        FileParser parser(filepath, BINDS, sizeof(BINDS) / sizeof(*BINDS));
        int res = parser.parse();
        if (res != 0)
            return res;
        std::sort(_waves.begin(), _waves.end(), [](const WaveConfig &a, const WaveConfig &b) -> bool
            {
                return a.getDifficulty() < b.getDifficulty();
            }
        );
        return 0;
    }

    std::ostream &operator<<(std::ostream &os, const Settings &s) noexcept
    {
        os << std::endl << '{' << std::endl
           << "  fps: " << s.fps() << ',' << std::endl
           << "  verbose: " << (s.verbose() ? "true," : "false,") << std::endl
           << "  window: " << s.windowName() << std::endl;
        for (auto &&i : s.getWaves()) {
            os << "  {" << std::endl
                << "    name: " << i.getName() << ',' << std::endl
                << "    difficulty: " << i.getDifficulty() << ',' << std::endl;
            for (auto &&mobs : i.getMobs()) {
                os << "    {" << std::endl
                    << "      id: " << mobs.getId() << ',' << std::endl
                    << "      count: " << mobs.getCount() << ',' << std::endl
                    << "    }," << std::endl;
            }
            os << "  }," << std::endl;
        }
        os << "}" << std::endl;
        return os;
    }
}