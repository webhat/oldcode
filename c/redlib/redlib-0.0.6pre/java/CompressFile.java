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

/* Last modified: Tue 30 Jul 2002 01:44:23 GMT
 */

package redlib.RFILE;

/**
 * <B>redlib</B>
 * <P>
 * The <CODE>redlib</CODE> java class is a native implementation
 * of the redlib <CODE>RFILE</CODE>. This java extention is meaned
 * to make it easier and faster to nativly handle files of various
 * compressed forms:
 * <UL>
 * <LI>gzip&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(Lempel-Ziv)</LI>
 * <LI>freeze&nbsp;&nbsp;&nbsp;&nbsp;1.0</LI>
 * <LI>freeze&nbsp;&nbsp;&nbsp;&nbsp;2.1</LI>
 * <LI>compress&nbsp;&nbsp;(SCO compress LZH)</LI>
 * <LI>lzop</LI>
 * <LI>bzip</LI>
 * <LI>bzip2</LI>
 * </UL>
 * <P>
 * 
 * 
 */
public abstract class CompressFile {
				static {
								System.loadLibrary("red");
				}
				/**
				 * End Of File.
				 */
				public static final int EOF = -1;
				/**
				 * Read <CODE>char[]</CODE> from stream.
				 * @param sz of bytes read.
				 * @return <CODE>char[]</CODE> read.
				 */
				protected native char[] read(int sz);
				/**
				 * Write <CODE>char[]</CODE> to stream.
				 * @param string to write.
				 * @return number of bytes read.
				 */
				protected native int write(char[] string);
				/**
				 * Flush stream.
				 * @return on success 0 is returned otherwise <CODE>EOF</CODE>.
				 */
				private native int flush();
				/**
				 * Open file.
				 * @param 
				 * @param 
				 */
				private native void open(char[] file, char[] mode);
				/**
				 * Close file.
				 */
				private native void close();

				/**
				 * Open read only.
				 * @param file name.
				 */
				public CompressFile(String file) {
								this(file,"r9");
				}

				/**
				 * Open file with mode (as in libc <CODE>fopen</CODE>).
				 * @param file name.
				 * @param mode to open with.
				 */
				public CompressFile(String file, String mode) {
								open(
																file.toCharArray(),
																mode.toCharArray()
																);
				}

				/**
				 * Call to native methode <CODE>read()</CODE> and throw
				 * exception on failure.
				 * @see redlib.RFILE.CompressFileException
				 */
				public String Read(int sz) throws CompressFileException {
								String str = new String(read(sz));

					//			if(str.length() > sz)
					//							throw new CompressFileException("Read too much");

								return str;
				}

				/**
				 * Call to native methode <CODE>write()</CODE> and throw
				 * exception on failure.
				 * @see redlib.RFILE.CompressFileException
				 */
				public int Write(String string) throws CompressFileException {
								int written = write(string.toCharArray());

								if(written > string.length())
												throw new CompressFileException("Wrote too much");

								return written;
				}

				/**
				 * Call to native methode <CODE>flush()</CODE> and throw
				 * exception on failure.
				 * @see redlib.RFILE.CompressFileException
				 */
				public void Flush() throws CompressFileException {
								if(flush() == EOF)
												throw new CompressFileException(
																				"Failed to flush stream to disk"
																				);
				}

				public void Close() throws CompressFileException {
								close();
				}

				/**
				 * On garbage collect close the file.
				 */
				protected void finalize() {
								try {
												Close();
								} catch( CompressFileException cfe) { /* empty */ }
				}

				/**
				 * main for testing only!
				 */
				public static void main(String arg[]) {
								CompressFile file0 = new CompressFile(arg[0], "r+9") { };
								try {
												file0.Flush();
												file0.Write("gzip5678");
												file0.Flush();
												System.out.println( file0.Read(8));
												file0.Close();
								} catch( CompressFileException cfe) {
												/* empty */
												cfe.printStackTrace();
								}
								System.out.println("java "+ arg[0]);
				}
}


