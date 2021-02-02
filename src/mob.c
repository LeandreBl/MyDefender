#include "mob.h"
#include "types.h"

static void mob_start(lgameobject_t *object)
{
    (void)object;
}

static void mob_update(lgameobject_t *object)
{
    (void)object;
}

static void mob_catch_event(lgameobject_t *object, const sfEvent *event)
{
    (void)object;
    (void)event;
}

static void mob_destroy(lgameobject_t *object)
{
    (void)object;
}

lgameobject_t *mob_create(const char *name, size_t max_health, float speed)
{
    mob_t *mob = calloc(1, sizeof(*mob));

    if (mob == NULL || lgameobject_create(&mob->base_object, name) == -1) {
        return NULL;
    }
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