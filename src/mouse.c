#include "../includes/cub3d.h"

int mouse_handle(int x, int y, void *param)
{
    (void)param;
    printf("The current X:%d\n",x);
    printf("The current Y:%d\n",y);
    return (0);
}