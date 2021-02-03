#include "LSCENE/lscene.h"
#include "mob.h"
#include "types.h"

static void mob_start(lgameobject_t *object)
{
    mob_t *mob = (typeof(mob))object;
    const sfTexture *texture = lscene_get_texture(object->scene, mob->texture);
    sfVector2u size;

    if (texture == NULL) {
        fprintf(stderr, "Could not load %s texture\n", mob->texture);
        lscene_close(object->scene);
        return;
    }
    size = sfTexture_getSize(texture);
    mob->delay_between_animation = 1.0 / (size.x / size.y);
    sfSprite_setTexture(object->sprite, texture, true);
}

static void mob_update(lgameobject_t *object)
{
    mob_t *mob = (typeof(mob))object;
    sfIntRect rect;
    sfVector2u size;
    size_t width;

    mob->last_animation_time += lscene_delta_time(object->scene);
    if (mob->last_animation_time >= mob->delay_between_animation) {
        mob->last_animation_time = 0;
        size = sfTexture_getSize(sfSprite_getTexture(object->sprite));
        width = size.x / size.y;
        rect = sfSprite_getTextureRect(object->sprite);
        rect.height = size.y;
        rect.left = (rect.left + width) % width;
        sfSprite_setTextureRect(object->sprite, rect);
    }
}

static void mob_catch_event(lgameobject_t *object, const sfEvent *event)
{
    (void)object;
    (void)event;
}

static void mob_destroy(lgameobject_t *object)
{
    mob_t *mob = (typeof(mob))object;
    free(mob->texture);
}

lgameobject_t *mob_create(const char *name, size_t max_health, float speed, const char *texture)
{
    mob_t *mob = calloc(1, sizeof(*mob));

    if (mob == NULL || lgameobject_create(&mob->base_object, name) == -1) {
        return NULL;
    }
    mob->texture = strdup(texture);
    if (mob->texture == NULL) {
        return NULL;
    }
    mob->last_animation_time = 0;
    mob->delay_between_animation = 0;
    mob->texture = NULL;
    mob->health = max_health;
    mob->max_health = max_health;
    mob->speed = speed;
    mob->base_object.type = DEFAULT_MOB;
    mob->base_object.start = &mob_start;
    mob->base_object.update = &mob_update;
    mob->base_object.catch_event = &mob_catch_event;
    mob->base_object.destroy = &mob_destroy;
    return (lgameobject_t *)mob;
}