#include <time.h>

#include "hashtable.h"

// full insert -> full find -> full erase -> full find test
int test(HashTable *ht, int loop)
{
	int i, *keys = NULL;
	char data[] = "Hello, World";
	size_t data_len = strlen(data);
	HashTableBucket *bucket;

	if ( !(keys = malloc(sizeof(int) * loop)) ) {
		fprintf(stderr, "malloc() is failed: (errmsg: %s, errno: %d, size: %lu\n", strerror(errno), errno, sizeof(int) * loop);
		goto out;
	}
	
	// insert
	for ( i = 0; i < loop; i++ ) {
		keys[i] = i;
		if ( ht->insert(ht, &keys[i], sizeof(int), data, data_len) < 0 ) {
			fprintf(stderr, "insert test fail: %s\n", ht_get_last_error());
			goto out;
		}
	}
	
	// find
	for ( i = 0; i < loop; i++ ) {
		if ( !(bucket = ht->find(ht, &keys[i], sizeof(int))) ) {
			fprintf(stderr, "find test fail: can not found to bucket: (key: %d)\n", keys[i]);
			goto out;
		}
	}

	// erase
	for ( i = 0; i < loop; i++ ) {
		if ( ht->erase(ht, &keys[i], sizeof(int)) == HT_BUCKET_NOT_FOUND ) {
			fprintf(stderr, "erase test fail: can not found to bucket: (key: %d)\n", keys[i]);
			goto out;
		}
	}
	
	// find
	for ( i = 0; i < loop; i++ ) {
		if ( (bucket = ht->find(ht, &keys[i], sizeof(int))) ) {
			fprintf(stderr, "find test fail: bucket shouldn't have been found: (key: %d)\n", keys[i]);
			goto out;
		}
	}
	
	if ( ht->rearrange_fail ) {
		fprintf(stderr, "ht->rearrange_fail: %d\n", ht->rearrange_fail);
		goto out;
	}
	
	free(keys);

	return 0;

out:
	if ( keys ) free(keys);

	return -1;
}

// half insert -> half find -> half insert -> half find -> full erase -> full find test
int test2(HashTable *ht, int loop)
{
	return 0;
}

int main(int argc, char **argv)
{
	HashTable *ht;

	if ( argc != 2 ) {
		fprintf(stderr, "%s (loop count)\n", argv[0]);
		goto out;
	}

	if ( !(ht = ht_create(1024, 0)) ) {
		fprintf(stderr, "ht_create() is failed: %s\n", ht_get_last_error());
		goto out;
	}

	if ( test(ht, atoi(argv[1])) < 0 ) goto out;
	if ( test2(ht, atoi(argv[1])) < 0 ) goto out;

	ht_dump(ht, 1);

	ht_delete(ht);

	printf("test success!\n");

	return 0;

out:
	ht_delete(ht);

	fprintf(stderr, "test fail.\n");

	return 1;
}
