/**
 * @param r_dst		destination (register number)
 * @param r_src		source (register number)
 * @param bu_sines	number of sine cycles (unsigned byte [2, 32])
 */

static int16_t tp_tab[256];

void tp_op_colors_sine_color(uint8_t r_dst, uint8_t r_src, uint8_t bu_sines)
{
	int i;

	for (i = 0; i < 256; i++)
	   	tp_tab[i] = 127 - (int16_t)(sinf(i / 256.0f * bu_sines * M_2_PI) * 127.0f) + 127;

	int16_t x, y;

	for (y = 0; y < TP_HEIGHT; y++)
		for (x = 0; x < TP_WIDTH; x++)
			tp_reg_put_pixel(r_dst, x, y, tp_tab[tp_reg_get_pixel(r_src, x, y)]);
}

/**
 * @param r_dst		destination (RGB register number)
 * @param r_src		source (register number)
 * @param c_c1		first color (RGB color)
 * @param c_c2		second color (RGB color)
 */

void ColorsColorize(uint8_t dst, uint8_t src, color_t c_c1, color_t c_c2)
{
	colori_t d = { c_c2.r - c_c1.r, c_c2.g - c_c1.g, c_c2.b - c_c1.b };

	int16_t x, y;

	for (y = 0; y < TP_HEIGHT; y++) {
		for (x = 0; x < TP_WIDTH; x++) {
			int16_t p = tp_reg_get_pixel(src, x, y);

			colori_t c;

			c.r = ((d.r * p) >> 8) + c_c1.r;
			c.g = ((d.g * p) >> 8) + c_c1.g;
			c.b = ((d.b * p) >> 8) + c_c2.b;

			tp_reg_put_rgb_pixel(dst, x, y, &c);
		}
	}
}
