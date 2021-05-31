# hashtable
Hashtable is O(1) data structure library. Use in threads you must use lock(mutex). (same as in the case of STL(C++))

* autoscale bucket
* maximum number of buckets can be specified when creating (may be useful in environments with severe memory constraints)
* insert, erase, find (execution completed within O(1) time)

And you need **gcc, make, cmake** installed to compile. 

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

  if ( !(ht = ht_create(0 /* use default size(16) */,0 /* use default size(8) */)) ) {
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
# build & test
```
[maze@kercube 12:15:50 hashtable]$ ./c.sh 
-- The C compiler identification is GNU 10.3.0
-- The CXX compiler identification is GNU 10.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/maze/git/hashtable
[maze@kercube 12:15:52 hashtable]$ make
Scanning dependencies of target test
[ 20%] Building C object CMakeFiles/test.dir/test.c.o
[ 40%] Building C object CMakeFiles/test.dir/hashtable.c.o
[ 60%] Building C object CMakeFiles/test.dir/halfsiphash.c.o
[ 80%] Building C object CMakeFiles/test.dir/hashtable_error.c.o
[100%] Linking C executable test
[100%] Built target test
[maze@devcube 12:01:02 hashtable]$ ./test 10
curr_buckets_size:       16
max_buckets_size:        1024
bucket_count:            0
bucket[0] link count: empty
bucket[1] link count: empty
bucket[2] link count: empty
bucket[3] link count: empty
bucket[4] link count: empty
bucket[5] link count: empty
bucket[6] link count: empty
bucket[7] link count: empty
bucket[8] link count: empty
bucket[9] link count: empty
bucket[10] link count: empty
bucket[11] link count: empty
bucket[12] link count: empty
bucket[13] link count: empty
bucket[14] link count: empty
bucket[15] link count: empty
test success!
[maze@devcube 12:01:06 hashtable]$ 
```
