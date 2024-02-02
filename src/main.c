#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../stb/stb_image.h"
#include "../stb/stb_image_write.h"
#include  <unistd.h>

#define ARRLEN 22
#define WRATIO 6
#define HRATIO 8

char arr[] = " .,'\":;!-+=>i|lOPMX$#@";

void make_grey(unsigned char *img, int width, int height)
{
	int				grey;
	unsigned char	*data;

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			data = img + (j * width + i) * 3;
			grey = 0.299 * data[0] + 0.587 * data[1] + 0.114 * data[2];
			data[0] = grey;
			data[1] = grey;
			data[2] = grey;
		}
}
int get_WHratio_grey(unsigned char *img, int width, int height, int x, int y)
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

int main(int ac, char **av) {
	int				width, height, channels, owidth, oheight, newlines = 0;
	unsigned char	*img;
	char			*output;

	if (ac < 2)
		return (printf("Program requires input!"), 1);
	img = stbi_load(av[1], &width, &height, &channels, 3);
	if (!img)
		return (printf("image could not be loaded\nReason : %s", stbi_failure_reason()), stbi_image_free(img), 1);
	make_grey(img, width, height);
	owidth = width / WRATIO;
	oheight = height / HRATIO;
	output = malloc((owidth + 1) * oheight + 1);
	for (int j = 0; j < oheight; j++)
		for (int i = 0; i < owidth; i++)
		{
			int tmp = get_WHratio_grey(img, width, height, i * WRATIO, j * HRATIO);
			output[j * (owidth + 1) + i] = arr[tmp * ARRLEN / 256];
			if (i == owidth - 1)
			{
				output[j * (owidth + 1) + i + 1] = '\n';
				newlines++;
			}
			/*printf("%c", arr[tmp * ARRLEN / 256]);
			if (i == width / WRATIO - 1)
				printf("\n");*/
		}
	for (int i = 0; i < newlines; i++)
		printf("\x1b[A");
	output[oheight * (owidth + 1)] = '\0';
	write(1, output, oheight * (owidth + 1));
	free(output);
	stbi_image_free(img);
    return 0;
}
