# hashtable
Hashtable is O(1) data structure library.
Use in threads you must use lock(mutex).

* autoscale bucket
* maximum number of buckets can be specified when creating (may be useful in environments with severe memory constraints)
* insert, erase, find (execution completed within O(1) time)

# example
```c
#include "hashtable.h"
 
int main(int argc, char **argv)
{
  HashTable *ht;
  HashTableBucket *bucket;
  int key = 1234;
  char value[] = "Hello, World";
  size_t value_len = strlen(value);

  if ( !(ht = ht_create(1024, 0 /* use default size */)) ) {
    fprintf(stderr, "ht_create() is failed: %s\n", ht_get_last_error());
    goto out;
  }

  // insert
  if ( ht->insert(ht, &key, sizeof(key), value, value_len) < 0 ) {
    fprintf(stderr, "insert test fail: %s\n", ht_get_last_error());
    goto out;
  }
  
  // find
  if ( !(bucket = ht->find(ht, &key, sizeof(key))) ) {
    fprintf(stderr, "find test fail: can not found to bucket: (key: %d)\n", key);
    goto out;
  }
  printf("key: %d\n", *(int *)bucket->key);
  printf("value: %s\n", (char *)bucket->value);
  
  // erase
  if ( ht->erase(ht, &key, sizeof(key)) == HT_BUCKET_NOT_FOUND ) {
    fprintf(stderr, "erase test fail: can not found to bucket: (key: %d)\n", key);
    goto out;
  }
  
  ht_dump(ht, 1);

  ht_delete(ht);

  printf("test success!\n");

  return 0;

out:
  ht_delete(ht);

  fprintf(stderr, "test fail.\n");

  return 1;
}
```
