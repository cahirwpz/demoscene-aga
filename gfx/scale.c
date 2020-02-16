void ScaleLine(uint8_t *dst, int x1, int x2, uint8_t *src, int u1, int u2) {
  /* u1 < u2 always holds */

  const int dx = abs(x2 - x1);
  const int sx = sign(x2 - x1);
  const int du = u2 - u1;
  const int dx2 = 2 * dx;

  int e = 2 * du - dx;
  int i;

  for (i = 0; i <= dx; i++) {
    dst[x1] = src[u1];

    while (e >= 0) {
      u1++;
      e -= dx2;
    }

    x1 += sx;
    e += du;
  }
}

