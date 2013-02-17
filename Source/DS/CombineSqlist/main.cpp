#include <stdio.h>

int main()
{
	int a[10],b[10],c[20];
	
	for(size_t ix = 0;ix != 10;++ix)
	{
		a[ix] = 2 * ix + 1;
		b[ix] = 2 * ix + 2;
		printf("%d\t%d\n",a[ix],b[ix]);
	}
	printf("\n");
	size_t ix_a = 0,ix_b = 0,ix_c = 0;
	while(ix_a < sizeof(a) / sizeof(*a) 
		  && ix_b < sizeof(b) / sizeof(*b))
		  c[ix_c++]=a[ix_a]>b[ix_b]?(b[ix_b++]):(a[ix_a++]);
	while(ix_a < sizeof(a) / sizeof(*a))
		c[ix_c++]=a[ix_a++];
	while(ix_b < sizeof(b) / sizeof(*b))
		c[ix_c++]=b[ix_b++];
	for(ix = 0;ix != sizeof(c) / sizeof(*c);++ix)
	{
		printf("%d\t",c[ix]);
		if((ix + 1) % 4 == 0) printf("\n");
	}
	printf("\n");
	return 0;
}