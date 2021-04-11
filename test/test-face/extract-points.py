#!/usr/bin/env python3

from PIL import Image
import sys

if len(sys.argv) < 2:
    print(f'Usage: {sys.argv[0]} <image>')
    print(f'  Extract green (#00ff00) points from image')
    exit()

im = Image.open(sys.argv[1])

pixels = im.load()
width, height = im.size

for y in range(0, height):
    for x in range(0, width):
        if pixels[x, y] == (0, 255, 0, 255):
            shifted_x = x - width / 2
            normalized_x = '%.5f' % (shifted_x / (width / 2))
            shifted_y = height / 2 - y
            normalized_y = '%.5f' % (shifted_y / (height / 2))
            print(f'{normalized_x}, {normalized_y}, 0.0')
