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

static void on_click(ltext_button_t *button, void *data)
{
    printf("clicked\n");
}

int my_defender_ctx_run(defender_ctx_t *ctx)
{
    if (lscene_create(
            &ctx->scene, ctx->settings.window_name, ctx->settings.fps) == -1) {
        return -1;
    }
    lgameobject_t *bt = ltext_button_create("click me", vector2f(100, 100), lscene_get_texture(&ctx->scene, "assets/textures/button.png"), &on_click);
    ltext_button_set_text(bt, lscene_get_font(&ctx->scene, "assets/fonts/commodore-64.ttf"), sfBlack, 18);
    lscene_add_gameobject(&ctx->scene, bt);
    lscene_run(&ctx->scene);
    return 0;
}

void my_defender_ctx_destroy(defender_ctx_t *ctx)
{
    free(ctx->settings.window_name);
    lscene_destroy(&ctx->scene);
}