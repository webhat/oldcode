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
/* Last modified: Thu 13 Feb 2003 03:34:38 GMT
 */

#ifndef HAVE_XDVNG_H
# define HAVE_XDVNG_H

#include <qwidget.h>

class XdvngButton;

class Xdvng : public QWidget
{
		Q_OBJECT;
		public:
				Xdvng( QWidget *parent=0, const char *name=0);
				~Xdvng();

		public slots:
				void setCorrect( int num );
		signals:
				void isCorrect(int);

		private:
				XdvngButton *Top;
				XdvngButton *Bot[6];
};


#endif /* HAVE_XDVNG_H */


