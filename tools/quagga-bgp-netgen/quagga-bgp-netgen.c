/*-
 * Copyright (c) 2011 Olivier Cochard-Labbé
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/tools/tools/netrate/netblast/netblast.c,v 1.3.10.1.6.1 2010/12/21 17:09:25 kensmith Exp $
 */

#include <stdio.h>
#include <stdlib.h>
/* #include <string.h> */

static void
usage(void)
{

	fprintf(stderr, "genroute [number] [local-as] [router-id] [remote-as] [remote-peer-ip]\n");
	exit(-1);
}

/* Generate sample quagga bgp configuration file */
/* With "number" of routes*/
int
main(int argc, char *argv[])
{
	unsigned long networks,i;
	char *dummy;
	/* Network IP: a.b.c.0/24 */
	unsigned short a=1,b=1,c=0;

	/* check number of argument */
	if (argc != 6)
		usage();

	networks = strtoul(argv[1], &dummy, 10);
	if ( networks < 1 || *dummy != '\0' )
		usage();
	printf("! Quagga/Zebra configuration file\n");
	printf("! Autogenerated with quagga-bgp-netgen\n");
	printf("router bgp %s\n",argv[2]);
	printf(" bgp router-id %s\n",argv[3]);
	printf(" neighbor %s remote-as %s\n",argv[5],argv[4]);
	for (i = 0; i <= networks; i++) {
		if ( a < 223 ) {
			if ( a == 127 )
				a++;
			if ( b == 255 ) {
				a++;
				b=0;
				c=0;
			} else if ( b < 255 ) {
				if ( c == 255 ) {
					b++;
					if ( b == 254 )
						b = 0;
					c=0;
				} else if ( c < 255 ) 
					c++;
			}
			printf(" network %u.%i.%i.0/24\n",a,b,c);
		} else {
			printf ("Max value reached");
			break;
		}
	}

	return (0);
}