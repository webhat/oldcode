#!/usr/local/bin/pike6.132

void main( int argc, array(string) argv) {
				string java;
				string code;
				string out;
				array(string) bytes;

				code = Stdio.read_bytes( argv[1]);

				bytes = replace( code, ({ "(byte)", "}", "{", "\r", "\n"}), ({ "", "", "", "", ""}))/",";

				foreach(values(bytes), string i) {
								out +=(string)(int)i;
				}
				werror(sprintf("%O", out));
}
