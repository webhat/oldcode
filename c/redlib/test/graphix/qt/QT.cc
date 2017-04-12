/* Copyright (C) 1997-2002  Daniel W. Crompton <redhat@rphh.org> */

/*
 *   This program is free software; you can redistribute it and/or modify
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
/* Last modified: Thu 13 Feb 2003 03:36:44 GMT
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qlayout.h>
#include "xdvng.h"
#include "xdvngbutton.h"

XdvngButton::XdvngButton( const char *text, QWidget *parent, const char *name)
		: QPushButton(text, parent, name)
{
		setFont( QFont( "xdvng", 18, QFont::Bold));
}

void XdvngButton::setCorrect(bool correct)
{
		c = correct;
}

XdvngButton::~XdvngButton()
{
}

Xdvng::Xdvng( QWidget *parent, const char *name)
		: QWidget( parent, name)
{
		//Top = new XdvngButton("Push to start", this, "start");
		Top = new XdvngButton("calanà", this, "start");
		QPushButton *Quit = new QPushButton("&Quit", this, "quit");
		Bot[0] = new XdvngButton("1", this, "but1");
		Bot[1] = new XdvngButton("2", this, "but2");
		Bot[2] = new XdvngButton("3", this, "but3");
		Bot[3] = new XdvngButton("4", this, "but4");
		Bot[4] = new XdvngButton("5", this, "but5");
		Bot[5] = new XdvngButton("6", this, "but6");
		Top->setFocus();
		QGridLayout *grid = new QGridLayout( this, 3, 1, 3);
		grid->addWidget( Top, 0, 0);
		grid->addWidget( Quit, 2, 0);

		Quit->setFont( QFont( "times", 18, QFont::Bold));
		connect( Quit, SIGNAL(clicked()), qApp, SLOT(quit()));

		QGridLayout *bottomGrid = new QGridLayout;
		grid->addLayout( bottomGrid, 1, 0);
		bottomGrid->addWidget( Bot[0], 0, 0);
		bottomGrid->addWidget( Bot[1], 0, 1);
		bottomGrid->addWidget( Bot[2], 0, 2);
		bottomGrid->addWidget( Bot[3], 1, 0);
		bottomGrid->addWidget( Bot[4], 1, 1);
		bottomGrid->addWidget( Bot[5], 1, 2);
}

void Xdvng::setCorrect(int num )
{
}

Xdvng::~Xdvng()
{
}

int main( int argc, char *argv[], char *envp[])
{
		QApplication a( argc, argv);
		Xdvng xdvng;

		xdvng.setGeometry( 100, 100, 400, 100);

		a.setMainWidget( &xdvng);
		xdvng.show();
		return a.exec();
}
