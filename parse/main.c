#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    t_global_state *data;

    data = (t_global_state *)malloc(sizeof(t_global_state));
    if (!data)
        return (0);
    if (argc > 1)
	    parse_map(argv[1], data);
    return (0);
}
