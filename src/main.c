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
        .opt = "-wc",
        .optlong = "--waves-config",
        .handler = &waves_setting_handler,
        .help = "Defender waves configuration file",
        .args_type_info = "FILEPATH",
        .argument_needed = true,
    },
    {
        .opt = "-mc",
        .optlong = "--mobs-config",
        .handler = &mobs_setting_handler,
        .help = "Defender mobs configuration file",
        .args_type_info = "FILEPATH",
        .argument_needed = true,
    },
    {
        .opt = "-v",
        .optlong = "--verbose",
        .handler = &verbose_setting_handler,
        .help = "Turn on the verbose mode",
        .args_type_info = NULL,
        .argument_needed = false,
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
    if (ctx.settings.verbose)
        settings_print(&ctx.settings);
    if (my_defender_ctx_run(&ctx) == -1)
        return 1;
    my_defender_ctx_destroy(&ctx);
    return 0;
}