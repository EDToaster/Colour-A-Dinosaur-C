#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>
#include <stdint.h>

#define MALLOC_ERR_IMAGE 1
#define INDEX_OUT_OF_RANGE 2

/* Defines a struct image with width height and image data */
typedef struct IMAGE {

  uint8_t	width;
  uint8_t	height;
  uint8_t	_data[];

} image;

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

void assert_image_dims(image* im, uint8_t x, uint8_t y){
  if(x >= im -> width || y >= im -> height) { perror("Index out of range"); exit(INDEX_OUT_OF_RANGE); }
}

uint16_t xy_to_ind(image* im, uint8_t x, uint8_t y) {
  return x + y * im -> width;
}

bool check_flood_valid(image* im, uint16_t x, uint16_t y, uint8_t target, bool* targets){

  if(x >= im -> width || y >= im -> height) return false;

  uint16_t ind = xy_to_ind(im, x, y);
  if(targets[ind]) return false;

  targets[ind] = true;
  return im -> _data[ind] == target;
}

void set_pix(image* im, uint8_t x, uint8_t y, uint8_t fill) {
  assert_image_dims(im, x, y);

  unsigned ind = x + y * im -> width;
  im -> _data[ind] = fill;

}


void _rec_fill(image* im, uint8_t x, uint8_t y, uint8_t fill, uint8_t target, bool* targets){
  uint16_t ind = xy_to_ind(im, x, y);

  if (check_flood_valid(im, x, y, target, targets)) im -> _data[ind] = fill;
  else return;

  // prevent over-under-flow
  if(x != 0xFF)
    _rec_fill(im, x + 1, y, fill, target, targets);
  if(x != 0x00)
    _rec_fill(im, x - 1, y, fill, target, targets);
  if(y != 0xFF)
    _rec_fill(im, x, y + 1, fill, target, targets);
  if(y != 0x00)
    _rec_fill(im, x, y - 1, fill, target, targets);
}

void fill_buc(image* im, uint8_t x, uint8_t y, uint8_t fill) {

  uint16_t i_size = im -> width * im -> height;

  bool* targets = malloc(i_size * sizeof(bool));

  _rec_fill(im, x, y, fill, im -> _data[xy_to_ind(im, x, y)], targets);
}



int main() {

  setlocale(LC_ALL, "");

  image* im = create_image(0x20, 0x20, 0x00);

  for(unsigned i = 0; i < im -> width; i++){
    set_pix(im, i, im -> height - 1 - i, 0x44);
    set_pix(im, i, i, 0x44);
  }

  fill_buc(im, 5, 0, 0xFF);

  for(unsigned j = 0; j < im -> height; j++) {
    for(unsigned i = 0; i < im -> width; i++) {
      unsigned ind = xy_to_ind(im, i, j);
      printf("%lc", (wint_t) (im -> _data[ind] + 0x2800));
    }
    printf("\n");
  }


  return 0;
}
