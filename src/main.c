#include "arguments.h"
#include "my_defender.h"

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
    },
    {
        .opt = "-c",
        .optlong = "--config",
        .handler = &config_setting_handler,
        .help =
            "Defender configuration file, including waves and mobs definitions",
        .args_type_info = "FILEPATH",
        .argument_needed = true,
    },
};

int main(int ac, const char *av[])
{
    opts_handler_t opts;
    defender_ctx_t ctx;

    if (my_defender_ctx_init(&ctx) == -1)
        return -1;
    opts_create(&opts, av[0], HANDLERS, sizeof(HANDLERS) / sizeof(*HANDLERS));
    if (opts_get(&opts, ac, av, &ctx.settings) == -1) {
        return 1;
    }
    if (my_defender_ctx_run(&ctx) == -1)
        return 1;
    my_defender_ctx_destroy(&ctx);
    return 0;
}