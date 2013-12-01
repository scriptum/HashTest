#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

char **words = NULL;
int words_count;

static inline int read_dict()
{
	char buf[64];
	int c = 0;
	char **words_new = NULL;
	const int extent = 1 << 8;
	FILE *f = fopen("dictionary.txt", "rb");
	if(NULL == f) goto fail;
	while(fgets(buf, sizeof(buf), f))
	{
		size_t p;
		words_new = (char **)realloc(words, (c/extent+1)*extent*sizeof(char**));
		if(NULL == words_new) goto fail_close;
		words = words_new;
		p = strcspn(buf, "\n\r");
		buf[p] = '\0';
		words[c] = strdup(buf);
		c++;
	}
	words_count = c;
	return 1;
fail_close:
	fclose(f);
	while(--c)
		free(words[c]);
	free(words);
fail:
	return 0;
}
