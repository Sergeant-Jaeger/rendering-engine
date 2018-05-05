#include "plot.h"

void pixel_plot(PointH &plot_pointh)
{
	int x, y;

	x = (int)plot_pointh[0];
	y = (int)plot_pointh[1];

	if (plot_pointh[2] < zbuffer[y][x])
	{
		rd_write_pixel(x, y, fg_color);

		zbuffer[y][x] = plot_pointh[2];
	}
}

void poly_plot(PointH &plot_pointh, float color[3])
{
	int x, y;

	x = (int)plot_pointh[0];
	y = (int)plot_pointh[1];

	if (plot_pointh[2] < zbuffer[y][x])
	{
		rd_write_pixel(x, y, color);

		zbuffer[y][x] = plot_pointh[2];
	}
}