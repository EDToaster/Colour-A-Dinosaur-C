#include <stdint.h>

typedef struct IMAGE {
	uint8_t width;
	uint8_t height;
	uint8_t _data[];
} image;


extern image* create_image(uint8_t width, uint8_t height, uint8_t fill);

extern uint16_t xy_to_ind(image* im, uint8_t x, uint8_t y);

extern void set_pix(image* im, uint8_t x, uint8_t y, uint8_t fill);

extern void fill_buc(image* im, uint8_t x, uint8_t y, uint8_t fill);
