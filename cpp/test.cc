#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>

using namespace std;

int main() {

	int len = atoi( getenv( "CONTENT_LENGTH"));
	if ( len < 0) return -1;

	void * data = malloc( len + 10);
	int rc = 0;
	do {
		int r = read( 0, data, len-rc);
		if ( r <= 0) return -1;
		rc += r;
	} while ( rc < len);

	FILE * fp = fopen( "log.txt", "w");
	fwrite( data, len, 1, fp);
	fclose( fp);

	free( data);

	std::string content = std::string( "<XACTOR autocommand=\"cgirun\">\n") +
		std::string( "<COMMAND ID=\"cgirun\"\n") +
		std::string( "remove cgirun;\n") +
		std::string( "</COMMAND>\n") +
		std::string( "</XACTOR>\n");
	
	cout << "Content-type: text/html\n";
	cout << "Content-length: " << content.length() << endl << endl << content;
	
	return 0;
}
