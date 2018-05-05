#include "pnm_display.h"
#include "rd_display.h"
#include "rd_direct.h"
#include "rd_error.h"
#include "rd_enginebase.h"
#include <fstream>
#include <iostream>

int pnm_init_display(void)
{
	display_image = new int*[display_ySize];	
	
	for(int i = 0; i < display_ySize; i++)
	{
		display_image[i] = new int[display_xSize * 3];
	}

	return RD_OK;
}

int pnm_end_display(void)
{
	for (int i = 0; i < display_ySize; i++) 
	{
		delete[] display_image[i];
	}
	delete[] display_image;

	return RD_OK;
}

int pnm_init_frame(int frame_no)
{
	pnm_clear();

	return RD_OK;
}

int pnm_end_frame(void)
{
	string new_file = display_name;

	new_file.append(std::to_string(glbl_frame));

	new_file.append(".ppm");

	std::ofstream write_to_pnm;
	
	write_to_pnm.open(new_file);

	write_to_pnm << "P3\n" << display_xSize << " " << display_ySize << "\n255\n";

	for (int i = 0; i < display_ySize; i++)
	{
		for (int j = 0; j < display_xSize * 3; j++)
		{
			write_to_pnm << display_image[i][j];

			write_to_pnm << " ";
		}
	}

	write_to_pnm.close();

	return RD_OK;
}

int pnm_write_pixel(int x, int y, const float rgb [])
{
	float temp;

	temp = rgb[0] * 255.0;
	display_image[y][3 * x] = (int)temp;

	temp = rgb[1] * 255.0;
	display_image[y][3 * x + 1] = (int)temp;

	temp = rgb[2] * 255.0;
	display_image[y][3 * x + 2] = (int)temp;
	
	return RD_OK;
}

int pnm_read_pixel(int x, int y, float rgb[])
{
	float temp;

	temp = (float)display_image[y][3 * x] / 255.0;
	rgb[0] = temp;

	temp = (float)display_image[y][3 * x + 1] / 255.0;
	rgb[1] = temp;

	temp = (float)display_image[y][3 * x + 2] / 255.0;
	rgb[2] = temp;

	return RD_OK;
}

int pnm_set_background(const float rgb[])
{
	bg_color[0] = rgb[0];
	bg_color[1] = rgb[1];
	bg_color[2] = rgb[2];

	return RD_OK;
}

int pnm_clear(void)
{
	for (int i = 0; i < display_ySize; i++)
	{
		for (int j = 0; j < display_xSize * 3; j += 3)
		{
			float temp;

			temp = bg_color[0] * 255.0;
			display_image[i][j] = (int)temp;

			temp = bg_color[1] * 255.0;
			display_image[i][j + 1] = (int)temp;

			temp = bg_color[2] * 255.0;
			display_image[i][j + 2] = (int)temp;
		}
	}

	return RD_OK;
}