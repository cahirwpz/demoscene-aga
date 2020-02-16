#include <stdlib.h>

#include "libtxtproc_private.h"

tp_state_t *tp_state = NULL;

int tp_init(uint16_t width, uint16_t height, uint8_t regs)
{
	assert((width == 256) && (height == 256));

	if (tp_state == NULL) {

		tp_state = calloc(1, sizeof(tp_state_t) + regs * sizeof(layer_t));
		tp_state->width  = width;
		tp_state->height = height;
		tp_state->regs   = regs;

		int i;

		for (i = 0; i < regs; i++)
			TP_REG_LAYER(i) = calloc(1, width * height);

		return 1;
	}

	return 0;
}

void tp_cleanup()
{
	assert(tp_state != NULL);

	int i;

	for (i = 0; i < tp_state->regs; i++)
		free(TP_REG_LAYER(i));

	free(tp_state);

	tp_state = NULL;
}

void tp_get_texture_size(int16_t *width, int16_t *height)
{
	*width  = tp_state->width;
	*height = tp_state->height;
}

uint32_t tp_get_rgb_register_size()
{
	return tp_state->width * tp_state->height * 3;
}

void tp_load_rgb_register(uint8_t dst, uint8_t *buffer)
{
	int32_t i = 0;
	int16_t x, y;

	for (y = 0; y < TP_WIDTH; y++) {
		for (x = 0; x < TP_HEIGHT; x++) {
			colori_t c;

			c.r = buffer[i++];
			c.g = buffer[i++];
			c.b = buffer[i++];

			tp_reg_put_rgb_pixel(dst, x, y, &c);
		}
	}
}

void tp_save_rgb_register(uint8_t src, uint8_t *buffer)
{
	int32_t i = 0;
	int16_t x, y;

	for (y = 0; y < TP_WIDTH; y++) {
		for (x = 0; x < TP_HEIGHT; x++) {
			colori_t c;

			tp_reg_get_rgb_pixel(src, x, y, &c);

			buffer[i++] = c.r;
			buffer[i++] = c.g;
			buffer[i++] = c.b;
		}
	}
}

#if 0
void *wpz_texture_generate(uint8_t *mem)
{
	uint32_t picsize;

	if (wpz_texture_generate_init())
	{
		for(;;)
		{
			switch (mem[0])
			{
				case ITEM_END:
					ConvertTexture(layer[mem[1]]);
					wpz_texture_generate_kill();
					return picture;

					// Plasma(guint8_t layernr,guint8_t SinesX,guint8_t SinesY,guint8_t PhaseX,guint8_t PhaseY)
				case ITEM_PLASMA:
					Plasma(layer[mem[1]],mem[2],mem[3],mem[4],mem[5]);
					mem += SIZE_PLASMA;
					break;

					// SubPlasma(guint8_t layernr,guint8_t Step,guint16_t Seed,guint16_t RSeed)
				case ITEM_SUBPLASMA:
					SubPlasma(layer[mem[1]],mem[2],rw(*((uint16_t*)(mem+3))),rw(*((uint16_t*)(mem+5))));
					mem += SIZE_SUBPLASMA;
					break;

					// FractalPlasma(guint8_t layernr,guint16_t Seed,guint16_t RSeed)
				case ITEM_FRACTALPLASMA:
					FractalPlasma(layer[mem[1]],rw(*((uint16_t*)(mem+2))),rw(*((uint16_t*)(mem+4))));
					mem += SIZE_FRACTALPLASMA;
					break;

					// Light(guint8_t layernr,guint8_t Radius,guint8_t Type)
				case ITEM_LIGHT:
					Light(layer[mem[1]],mem[2],mem[3]);
					mem += SIZE_LIGHT;
					break;

					// Cells(guint8_t layernr,guint8_t Intensity,guint8_t Amount,guint16_t Seed, guint16_t RSeed)
				case ITEM_CELLS:
					Cells(layer[mem[1]],mem[2],mem[3],rw(*((uint16_t*)(mem+4))),rw(*((uint16_t*)(mem+6))));
					mem += SIZE_CELLS;
					break;

					// Picture(guint8_t layernr,guint8_t h,guint8_t w,guint8_t x,guint8_t y,guint8_t backcol,guint8_t datalayer)
				case ITEM_PICTURE:
					Picture(layer[mem[1]],mem[2],mem[3],mem[4],mem[5],(mem+6));
					picsize=(mem[2]+1)*(mem[3]+1);
					if ((picsize&7)!=0)
						picsize=(picsize>>3)+1;
					else
						picsize=(picsize>>3);
					mem += SIZE_PICTURE+picsize;
					break;

					// Clear(guint8_t layernr)
				case ITEM_CLEAR:
					Clear(layer[mem[1]]);
					mem += SIZE_CLEAR;
					break;

					// Sine(guint8_t layernr,guint8_t XSines,guint8_t YSines,guint8_t XAmp,guint8_t YAmp,guint8_t XShift,guint8_t YShift)
				case ITEM_SINE:
					Sine(layer[mem[1]],mem[2],mem[3],mem[4],mem[5],mem[6],mem[7]);
					mem += SIZE_SINE;
					break;

					// Twirl(guint8_t layernr,gint8_t Strenght)
				case ITEM_TWIRL:
					Twirl(layer[mem[1]],mem[2]);
					mem += SIZE_TWIRL;
					break;

					// Offset(guint8_t layernr,guint8_t XOffset,guint8_t YOffset)
				case ITEM_OFFSET:
					Offset(layer[mem[1]],mem[2],mem[3]);
					mem += SIZE_OFFSET;
					break;

					// Map(guint8_t layernr,guint8_t xlayernr,guint8_t ylayernr,guint8_t StrenghtX,guint8_t StrenghtY)
				case ITEM_MAP:
					Map(layer[mem[1]],layer[mem[2]],layer[mem[3]],mem[4],mem[5]);
					mem += SIZE_MAP;
					break;

					// HSV(guint8_t layernr,guint8_t Hue,guint8_t Saturation)
				case ITEM_HSV:
					HSV(layer[mem[1]],mem[2],mem[3]);
					mem += SIZE_HSV;
					break;

					// Invert(guint8_t layernr)
				case ITEM_INVERT:
					Invert(layer[mem[1]]);
					mem += SIZE_INVERT;
					break;

					// Emboss(guint8_t layernr)
				case ITEM_EMBOSS:
					Emboss(layer[mem[1]]);
					mem += SIZE_EMBOSS;
					break;

					// Bright(guint8_t layernr,guint8_t amount)
				case ITEM_BRIGHT:
					Bright(layer[mem[1]],mem[2]);
					mem += SIZE_BRIGHT;
					break;

					// SineColor(guint8_t layernr,guint8_t Sines)
				case ITEM_SINECOLOR:
					SineColor(layer[mem[1]],mem[2]);
					mem += SIZE_SINECOLOR;
					break;

					// Contrast(guint8_t layernr,guint8_t Cont)
				case ITEM_CONTRAST:
					Contrast(layer[mem[1]],mem[2]);
					mem += SIZE_CONTRAST;
					break;

					// Colorize(guint8_t layernr,guint8_t datalayernr,guint8_t R1,guint8_t B1,guint8_t G1,guint8_t R2,guint8_t B2,guint8_t G2)
				case ITEM_COLORIZE:
					Colorize(layer[mem[1]],layer[mem[2]],mem[3],mem[4],mem[5],mem[6],mem[7],mem[8]);
					mem += SIZE_COLORIZE;
					break;

					// Average(guint8_t layernr,guint8_t datalayernr)
				case ITEM_AVERAGE:
					Average(layer[mem[1]],layer[mem[2]]);
					mem += SIZE_AVERAGE;
					break;

					// LayersAdd(guint8_t destlayernr,guint8_t srclayernr)
				case ITEM_ADD:
					LayersAdd(layer[mem[1]],layer[mem[2]]);
					mem += SIZE_ADD;
					break;

					// LayersMul(guint8_t destlayernr,guint8_t srclayernr)
				case ITEM_MUL:
					LayersMul(layer[mem[1]],layer[mem[2]]);
					mem += SIZE_MUL;
					break;

					// LayersMix(guint8_t destlayernr,guint8_t srclayernr,guint8_t percent)
				case ITEM_MIX:
					LayersMix(layer[mem[1]],layer[mem[2]],mem[3]);
					mem += SIZE_MIX;
					break;

					// LayersCopy(guint8_t destlayernr,guint8_t srclayernr)
				case ITEM_COPY:
					LayersCopy(layer[mem[1]],layer[mem[2]]);
					mem += SIZE_COPY;
					break;

					// LayersExg(guint8_t destlayernr,guint8_t srclayernr)
				case ITEM_EXG:
					LayersExg(layer[mem[1]],layer[mem[2]]);
					mem += SIZE_EXG;
					break;

					// LayersMax(guint8_t destlayernr,guint8_t srclayernr)
				case ITEM_MAX:
					LayersMax(layer[mem[1]],layer[mem[2]]);
					mem += SIZE_MAX;
					break;

					// LayersShade(guint8_t destlayernr,guint8_t srclayernr)
				case ITEM_SHADE:
					LayersShade(layer[mem[1]],layer[mem[2]]);
					mem += SIZE_SHADE;
					break;

					// LayersMixmap(guint8_t destlayernr,guint8_t datalayer1nr,guint8_t datalayer2nr,guint8_t maplayernr)
				case ITEM_MIXMAP:
					LayersMixmap(layer[mem[1]],layer[mem[2]],layer[mem[3]],layer[mem[4]]);
					mem += SIZE_MIXMAP;
					break;

					// Blur(guint8_t layernr,guint8_t amount)
				case ITEM_BLUR:
					Blur(layer[mem[1]],mem[2]);
					mem += SIZE_BLUR;
					break;

					// DirectionalBlur(guint8_t layernr,guint8_t datalayernr,guint8_t Distance)
				case ITEM_DIRECTIONAL:
					DirectionalBlur(layer[mem[1]],layer[mem[2]],mem[3]);
					mem += SIZE_DIRECTIONAL;
					break;

				default:
					fprintf(stderr,"ERROR: WPZT: Texture corrupted.\n");
					wpz_texture_generate_kill();
					free(picture);
					return NULL;
			}
		}
		wpz_texture_generate_kill();
		free(picture);
	}
	else
	{
		fprintf(stderr,"ERROR: WPZT: No memory for generating texture.\n");
	}

	return NULL;
}
#endif
