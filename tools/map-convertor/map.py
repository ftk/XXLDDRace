from __future__ import print_function

from tml.tml import Teemap
from tml.items import Group, TileLayer, Tile

import Image

import sys

def map2img(layer):
  img = Image.new("RGB", (layer.width, layer.height))
  for y in range(0, layer.height):
    for x in range(0, layer.width):
      idx = layer.get_tile(x, y).index
      img.putpixel((x,y), (idx, idx, idx))
  return img
#

class RGBTile:
  air = (255, 255, 255)
  block = (0, 0, 255)
  blocknohook = (0, 0, 0)
  freeze = (128, 128, 128)
  unfreeze = (192, 192, 192)
  start = (0, 192, 0)
  end = (0, 64, 0)
  spawn = (255, 255, 0)
  kill = (255, 0, 0)

# 0x56 = tile at 5th row and 6th column in tileset
color_to_tile = dict(
{
  # (r, g, b) : [game, tile]
  RGBTile.air : [0x00, 0x00], # air
  
  RGBTile.block : [0x01, 0x11], # block (hook?)
  RGBTile.blocknohook : [0x03, 0x18], # block (unhook?)
  
  RGBTile.freeze : [0x9, 0x1f], # freeze
  RGBTile.unfreeze : [0xb, 0x0e], # unfreeze
  
  RGBTile.start : [0x21, 0x0e], # start
  RGBTile.end : [0x22, 0x0e], # end
  RGBTile.spawn : [0xc0, 0x00], # spawn
  RGBTile.kill : [0x2, 0x1e], # kill
  
  (1,2,3) : [0x15, 0x0e], # solo in
  (4,5,6) : [0x16, 0x0e] # solo out
  # TODO: add more
})


def rgb2game(rgb):
  if rgb in color_to_tile.keys():
    return color_to_tile[rgb][0]
  else:
    print("no matching color %02x%02x%02x" % rgb)
    return 0
#
def rgb2tile(rgb):
  #print(color_to_tile[rgb][1])
  if rgb in color_to_tile.keys():
    return color_to_tile[rgb][1]
  else:
    return 0
#
def img2map(img, gamelayer, tilelayer):
  width, height = img.size
  
  tilelayer.width = gamelayer.width = width
  tilelayer.height = gamelayer.height = height

  
  for y in range(0, height):
    for x in range(0, width):
      rgb = img.getpixel((x, y))
      
      tileidx = rgb2tile(rgb)
      gameidx = rgb2game(rgb)
      
      t = Tile()
      t.index = tileidx
      
      tilelayer.set_tile(x, y, t)
      t.index = gameidx
      gamelayer.set_tile(x, y, t)
#


# symbol : color
txt_to_color = dict(
{
  ' ' : RGBTile.air,
  'X' : RGBTile.blocknohook,
  'O' : RGBTile.block,
  'S' : RGBTile.spawn,
  's' : RGBTile.start,
  'e' : RGBTile.end,
  '-' : RGBTile.freeze,
  '.' : RGBTile.unfreeze
})

def txt2rgb(ch):
  return txt_to_color[ch]


def txt2map(txt, gamelayer, tilelayer):
  size = txt.readline().split()
  width = tilelayer.width = gamelayer.width = int(size[0])
  height = tilelayer.height = gamelayer.height = int(size[1])
  
  for y in range(0, height):
    row = txt.readline().rstrip('\n')
    x = 0
    for c in row:
      t = Tile()
      t.index = rgb2tile(txt2rgb(c))
      tilelayer.set_tile(x, y, t)
      t.index = rgb2game(txt2rgb(c))
      gamelayer.set_tile(x, y, t)
      x += 1
#

def make_map_txt(txtfile, mapfile):
  twmap = Teemap("dummy")
  txt2map(open(txtfile, "r"), twmap.gamelayer, twmap.layers[2])
  twmap.save(mapfile)
#
def make_map_img(imgfile, mapfile):
  twmap = Teemap("dummy")
  img2map(Image.open(imgfile).convert("RGB"), twmap.gamelayer, twmap.layers[2])
  twmap.save(mapfile)
#

if __name__ == "__main__":
  if sys.argv[1][-4:] == ".txt":
    make_map_txt(sys.argv[1], sys.argv[2])
  elif sys.argv[1][-4:] == ".map":
    map2img(Teemap(sys.argv[1]).gamelayer).save(sys.argv[2])
  else:
      make_map_img(sys.argv[1], sys.argv[2])
#twmap2 = Teemap("yoko")
#mm = map2img(twmap2.gamelayer)
#mm.save("outgame.png")
#mm = map2img(twmap2.layers[2])
#mm.save("outtile.png")
