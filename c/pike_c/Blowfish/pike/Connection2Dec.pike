#!/usr/local/bin/pike6.132

void debug( string in) {
				werror(in +"\n");
}
void main () {
				object o = Stdio.FILE();
				object BF = Blowfish.blowz("12345678");
				string tmp;
				string stringhex;
				array(string) bytearray = ({});
				string output ="";

				o->open_socket();
				o->connect("cvs", 1024);
				tmp = o->gets();
				tmp = o->gets();
				sscanf(tmp, "plaap : %s", stringhex);
				debug(stringhex);

				bytearray = stringhex/2;
				debug(sprintf("%O", values(bytearray)));

				foreach( values(bytearray), string i) {
								output += (string)(int)i;
								debug( BF->decrypt((string)(int)i));
				}
				debug(output);
				debug(BF->decrypt(output));
}
