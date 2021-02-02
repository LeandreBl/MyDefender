#include "settings.h"
#include "arguments.h"
#include "LSCENE/lscene.h"

static const arg_handler(settings_t) HANDLERS[] = {
    {
        .opt = "-h",
        .optlong = "--help",
        .handler = OPTS_HELP_HANDLER,
        .help = "Display this help",
        .args_type_info = NULL,
        .argument_needed = false,
    },
    {
        .opt = "-f",
        .optlong = "--framerate",
        .handler = &fps_setting_handler,
        .help = "Set a custom framerate",
        .args_type_info = "UNSIGNED INT",
        .argument_needed = true,
    },
    {
        .opt = "-n",
        .optlong = "--name",
        .handler = &window_name_setting_handler,
        .help = "Set a custom window's name",
        .args_type_info = "STRING",
        .argument_needed = true,
    }
};

int main(int ac, const char *av[])
{
    opts_handler_t opts;
    settings_t settings = {
        .window_name = "MyDefender",
        .fps = 30,
    };
    lscene_t scene;

    opts_create(&opts, av[0], HANDLERS, sizeof(HANDLERS) / sizeof(*HANDLERS));
    if (opts_get(&opts, ac, av, &settings) == -1) {
        return 1;
    }
    if (lscene_create(&scene, settings.window_name, settings.fps) == -1) {
        return -1;
    }
    lscene_run(&scene);
    lscene_destroy(&scene);
    return 0;
}