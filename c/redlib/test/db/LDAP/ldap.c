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
/* Last modified: Thu 23 Jan 2003 03:45:22 GMT
 */

#include <lber.h>
#include <ldap.h>

#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ERROR(X) do { fprintf(stderr,"Error: %s\n", X); exit(-1); } while(0)

int main( argc, argv, envp)
		int argc;
		char *argv[];
		char *envp[];
{
		int j;
		char **sstr_l, *attr;
		BerElement *ber;
		LDAPMessage *res;
		LDAPMessage *elem;
		LDAP *ld = ldap_open("localhost",389);

		if(ld == NULL)
				ERROR("Couldn't open connection");

		ldap_simple_bind(ld, "cn=root,o=xlnt", "secret");

		if(ldap_search_s(ld,
#if 1
								"cn=umdb,o=xlnt",
#else
								"domain=xlnt,o=xlnt",
#endif
								LDAP_SCOPE_ONELEVEL,
#if 1
								"(objectclass=*)",
#else
								"(&(objectclass=*)(uid=redhat))",
#endif
								NULL,
								0,
								&res) == LDAP_SUCCESS)
				printf("LDAP: success(%d)\n", ldap_count_entries(ld,res));
		
		if((elem = ldap_first_entry(ld, res)) == NULL)
				ERROR("ldap_first_entry");

		do {
				printf("\n");
				attr = ldap_first_attribute(ld,elem,&ber);
				do {
						sstr_l = ldap_get_values(ld,elem,attr);
						for( j = 0; j <= ldap_count_values(sstr_l) ; sstr_l++, j++) {
								printf("LDAP: result %s=%s\n"
												,attr
												,*(sstr_l));
						}
				} while((attr = ldap_next_attribute(ld,elem,ber)) != NULL);
		} while((elem = ldap_next_entry(ld,elem)) != NULL);


		ldap_unbind(ld);

		printf("\n");

		return 0;
}
