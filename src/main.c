#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../stb/stb_image.h"
#include "../stb/stb_image_write.h"
#define ARRLEN 17
#define WRATIO 6
#define HRATIO 8
char arr[] = ".,\"!;:-+=<>i|l$#@";

void make_grey(unsigned char *img, int width, int height)
{
	int grey;
	unsigned char *data;
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
int get_6By8_grey(unsigned char *img, int width, int height, int x, int y, int channels)
{
	int grey = 0;
	
	if (x < 0 || (x >= width - WRATIO) || y < 0 || (y >= height - HRATIO))
		return (0);
	for (int i = x; i < x + WRATIO; i++)
		for (int j = y; j < y + HRATIO; j++)
			grey += img[(j * width + i) * channels];
	grey /= WRATIO * HRATIO;
	return (grey);
}

int main(int ac, char **av) {
	int width, height, channels;
	unsigned char *img;

	if (ac < 2)
		return (printf("Program requires input!"), 1);
	img = stbi_load(av[1], &width, &height, &channels, 3);
	if (!img)
		return (printf("image could not be loaded\nReason : %s", stbi_failure_reason()), stbi_image_free(img), 1);
	make_grey(img, width, height);
	for (int j = 0; j < height / HRATIO; j++)
		for (int i = 0; i < width / WRATIO; i++)
		{
			//printf("w = %d, h = %d, i = %3d, ir = %3d, j = %3d, jr = %3d, channels = %d\n", width, height, i, i * WRATIO, j, j * HRATIO, channels);
			int tmp = get_6By8_grey(img, width, height, i * WRATIO, j * HRATIO, 3);
			printf("%c", arr[tmp * ARRLEN / 256]);
			if (i == width / WRATIO - 1)
				printf("\n");
		}
	stbi_image_free(img);
    return 0;
}
