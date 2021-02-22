#include "my_defender.h"
#include "LSCENE/ltext_button.h"
#include "LSCENE/lvector.h"

int my_defender_ctx_init(defender_ctx_t *ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    ctx->settings.fps = DEFAULT_FPS;
    ctx->settings.window_name = strdup(DEFAULT_WINDOW_NAME);
    if (ctx->settings.window_name == NULL)
        return -1;
    return 0;
}

int my_defender_ctx_run(defender_ctx_t *ctx)
{
    if (lscene_create(
            &ctx->scene, ctx->settings.window_name, ctx->settings.fps) == -1) {
        return -1;
    }
    lscene_run(&ctx->scene);
    return 0;
}

void my_defender_ctx_destroy(defender_ctx_t *ctx)
{
    free(ctx->settings.window_name);
    lscene_destroy(&ctx->scene);
}