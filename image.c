#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#include "image.h"

#define MALLOC_ERR_IMAGE 1
#define INDEX_OUT_OF_RANGE 2

/* Helper to create the image */
image* create_image(uint8_t width, uint8_t height, uint8_t fill) {

	uint16_t i_size = width * height;

	image* i = malloc(sizeof(image) + i_size * sizeof(uint8_t));
	if(!i) { perror("Malloc Err Image"); exit(MALLOC_ERR_IMAGE); }

	i -> width = width;
	i -> height = height;

	for(unsigned ind = 0; ind < i_size; ind++) {
		i -> _data[ind] = fill;
	}

	return i;
}

/* convert x and y to image indices */
uint16_t xy_to_ind(image* im, uint8_t x, uint8_t y) {
	return x + y * im -> width;
}

/* sets pixel */
void set_pix(image* im, uint8_t x, uint8_t y, uint8_t fill) {

	unsigned ind = x + y * im -> width;
	im -> _data[ind] = fill;

}

/* recursively fills itself and all connected squares of target colour */
void _rec_fill(image* im, uint8_t x, uint8_t y, uint8_t fill, uint8_t target){
	uint16_t ind = xy_to_ind(im, x, y);

	if(x >= im -> width || y >= im -> height) return;

  if(target == fill) return;
  if(im -> _data[ind] != target) return;

  im -> _data[ind] = fill;


	// prevent over-under-flow
	if(x != 0xFF)
		_rec_fill(im, x + 1, y, fill, target);
	if(x != 0x00)
		_rec_fill(im, x - 1, y, fill, target);
	if(y != 0xFF)
		_rec_fill(im, x, y + 1, fill, target);
	if(y != 0x00)
		_rec_fill(im, x, y - 1, fill, target);
}

/* fills the selected pixel using the fill bucket */
void fill_buc(image* im, uint8_t x, uint8_t y, uint8_t fill) {
	_rec_fill(im, x, y, fill, im -> _data[xy_to_ind(im, x, y)]);
}


