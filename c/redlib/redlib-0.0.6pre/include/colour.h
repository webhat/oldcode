/* Copyright (C) 1997-2002  Daniel W. Crompton <redhat@rphh.org> */

/*
 *  This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

/* CVSVERSION: $Id: $ */
/* Last modified: Sun 08 Sep 2002 02:26:18 GMT
 */

#ifndef HAVE_COLOUR_H
# define HAVE_COLOUR_H

# include "default.h"

# define PLAIN		0
# define BOLD			1
# define BLACK		30
# define RED			31
# define GREEN		32
# define YELLOW		33
# define BLUE			34
# define PURPLE		35
# define MAGENTA	35 /* extra */
# define CYAN			36
# define WHITE		37
# define GREY			46

# define BG_DARKGREY	5
# define BG_WHITE			6
# define BG_BLACK			40
# define BG_RED				41
# define BG_GREEN			42
# define BG_YELLOW		43
# define BG_BLUE			44
# define BG_PURPLE		45
# define BG_MAGENTA		45 /* extra */
# define BG_CYAN			46
# define BG_WHITE			47
# define BG_TRANS			48

# define COLOUR_DARK			0
# define COLOUR_BRIGHT		1
# define COLOUR_BG_GREY		5
# define COLOUR_BG_LIGHT	5
# define COLOUR_FLASH			6
# define COLOUR_INVERT		7
# define COLOUR_SOLID		38

# define COLOUR(X,Y) COL(X,Y)
# define COL(X,Y) "\033[" #X ";" #Y "m"
# define COLOUR_RESET printf("\033[0;22m")
# define COLSTR "\033[%u;%um"

# define RESET				"\033[0;22m"
# define TOP					"\033[H"
# define CLEAR				"\033[H\033[2J"
# define CLEAR_BELOW	"\033[0J"
# define CLEAR_ABOVE	"\033[2J"

# define INDENT				"\033[I"

# define CURSOR_UP		"\033[%sA"
# define CURSOR_DOWN	"\033[%sB"
# define CURSOR_RIGHT	"\033[%sC"
# define CURSOR_LEFT	"\033[%sD"

# define MV_ABOVE		"\033[%sK"
# define MV_BELOW		"\033[%sL"
# define RM_BELOW		"\033[%sM"
# define RM_ABOVE		"\033[%sN"

# define TITLE				"\033]0;%s\007"

#endif /* HAVE_COLOUR_H */


