#! /usr/bin/env python

# Zebra's World:
#     the world full of lions, zebras and lions turned into cannibalistic zebras ;)

# Author: Miroslav Franc
# The idea comes from Arjun Shankar (it's a pub idea :))


from __future__ import print_function
from random import choice, randrange
import curses
import time
import sys


class ZebraWorld(object):
    def __init__(self, x, y):
        self._a = [[self._populate() for i in xrange(x)] for i in xrange(y)]
        self._x = x
        self._y = y
        self._c = 0

    def _populate(self):
        return choice(['z', 'L'] + [' '] * 64)

    def _move(self, x, y):
        xmove = choice([-1, 0, 1]) + x
        if xmove < self._x and xmove >= 0:
            x = xmove
        ymove = choice([-1, 0, 1]) + y
        if ymove < self._y and ymove >= 0:
            y = ymove
        return x, y

    def clear(self):
        self._a = [[self._populate() for i in xrange(self._x)] for i in xrange(self._y)]

    def update(self):
        b = [[True for i in xrange(self._x)] for i in xrange(self._y)]
        for iy, y in enumerate(self._a):
            for ix, x in enumerate(y):
                nix, niy = self._move(ix, iy)
                if not b[niy][nix]:
                    break
                if x != ' ' and self._a[niy][nix] == ' ':
                    self._a[niy][nix] = x
                    self._a[iy][ix] = ' '
                    b[niy][nix] = False
                elif x == 'z' and self._a[niy][nix] == 'L':
                    self._a[niy][nix] = 'Z'
                    self._a[iy][ix] = ' '
                    b[niy][nix] = False
                elif x == 'L' and self._a[niy][nix] == 'z':
                    self._a[iy][ix] = ' '
                    self._a[niy][nix] = 'Z'
                    b[niy][nix] = False
                elif x == 'Z' and self._a[niy][nix] == 'z':
                    self._a[iy][ix] = choice(['Z', ' ', ' ', ' ', 'z'])
                    self._a[niy][nix] = 'Z'
                    b[niy][nix] = False
                elif x == 'z' and self._a[niy][nix] == 'Z':
                    self._a[iy][ix] = choice(['Z', ' ', ' ', ' ', 'z'])
                    self._a[niy][nix] = 'Z'
                    b[niy][nix] = False
                elif x == 'Z' and self._a[niy][nix] == 'Z':
                    self._a[iy][ix] = choice(['Z', 'Z', 'Z', ' ', 'z'])
                    self._a[niy][nix] = 'Z'
                    b[niy][nix] = False
                elif x == 'z' and self._a[niy][nix] == 'z':
                    oix, oiy = self._move(nix, niy)
                    if self._a[oiy][oix] == ' ':
                        self._a[oiy][oix] = choice(['z', 'z', 'z', ' ', ' ', ' ', ' '])
                        b[oiy][oix] = False
                elif x == 'L' and self._a[niy][nix] == 'L':
                    self._a[iy][ix] = choice(['L', 'L', 'L', ' '])
                    oix, oiy = self._move(nix, niy)
                    if self._a[oiy][oix] == ' ':
                        self._a[oiy][oix] = choice(['L', ' '])
                        b[oiy][oix] = False
                if randrange(10) == 0:
                    self._a[iy][ix] = ' '

    def __iter__(self):
        self._c = 0
        return self

    def next(self):
        if self._c < self._y:
            self._c += 1
            return self._a[self._c-1]
        else:
            raise StopIteration()


def main():
    try:
        def draw_border(w, xsize):
            w.border()
            w.addstr(0, 2, "Zebra's world")
            w.addstr(xsize-1, 2, "(q)uit (r)efresh")

        w = curses.initscr()

        curses.start_color()
        curses.init_pair(1, curses.COLOR_GREEN, curses.COLOR_BLACK)
        curses.init_pair(2, curses.COLOR_YELLOW, curses.COLOR_BLACK)
        curses.init_pair(3, curses.COLOR_RED, curses.COLOR_BLACK)
        curses.init_pair(4, curses.COLOR_WHITE, curses.COLOR_BLACK)
        curses.noecho()
        curses.curs_set(False)

        w.nodelay(True)
        w.keypad(True)

        wx, wy = w.getmaxyx()

        z1 = ZebraWorld(wx-2, wy-2)

        draw_border(w, wx)
        w.refresh()

        colors = {'z': 1, 'L': 2, 'Z': 3, ' ': 4}

        q = w.getch()

        while q != ord('q'):
            time.sleep(0.1)
            for x, line in enumerate(z1, start=1):
                for y, cell in enumerate(line, start=1):
                    w.addstr(y, x, cell, curses.color_pair(colors[cell]))
            z1.update()
            w.refresh()
            q = w.getch()
            if q == ord('r'):
                z1.clear()
            elif q == curses.KEY_RESIZE:
                xx, yy = w.getmaxyx()
                z1 = ZebraWorld(xx-2, yy-2)
                draw_border(w, xx)

    finally:
        curses.endwin()


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        sys.stderr.write("\nControl-C.  Let's call it quits.\n")
