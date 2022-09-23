#include "../../includes/cub3d.h"

int  handle_leave (t_global_state *state)
{
    (void)state;
    exit (EXIT_SUCCESS);
    return (0);
}

int handle_shoot_sprite (t_global_state *state)
{
    static int i;
    static int j;
    
    if (state->trigger)
    {
        state->current_sprite = state->sprites[i++];
        rerender_map_sprites (state);
        if (i == 5)
        {
            state->trigger = 0;
            i = 0;
        }
    }
    else if (state->releaod)
    {
        state->current_sprite = state->releaod_sprites[j++];
        rerender_map_sprites (state);
        if (j == 10)
        {
            state->releaod = 0;
            j = 0;
            state->current_sprite = state->sprites[0];
            rerender_map_sprites (state);
        }
    }
    return (0);
}

void play_sound (int flag)
{
    int id;

    id = fork ();
    if (id == 0)
    {
        if (flag == 0)
            system ("afplay /Users/yelatman/Documents/CUB-3D/assets/shotgun-firing-4-6746.mp3");
        if (flag == 1)
            system ("afplay /Users/yelatman/Documents/CUB-3D/assets/1911-reload-6248.mp3");
        exit (EXIT_SUCCESS);
    }
}
