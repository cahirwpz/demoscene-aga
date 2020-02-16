void RGB2HSV(float r, float g, float b, float *h, float *s, float *v)
{
  float t1 = r;
  float t2 = g;
  float t3 = b;
  float tt, hi, lo, diff;

  if (t1 > t2) {
    tt = t1; t1 = t2; t2 = tt;
  }

  if (t1 > t3) {
    tt = t1; t1 = t3; t3 = tt;
  }

  if (t2 > t3) {
    tt = t2; t2 = t3; t3 = tt;
  }

  hi = t3;
  lo = t1;
  diff = hi - lo;

  *v = hi;
  *s = (hi == 0.0f) ? 0.0f : (diff / hi);

  if (*s != 0.0f) {
    if (r == hi) {
      *h = (g - b) / diff;
    } else {
      if (g == hi) {
        *h = 2.0 + (b - r) / diff;
      } else {
        *h = 4.0 + (r - g) / diff;
      }
    }

    *h /= 6.0f;

    if (*h < 0.0f)
      *h += 1.0f;
  } else {
    *h = 0.0f;
  }

}

void HSV2RGB(float *r, float *g, float *b, float h, float s, float v)
{
  if (s == 0.0f) {
    *r = v;
    *g = v;
    *b = v;
  } else {
    if (h == 1.0f)
      h = 0.0f;

    h *= 6.0f;

    {
      float hi = truncf(h);
      float hf = h - hi;

      float p = v * (1.0f - s);
      float q = v * (1.0f - s * hf);
      float t = v * (1.0f - s * (1.0f - hf));

      switch ((int)hi) {
        case 0:
          *r = v;
          *g = t;
          *b = p;
          break;

        case 1:
          *r = q;
          *g = v;
          *b = p;
          break;

        case 2:
          *r = p;
          *g = v;
          *b = t;
          break;

        case 3:
          *r = p;
          *g = q;
          *b = v;
          break;

        case 4:
          *r = t;
          *g = p;
          *b = v;
          break;

        case 5:
          *r = v;
          *g = p;
          *b = q;
          break;
      }
    }
  }
}
