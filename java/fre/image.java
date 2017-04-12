
/*
    Copyright (C) 1997-1999  Daniel W. Crompton <redhat@rphh.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

public final synchronized class image {
  static final String defaultImageName = "roxen.gif";
  ImageMapTransBean imapBean;
  boolean usingDefaultImage;

  public void ImageGet(String nm) {
    setTransitional(true);
    imapBean = new ImageMapTransBean();
    imapBean.setImageMapListener(this);
    usingDefaultImage = true;
    imapBean.setImageName("roxen.gif");
    loadImage();
  }

  public static Image getImage(Object comp, String name) {
    try {
      URL u = getResource(comp, name);
      return getImage(u);
    }
    catch (Exception e) {
      return null;
    }
  }

  void loadImage() {
    java.awt.Image image = getImage(this, imapBean.getImageName());
    imapBean.loadImage(image);
  }
}
