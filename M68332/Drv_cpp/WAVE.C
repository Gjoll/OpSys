/* * * * * * * * * * * * * * * * * * * * * * * * * * 
* wave
*
* Displays the wave form of bytes using printable ascii.
*
* Author: Mark Giebler
** * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>

main()
{
  unsigned char table[1024];
  char buf[80];
  int i = 0, ti = 0, nmbr;
  unsigned int u_nmbr;
  int c;

/* read in the table and convert numbers to binary */
     while( (c = getchar()) != EOF){
  		if( c == '/'){ /* comment line so skip it */
    		gets(buf);
			printf("/%s\n",buf);
 
    		continue;
		}
/* if we reach white space, try and convert a number */
		if( c == ' ' || c == '\n' || c == '\r'){
			if( i > 0){ /* skip leading white space */
				i = 0;
				nmbr = u_nmbr = 0;
				sscanf(buf,"%i", &nmbr);
	  			if( nmbr >=0 && nmbr <= 0x7f) /* need to shift up */
      				u_nmbr = (unsigned) nmbr + (unsigned) 0x080;
	  			else{
				/* need to shift down. */
					nmbr = nmbr & 0x07f;
					nmbr = (nmbr - 0x80) * -1;	/* mirror around 0x80 y axis */
					u_nmbr = nmbr & 0x0ff;
	  			}
				printf("0x%2.2x",u_nmbr);
				u_nmbr = u_nmbr / 4;
				while(u_nmbr-- != 0)
					printf(" ");
				if( ti & 0x01)
				  printf("*\n");
				else
				  printf("#\n");
				ti++;
    		}else
				continue;
    	}else{
		/* assume part of a number */
			buf[i] = c;
  			i++;
  			buf[i] = 0;
		}
	}
}










































































