#!/usr/bin/env python

import struct
from collections import namedtuple

Header = namedtuple("TiffHeader", "endianness id ifd")
Entry = namedtuple("IFDEntry", "tag type count value")

tagmap = {
  262: 'PhotometricInterpretation',
  259: 'Compression',
  257: 'ImageLength',
  256: 'ImageWidth',
  258: 'BitsPerSample',
  296: 'ResolutionUnit',
  282: 'XResolution',
  283: 'YResolution',
  278: 'RowsPerStrip',
  273: 'StripOffsets',
  279: 'StripByteCounts',
  266: 'FillOrder',
  274: 'Orientation',
  277: 'SamplesPerPixel',
  284: 'PlanarConfiguration',
  297: 'PageNumber',
  318: 'WhitePoint',
  319: 'PrimaryChromaticities',
  320: 'ColorMap'
}

typmap = {
  1: 'BYTE',
  2: 'CHAR',
  3: 'WORD',
  4: 'LONG',
  5: 'RATIONAL'
}

valmap = {
  'BYTE': ('B', 1),
  'CHAR': ('c', 1),
  'WORD': ('H', 2),
  'LONG': ('I', 4),
  'RATIONAL': ('Q', 8)
}

with open("img-16.tiff") as tga:
  header = Header(*struct.unpack("2sHI", tga.read(8)))
  tga.seek(header.ifd)
  entry_count = struct.unpack("H", tga.read(2))[0]
  entries = []
  for i in range(entry_count):
    tag, typ, count, value = struct.unpack("HHII", tga.read(12))
    tag = tagmap.get(tag, '?')
    typ = typmap.get(typ, '?')
    entries.append(Entry(tag, typ, count, value))
  for entry in entries:
    print entry
    a, b = valmap[entry.type]
    if b * entry.count > 4:
      tga.seek(entry.value, 0)
      print struct.unpack(a * entry.count, tga.read(b * entry.count))
