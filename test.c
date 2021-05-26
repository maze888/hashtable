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
		if ( ht->erase(ht, &keys[i], sizeof(int)) < 0 ) {
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
	
	/*if ( ht->rearrange_fail ) {
		fprintf(stderr, "ht->rearrange_fail: %d\n", ht->rearrange_fail);
		goto out;
	}*/
	
	free(keys);

	return 0;

out:
	if ( keys ) free(keys);

	return -1;
}

int multi_key_test(HashTable *ht, int loop)
{
	int i, key = 1234;
	char data[] = "Hello, World";
	size_t data_len = strlen(data);
	HashTableBucket *bucket;
	
	// insert
	for ( i = 0; i < loop; i++ ) {
		if ( ht->insert(ht, &key, sizeof(key), data, data_len) < 0 ) {
			fprintf(stderr, "insert test fail: %s\n", ht_get_last_error());
			goto out;
		}
	}
	
	// find
	for ( i = 0; i < loop; i++ ) {
		if ( !(bucket = ht->find(ht, &key, sizeof(key))) ) {
			fprintf(stderr, "find test fail: (key: %d)\n", key);
			goto out;
		}
	}
	
	// erase
	if ( ht->erase(ht, &key, sizeof(key)) < 0 ) {
		fprintf(stderr, "erase test fail: (key: %d)\n", key);
		goto out;
	}
	
	// find
	if ( (bucket = ht->find(ht, &key, sizeof(key))) ) {
		fprintf(stderr, "find test fail: (key: %d)\n", key);
		goto out;
	}

	return 0;

out:
	return -1;
}

int main(int argc, char **argv)
{
	HashTable *ht = NULL;
	HashTable *multi_key_ht = NULL;

	if ( argc != 2 ) {
		fprintf(stderr, "%s (loop count)\n", argv[0]);
		goto out;
	}

	if ( !(ht = ht_create(1024, 0, 0)) ) {
		fprintf(stderr, "ht_create() is failed: %s\n", ht_get_last_error());
		goto out;
	}
	
	if ( !(multi_key_ht = ht_create(1024, 0, 1)) ) {
		fprintf(stderr, "ht_create() is failed: %s\n", ht_get_last_error());
		goto out;
	}

	//if ( test(ht, atoi(argv[1])) < 0 ) goto out;
	if ( multi_key_test(multi_key_ht, atoi(argv[1])) < 0 ) goto out;

	//ht_dump(ht, 1);
	ht_dump(multi_key_ht, 1);

	ht_delete(ht);
	ht_delete(multi_key_ht);

	printf("test success!\n");

	return 0;

out:
	ht_delete(ht);
	ht_delete(multi_key_ht);

	fprintf(stderr, "test fail.\n");

	return 1;
}
