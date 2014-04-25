#---------------------------------------------------------------------------------
#  main.c
#  Copyright (C) David Millán Escrivá 2010 <david@artresnet.com>
#  
#  pseudocolor is free software: you can redistribute it and/or modify it
#  under the terms of the GNU General Public License as published by the
#  Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#  
#  pseudocolor is distributed in the hope that it will be useful, but
#  WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#  See the GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License along
#  with this program.  If not, see <http://www.gnu.org/licenses/>.
#---------------------------------------------------------------------------------
CC=gcc


all: tutorial

tutorial: main.c pseudocolor.o
	$(CC) -o $@ $^ `pkg-config --cflags --libs opencv`

pseudocolor.o: pseudocolor.c
	$(CC) -c $< `pkg-config --cflags  opencv`

clean:
	rm -f tutorial pseudocolor.o
