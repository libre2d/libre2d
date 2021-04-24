#!/usr/bin/env python3

from PIL import Image
import sys

if len(sys.argv) < 3:
    print(f'Usage: {sys.argv[0]} <mode> <image>')
    print(f'  Extract green (#00ff00) points from image')
    print(f'  mode: gl|img')
    print(f'        - gl:  upper left corner is [-1, 1], y grows up, x grows right')
    print(f'        - img: upper left corner is [ 0, 0], y grows down, x grows right')
    exit()

mode = sys.argv[1]
im = Image.open(sys.argv[2])

pixels = im.load()
width, height = im.size

for y in range(0, height):
    for x in range(0, width):
        if pixels[x, y] == (0, 255, 0, 255):
            shifted_x = x - width / 2
            normalized_x_gl = '%.5f' % (shifted_x / (width / 2))
            shifted_y = height / 2 - y
            normalized_y_gl = '%.5f' % (shifted_y / (height / 2))

            normalized_x_img = '%.5f' % (x / width)
            normalized_y_img = '%.5f' % (y / height)

            if mode == 'gl':
                print(f'{normalized_x_gl}, {normalized_y_gl}, 0.0')
            elif mode == 'img':
                print(f'{normalized_x_img}, {normalized_y_img}')
