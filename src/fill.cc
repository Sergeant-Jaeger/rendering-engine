#include "Fill.h"

void area_fill(int x, int y)
{
	float test_color[3];
	float up_test_color[3];
	float down_test_color[3];
	float left_test_color[3];
	float right_test_color[3];

	int lower_x, upper_x;

	rd_read_pixel(x, y, test_color);

	if (seed_color[0] == test_color[0] && seed_color[1] == test_color[1] && seed_color[2] == test_color[2]
		&& x >= 0 && x < display_xSize && y >= 0 && y < display_ySize)
	{
		rd_write_pixel(x, y, fg_color);

		int left_span_x = x - 1;

		rd_read_pixel(left_span_x, y, left_test_color);

		if (seed_color[0] != left_test_color[0] || seed_color[1] != left_test_color[1] || seed_color[2] != left_test_color[2])
			lower_x = x;

		while (seed_color[0] == left_test_color[0] && seed_color[1] == left_test_color[1] && seed_color[2] == left_test_color[2]
			&& left_span_x >= 0 && left_span_x < display_xSize)
		{
			rd_write_pixel(left_span_x, y, fg_color);

			left_span_x--;

			rd_read_pixel(left_span_x, y, left_test_color);

			if (seed_color[0] != left_test_color[0] || seed_color[1] != left_test_color[1] || seed_color[2] != left_test_color[2])
				lower_x = left_span_x + 1;
		}

		int right_span_x = x + 1;

		rd_read_pixel(right_span_x, y, right_test_color);

		if (seed_color[0] != right_test_color[0] || seed_color[1] != right_test_color[1] || seed_color[2] != right_test_color[2])
			upper_x = x;

		while (seed_color[0] == right_test_color[0] && seed_color[1] == right_test_color[1] && seed_color[2] == right_test_color[2]
			&& right_span_x >= 0 && right_span_x < display_xSize)
		{
			rd_write_pixel(right_span_x, y, fg_color);

			right_span_x++;

			rd_read_pixel(right_span_x, y, right_test_color);

			if (seed_color[0] != right_test_color[0] || seed_color[1] != right_test_color[1] || seed_color[2] != right_test_color[2])
				upper_x = right_span_x - 1;
		}

		for (left_span_x = x; left_span_x >= lower_x; left_span_x--)
		{
			if (y + 1 >= 0 && y + 1 < display_ySize)
			{
				rd_read_pixel(left_span_x, y + 1, up_test_color);

				if (seed_color[0] == up_test_color[0] && seed_color[1] == up_test_color[1] && seed_color[2] == up_test_color[2])
				{
					area_fill(left_span_x, y + 1);
				}
			}
		}

		for (left_span_x = x; left_span_x >= lower_x; left_span_x--)
		{
			if (y - 1 >= 0 && y - 1 < display_ySize)
			{
				rd_read_pixel(left_span_x, y - 1, down_test_color);

				if (seed_color[0] == down_test_color[0] && seed_color[1] == down_test_color[1] && seed_color[2] == down_test_color[2])
				{
					area_fill(left_span_x, y - 1);
				}
			}
		}

		for (right_span_x = x; right_span_x <= upper_x; right_span_x++)
		{
			if (y + 1 >= 0 && y + 1 < display_ySize)
			{
				rd_read_pixel(right_span_x, y + 1, up_test_color);

				if (seed_color[0] == up_test_color[0] && seed_color[1] == up_test_color[1] && seed_color[2] == up_test_color[2])
				{
					area_fill(right_span_x, y + 1);
				}
			}
		}

		for (right_span_x = x; right_span_x <= upper_x; right_span_x++)
		{
			if (y - 1 >= 0 && y - 1 < display_ySize)
			{
				rd_read_pixel(right_span_x, y - 1, down_test_color);

				if (seed_color[0] == down_test_color[0] && seed_color[1] == down_test_color[1] && seed_color[2] == down_test_color[2])
				{
					area_fill(right_span_x, y - 1);
				}
			}
		}
	}
}