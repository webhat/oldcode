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
/* Last modified: Tue 23 Jul 2002 21:54:22 GMT
 */

/* XXX: For Americans,
 * 		So you too can use colour.h from the library. (c;
 * Although this is meant as a joke the header is real,
 * I find myself typing color so often I sometimes forget
 * it's the wrong spelling.
 *
 * XXX: For Brits,
 * 		If you also have problems with our fine spelling, you
 * can not be forgiven and thusly must be shamed! (c:
 *
 * #define _I_AM_BRITISH_AND_CANT_SPELL_COLOUR_WITH_A_U_AND_MUST_THEREFORE_MUST_SPELL_IT_C_O_L_O_R
 *
 * 		Carry this mark of shame and you can pick and match.
 *
 * XXX: For everybody who read this far down,
 * 		You can flame me all you want for my spelling, for
 * wasting your time and generally for anything else. (c:
 */

#ifndef HAVE_COLOR_H
# define HAVE_COLOR_H

# include <redlib/colour.h>

# define COLOR_DARK			COLOUR_DARK
# define COLOR_BRIGHT		COLOUR_BRIGHT
# define COLOR_BG_GREY	COLOUR_BG_GREY
# define COLOR_BG_LIGHT	COLOUR_BG_LIGHT
# define COLOR_INVERT		COLOUR_INVERT
# define COLOR_SOLID		COLOUR_SOLID

# define COLOR(X,Y)			COLOUR(X,Y)
# define COLOR_RESET		COLOUR_RESET

# if !defined(_I_AM_BRITISH_AND_CANT_SPELL_COLOUR_WITH_A_U_AND_MUST_THEREFORE_MUST_SPELL_IT_C_O_L_O_R)
#  undef COLOUR_DARK
#  undef COLOUR_BRIGHT
#  undef COLOUR_BG_GREY
#  undef COLOUR_BG_LIGHT
#  undef COLOUR_INVERT
#  undef COLOUR_SOLID

#  undef		COLOUR(X,Y)
#  undef		COLOUR_RESET
# endif /* _I_AM_BRITISH_AND_CANT_SPELL_COLOUR_WITH_A_U_AND_MUST_THEREFORE_MUST_SPELL_IT_C_O_L_O_R */

#endif /* HAVE_COLOR_H */


