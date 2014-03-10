#include <cstdio>

unsigned str_quickhash(const char *str)
{
	unsigned hash = 5381;
	for(; *str; str++)
		hash = ((hash << 5) + hash) + (*str); /* hash * 33 + c */
	return hash;
}

int main(int argc, char * argv[])
{
	if(argc < 3)
	{
		fprintf(stderr, "USAGE: %s [name] [level]", argv[0]);
		return 1;
	}
	char key[64];
	snprintf(key, sizeof(key), "%s///%s", argv[2], argv[1]);

	printf("%08X", str_quickhash(key));
	return 0;
}
