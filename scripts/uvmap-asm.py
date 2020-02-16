#!/usr/bin/env python

import Image
import argparse
import os
from array import array


def main():
  parser = argparse.ArgumentParser(
      description='Assemble uvmap from two grayscale images.')
  parser.add_argument(
    '-k', '--kind', type=str, choices=['16c', 'rgb'], default='16c',
    help='which effect variant will use this uvmap?')
  parser.add_argument(
    '-s', '--size', type=int, choices=[64, 128, 256], default=128,
    help='generate uvmap for given texture size (N x N)')
  parser.add_argument(
    'umap', metavar='umap-img', type=str,
    help='input grayscale image with U coordinates')
  parser.add_argument(
    'vmap', metavar='vmap-img', type=str,
    help='input grayscale image with V coordinates')
  parser.add_argument(
    'uvmap', metavar='uvmap-bin', type=str,
    help='output binary file with UV map')
  args = parser.parse_args()

  maps = []

  for path in [args.umap, args.vmap]:
    if not os.path.isfile(path):
      raise SystemExit('File "%s" does not exists!' % path)

    img = Image.open(path)

    if img.mode != 'L':
      raise SystemExit('File "%s" is not a grayscale image!' % path)

    maps.append(img)

  umap, vmap = maps

  if len(umap.size) != len(vmap.size):
    raise SystemExit("Images size mismatch (%s vs. %s)!", umap.size, vmap.size)

  shift = {256: 0, 128: 1, 64: 2}.get(args.size)

  with open(args.uvmap, 'w') as f:
    uvmap = array("H")
    out = array("H")

    for u, v in zip(umap.getdata(), vmap.getdata()):
      u = u >> shift
      v = v >> shift
      uvmap.append(u * args.size + v)

    if args.kind == 'rgb':
      for uv in uvmap:
        out.append(uv * 2)
    elif args.kind == '16c':
      for i in range(0, len(uvmap), 8):
        out.append(uvmap[i + 0])
        out.append(uvmap[i + 1])
        out.append(uvmap[i + 4])
        out.append(uvmap[i + 5])
        out.append(uvmap[i + 2])
        out.append(uvmap[i + 3])
        out.append(uvmap[i + 6])
        out.append(uvmap[i + 7])

    out.byteswap()
    out.tofile(f)


if __name__ == '__main__':
  main()
