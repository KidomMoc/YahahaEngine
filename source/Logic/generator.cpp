#include "generator.hpp"
#include "Core/Asset/AssetTypes.hpp"
#include "Core/Asset/AssetManager.hpp"
#include <stdio.h>
#include <libpng/png.h>

namespace KFTG
{

void generateData ()
{
	Image *background;
	u32 size_background = readImg ("background.png", background);
	Image *img1;
	u32 size_img1 = readImg ("img.png", img1);
	Image *img2;
	u32 size_img2 = readImg ("img.png", img2);
	Image *img3;
	u32 size_img3 = readImg ("img.png", img3);
	u32 size_ani1 = sizeof (Animation) + 2 * sizeof (Animation::Clip);
	Animation *ani1 = (Animation*) new char[size_ani1];
	ani1->len = 2;
	ani1->ani[0].img = img1;
	ani1->ani[0].time = 400;
	ani1->ani[1].img = img2;
	ani1->ani[1].time = 400;
	u32 size_ani2 = sizeof (Animation) + 2 * sizeof (Animation::Clip);
	Animation *ani2 = (Animation*) new char[size_ani2];
	ani1->len = 2;
	ani1->ani[0].img = img1;
	ani1->ani[0].time = 250;
	ani1->ani[1].img = img3;
	ani1->ani[1].time = 250;
	u32 size_ani3 = sizeof (Animation) + 1 * sizeof (Animation::Clip);
	Animation *ani3 = (Animation*) new char[size_ani3];
	ani1->len = 1;
	ani1->ani[0].img = img3;
	ani1->ani[0].time = 1000;
}

u32 readImg (const char *path, Image *img)
{
	char header[8];
	png_structp png_ptr;
	png_infop info_ptr;
	u32 width, height;
	png_bytep *row_pointers;
	png_byte color_type;
	FILE *fp = fopen (path, "rb");
	fread (header, 1, 8, fp);
	png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct (png_ptr);
	png_init_io (png_ptr, fp);
	png_set_sig_bytes (png_ptr, 8);
	png_read_info (png_ptr, info_ptr);
	color_type = png_get_color_type (png_ptr, info_ptr);
	width = png_get_image_width (png_ptr, info_ptr);
	height = png_get_image_height (png_ptr, info_ptr);
	img = (Image*) new char[sizeof (Image) + width * height * sizeof (Color)];
	img->width = width;
	img->height = height;
	row_pointers = (png_bytep*) new char[sizeof (png_bytep) * height];
	for (u16 i = 0; i < height; ++i)
		row_pointers[i] = (png_byte*) new char [png_get_rowbytes (png_ptr, info_ptr)];
	png_read_image (png_ptr, row_pointers);
	for (u16 i = 0; i < height; ++i)
		for (u16 j = 0; j < width; ++j)
			img->image[i * height + j] = Color (row_pointers[i][j * 4], row_pointers[i][j * 4 + 1], row_pointers[i][j * 4 + 2], color_type == PNG_COLOR_TYPE_RGBA ? row_pointers[i][j * 4 + 0] : 255);
	for (u16 i = 0; i < height; ++i)
		delete[] row_pointers[i];
	delete[] row_pointers;
	fclose (fp);
	return sizeof (Color) * width * height;
}

}