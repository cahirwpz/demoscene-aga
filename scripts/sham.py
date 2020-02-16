#!/usr/bin/env python -B

import Image

if __name__ == '__main__':
  image = Image.open('sham-in.png').convert('RGB')
  output = Image.new('RGB', image.size)

  width, height = image.size

  src = image.load()
  dst = output.load()

  # Convert to Amiga 500 colorspace
  for y in range(height):
    for x in range(width):
      r, g, b = src[x, y]
      nr = (r + 8) / 17
      ng = (g + 8) / 17
      nb = (b + 8) / 17
      dst[x, y] = (nr, ng, nb)

  pr, pg, pb = dst[0, 0]

  print (pr, pg, pb)

  l = []

  for x in range(1, width):
    r, g, b = dst[x, y]
    er, eg, eb = abs(r - pr), abs(g - pg), abs(b - pb)
    e = sum([er, eg, eb])
    c = sum(map(bool, [er, eg, eb]))
    pr, pg, pb = dst[x, y]
    if c > 1:
      l.append((e, x))

  print sorted(l), len(l)

  # Convert from Amiga 500 colorspace
  for y in range(height):
    for x in range(width):
      r, g, b = dst[x, y]
      nr = (r << 4) | r
      ng = (g << 4) | g
      nb = (b << 4) | b
      dst[x, y] = (nr, ng, nb)

  #output.show()
  #output.save('sham-out.png')
