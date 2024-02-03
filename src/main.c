#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../stb/stb_image.h"
#include "../stb/stb_image_write.h"
#include  <unistd.h>

#define ARRLEN 22
#define WRATIO 3
#define HRATIO 4

char	arr[] = " .,'\":;!-+=>i|lOPMX$#@";
char	colors[][7] = {
	"\x1b[30m ",
	"\x1b[34m ",
	"\x1b[32m ",
	"\x1b[36m ",
	"\x1b[31m ",
	"\x1b[35m ",
	"\x1b[33m ",
	"\x1b[37m "
};

enum	mycolors{
	black,
	blue,
	green,
	cyan,
	red,
	magenta,
	yellow,
	white
};

void make_grey(unsigned char *img, int width, int height)
{
	int				grey;
	unsigned char	*data;

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			data = img + (j * width + i) * 3;
			grey = 0.299 * data[0] + 0.587 * data[1] + 0.114 * data[2];//getting the greyscale of each pixel
			data[0] = grey;
			data[1] = grey;
			data[2] = grey;
		}
}

int get_WHratio_grey(unsigned char *img, int width, int height, int x, int y)//getting the average grey scale of collective pixels
{
	int grey = 0;
	
	if (x < 0 || (x >= width - WRATIO) || y < 0 || (y >= height - HRATIO))
		return (0);
	for (int i = x; i < x + WRATIO; i++)
		for (int j = y; j < y + HRATIO; j++)
			grey += img[(j * width + i) * 3];
	grey /= WRATIO * HRATIO;
	return (grey);
}

enum mycolors get_WHratio_rgb(unsigned char *img, int width, int height, int x, int y)//getting the average rgb value per pixelsdivided by 128 to narrow number of colors to 8
{
	int				r = 0;
	int				g = 0;
	int				b = 0;
	unsigned char	*data;
	
	if (x < 0 || (x >= width - WRATIO) || y < 0 || (y >= height - HRATIO))
		return (0);
	for (int i = x; i < x + WRATIO; i++)
		for (int j = y; j < y + HRATIO; j++)
		{
			data = img + (j * width + i) * 3;
			r += data[0];
			g += data[1];
			b += data[2];
		}
	r /= WRATIO * HRATIO * 128;
	g /= WRATIO * HRATIO * 128;
	b /= WRATIO * HRATIO * 128;
	return ((r << 2) + (g << 1) + b);
}

unsigned char	*get_colors(unsigned char *img, int width, int height)
{
	unsigned char	*res;
	int				owidth, oheight;

	owidth = width / WRATIO;
	oheight = height / HRATIO;
	res = malloc(owidth * oheight);
	if (!res)
		return (0);
	for (int i = 0; i < owidth; i++)
		for (int j = 0; j < oheight; j++)
		{
			enum mycolors tmp2 = get_WHratio_rgb(img, width, height, i * WRATIO, j * HRATIO);
			res[j * owidth + i] = tmp2;
		}
	return (res);
}

int main(int ac, char **av) {
	int				width, height, channels, owidth, oheight, newlines = 0;
	unsigned char	*img, *output_colors, *output;

	if (ac < 2)
		return (printf("Program requires input!"), 1);
	img = stbi_load(av[1], &width, &height, &channels, 3);
	if (!img)
		return (printf("image could not be loaded\nReason : %s", stbi_failure_reason()),
			   stbi_image_free(img), 1);
	output_colors = get_colors(img, width, height);
	if (!output_colors)
		return (1);
	make_grey(img, width, height);
	owidth = width / WRATIO;
	oheight = height / HRATIO;
	output = malloc(oheight * (owidth * 6 + 1) + 1);
	*output = 0;
	for (int j = 0; j < oheight; j++)
		for (int i = 0; i < owidth; i++)
		{
			int tmp = get_WHratio_grey(img, width, height, i * WRATIO, j * HRATIO);
			int index = j * owidth + i;
			colors[output_colors[index]][5] = arr[tmp * ARRLEN / 256];
			strcat((char *)output + index, colors[output_colors[index]]);
			if (i == owidth - 1)
			{
				strcat((char *)output + index, "\n");
				newlines++;
			}
		}
	printf("%s", output);
	if (ac > 2)
		for (int i = 0; i < newlines; i++)
			printf("\x1b[A");				//this is for printing from the same position to avoid clearing the terminal
	printf("%s", colors[7]);				//this is for getting the terminal back to it's original color
	free(output);
	free(output_colors);
	stbi_image_free(img);
    return 0;
}
