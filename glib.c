#include <glib.h>
#include "read.h"
#include "perf_timer.h"

#ifndef TABLE_SIZE
#define TABLE_SIZE words_count
#endif

int main()
{
	if(read_dict() == 0)
		return -1;
	GHashTable *ht = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
	gint i;
	gpointer key;
	char * buf;
	perf_timer_start();
	for(i = 0; i < 20000000; i++)
	{
		buf = words[i % TABLE_SIZE];
		gint *val = g_hash_table_lookup(ht, buf);
		if(val)
		{
			*(gint*)val+=1;
		}
		else
		{
			gint *v = g_new(gint, 1);
			*v = 1;
			g_hash_table_insert(ht, buf, v);
		}
	}
	perf_timer_end();
	perf_timer_print();
	g_hash_table_destroy(ht);
	return 0;
}
