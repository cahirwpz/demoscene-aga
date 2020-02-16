
void tp_op_generate_light(uint8_t dst, uint8_t type, float radius)
{
	int16_t x, y;

	float s = 3.0f - radius;

	for (y = 0; y < TP_HEIGHT; y++) {
		for (x = 0; x < TP_WIDTH; x++) {
			float r = sqrtf((float)((x - 128) * (x - 128) + (y - 128) * (y - 128))) * s;

			int v;

			if (type == 0) {
				v = 255 - (int)r;
			} else {
				if (type == 1) {
					if (r == 0.0)
					   	r = 0.01;

					v = (int)(255.0f * log(r / 128.0f) / log(0.1f));
				} else {
					v = (int)(259.75f * exp(-r * r / 16384.0f) - 4.75f);
				}
			}

			tp_reg_put_pixel(dst, x, y, v);
		}
	}
}



#if 0
void generate_cells(layer_t dst, uint8_t intens, uint8_t amount, uint16_t seed, uint16_t rseed)
{
	layer_t tmp;
	int16_t v,r;
	int32_t x,y,i,a,as,ai,xs,ys;
	float s,fr;

	Clear(dst);
	tmp = layer[12];

	s=sqrt(amount)*(2-(float)(intens)/256);

	for (y=0,i=0;y<256;y++)
		for (x=0;x<256;x++,i++)
		{
			fr=sqrt((float)((x-128)*(x-128)+(y-128)*(y-128)))*s;
			v=(int16_t)(259.75*exp(-fr*fr/16/4096)-4.75);
			if (v<0) v=0;
			tmp[i]=v;
		}

	as=0x10000/amount;

	for (a=0,ai=seed;a<amount*2;a+=2,ai+=as+seed)
	{
		Random(&seed,rseed);
		xs=(ai&0xff)-127+((seed&31)-16);
		Random(&seed,rseed);
		ys=((ai>>8)&0xff)-127+((seed&31)-16);
		for (y=0,i=0;y<256;y++) {
			for (x=0;x<256;x++,i++) {
				v=dst[i];
				r=GetPix(tmp,x+xs,y+ys);
				if (v>r) v-=r;
				if (v<r) v=r;
				if (v>255) v=255;
				dst[i]=v;
			}
		}
	}

	for (i=0;i<0x10000;i++) dst[i]=~dst[i];
}
#endif

#if 0
void insert_bitmap(layer_t dst, uint8_t w, uint8_t h, uint8_t x, uint8_t y, uint8_t *data)
{
	uint8_t ppix,p;
	int8_t  bpos;
	int32_t j, xi, yi;

	Clear(dst);

	for (yi=0,j=0,bpos=-1,ppix=0;yi<=h;yi++) {
		for (xi=0;xi<=w;xi++,bpos--)
		{
			if (bpos<0)
			{
				bpos=7;
				ppix=data[j++];
			}
			p = (ppix&(1<<bpos)) ? 0xff : 0x00;
			PutPix(dst,x+xi,y+yi,p);
		}
	}
}
#endif
