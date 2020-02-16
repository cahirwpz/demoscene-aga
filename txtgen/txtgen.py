#!/usr/bin/env python

import pygtk
pygtk.require('2.0')
import gtk


class TxtGen(object):
  def hello(self, widget, data=None):
    print "Hello World"

  def delete_event(self, widget, event, data=None):
    print "delete event occurred"
    return False

  def destroy(self, widget, data=None):
    print "destroy signal occurred"
    gtk.main_quit()

  def area_expose_cb(self, area, event):
    self.style = self.area.get_style()
    self.gc = self.style.fg_gc[gtk.STATE_NORMAL]
    b = ['\0'] * 256 * 256 * 3
    for i in range(256):
      for j in range(256):
        b[3 * (256 * i + j)] = chr(255 - i)
        b[3 * (256 * i + j) + 1] = chr(255 - abs(i - j))
        b[3 * (256 * i + j) + 2] = chr(255 - j)
    buff = ''.join(b)
    self.area.window.draw_rgb_image(self.gc, 0, 0, 256, 256,
                                    gtk.gdk.RGB_DITHER_NONE, buff, 256 * 3)
    return True

  def __init__(self):
    self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
    self.window.connect("delete_event", self.delete_event)
    self.window.connect("destroy", self.destroy)
    self.window.set_border_width(10)

    self.area = gtk.DrawingArea()
    self.area.set_size_request(256, 256)
    self.area.connect("expose-event", self.area_expose_cb)
    self.area.show()

    self.button = gtk.Button("Hello World")
    self.button.connect("clicked", self.hello, None)
    self.button.connect_object("clicked", gtk.Widget.destroy, self.window)
    self.button.show()

    self.table = gtk.Table(1, 2)
    self.table.attach(self.area, 0, 1, 0, 1)
    self.table.attach(self.button, 0, 1, 1, 2)
    self.table.show()

    self.window.add(self.table)
    self.window.show()

  def run(self):
    gtk.main()


if __name__ == "__main__":
    txtgen = TxtGen()
    txtgen.run()
