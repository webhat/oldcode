/* Copyright (C) 1997-2002  XLNT-Software */
/* Daniel W. Crompton <redhat@xlnt-software.com> */

/* Last modified: Sun 03 Nov 2002 20:42:02 GMT
/* CVSVERSION: $Id: $ */

import java.util.Timer;
import java.util.TimerTask;
import javax.swing.*;
import javax.swing.event.*;
import java.awt.event.*;
import java.util.*;
import java.awt.*;

public class click extends JFrame {
		public click() {
				super();
				addWindowListener(new Closer());
				JButton test = new JButton();
				test.addMouseListener( new MouseInputAdapter() {
						protected Timer timer;
						protected Random rand = new Random();
						private boolean bool = true;
						private Dimension sz = Toolkit.getDefaultToolkit().getScreenSize();
						public void mouseEntered(final MouseEvent evt_) {
								int x = 0;
								int y = 0;
								float ranx = 0;
								float rany = 0;
								while((ranx = rand.nextFloat()) > 1 || ranx < 0);
								while((rany = rand.nextFloat()) > 1 || rany < 0);
								bool = rand.nextBoolean();
								Point p = click.this.getLocation();
								//System.out.println("["+ ranx +","+ rany +"]");
								if(evt_.getX() > (int)p.getX() || bool)
										x = (int)p.getX()+(int)(ranx*100);
								else
										x = (int)p.getX()-(int)(ranx*100);
								if(evt_.getY() > (int)p.getY() || bool)
										y = (int)p.getY()+(int)(rany*100);
								else
										y = (int)p.getY()-(int)(rany*100);
								if( x < 0 || x > sz.getWidth())
										x = 0;
								if( y < 0 || y > sz.getHeight())
										y = 0;
								click.this.setLocation(x,y);
						}
						public void mouseClicked(final MouseEvent evt_) {
								//System.out.println("ClickCount: "+ evt_.getClickCount());
								new click();
								if(evt_.getClickCount() == 2) {
										timer.cancel();
										System.out.println("double clicked");
										return;
								}
								timer = new Timer();
								timer.schedule(new TimerTask() {
										public void run() {
												System.out.println("clicked");
										}
								}, 500);
						}
						public void mousePressed(final MouseEvent evt_) {
								System.out.println("pressed");
						}
						public void mouseReleased(final MouseEvent evt_) {
								System.out.println("released");
						}
				});
				JTextArea text		= new JTextArea("pokoe");
				JScrollPane pane = new JScrollPane(text);
				text.setEditable(false);
				text.setPreferredSize(new Dimension(400,800));
				getContentPane().add(pane);
				//getContentPane().add(test);
				//getContentPane().add(new JColorChooser());
				//getContentPane().add(new pornwire.GUI.port.Options().createComp(this));
				//JColorChooser.showDialog(this,"color",Color.GREEN);
				pack();
				show();
		}
		public static void main(String arg[]) {
				new click();
		}
		protected static final class Closer extends WindowAdapter {
						/**
						 * Response to Window Closing.
						 * @param windowevent
						 */
						public void windowClosing(WindowEvent windowevent) {
										System.exit(0);
						}
		}
}

