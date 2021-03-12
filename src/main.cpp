#include "DefenderSettings.hpp"
#include "Logger.hpp"

int main(int ac, const char **av)
{
    Defender::Settings settings;

    if (settings.parse(ac, av) != 0)
        return 1;
    Logger::setVerbose(settings.verbose());
    Logger::Log(settings);
    return 0;
}