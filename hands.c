#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "perf_timer.h"

#ifndef TABLE_SIZE
#define TABLE_SIZE words_count
#endif

static inline unsigned hash_string(const char *c) {
	unsigned ht = ((unsigned)*c);
	while (c && *c)
		ht = ((ht << 5) + ht) + *c++;
	return ht;
}

static inline int str_cmp(const char *a, const char *b) {
	if((*(unsigned short*)a != *(unsigned short*)b)) return 0;
	return strcmp(a, b) == 0;
}
long long miss;
#define HASH_NODE ht->nodes[index]
#define HASH_INDEX(condition)                                                  \
unsigned index = hash_string(key) & ht->size, probes = 0;                      \
while(condition) probes++, index = (index + probes) & ht->size, miss++;

typedef struct __attribute__((__packed__)) HashNode {
	char *key;
	int   value;
} HashNode; 


typedef struct Hash {
	unsigned    size;
	unsigned    items;
	HashNode   *nodes;
} Hash;

static void Hash_destroy(Hash *ht) {
	int index;
	free(ht->nodes);
	free(ht);
}

static Hash *Hash_new(unsigned size) {
	Hash *ht = calloc(1, sizeof(Hash));
	if(NULL == ht)
		goto error;
	ht->size   = size - 1;
	ht->nodes  = calloc(ht->size + 1, sizeof(HashNode));
	return ht;
error:
	Hash_destroy(ht);
	return NULL;
}

static inline HashNode *Hash_get_node(Hash *ht, char *key) {
	HASH_INDEX(HASH_NODE.key && !str_cmp(HASH_NODE.key, key));
	return &HASH_NODE;
}

static inline int Hash_get(Hash *ht, char *key) {
	HashNode *n = Hash_get_node(ht, key);
	return n->value;
}

static inline int Hash_set(Hash *ht, char *key) {
	HashNode *n = Hash_get_node(ht, key);
	return n->value;
}

int main() {
	if(read_dict() == 0)
		return -1;
	const int hash_max = 1 << 17;
	Hash *ht = Hash_new(hash_max);
	int i, res;
	char *buf;
	perf_timer_start();
	for(i = 0; i < 20000000; i++) {
		buf = words[i % TABLE_SIZE];
		HashNode *n = Hash_get_node(ht, buf);
		if(NULL != n->key)
		{
			n->value++;
		}
		else
		{
			n->key = buf;
			n->value = 1;
		}
	}
	perf_timer_end();
	perf_timer_print();
	Hash_destroy(ht);
	return 0;

}
