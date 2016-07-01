#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "kvsns.h"

int main(int argc, char *argv[])
{
	int rc;
	kvsns_ino_t ino;
	kvsns_ino_t parent;
	char key[KLEN];
	char val[VLEN];

	rc = kvsns_init();
	if (rc != 0) {
		fprintf(stderr, "kvsns_init: err=%d\n", rc);
		exit(1);
	}

	/* KVS FUNCTIONS */
	rc = kvsns_next_inode(&ino);
	if (rc != 0) {
		fprintf(stderr, "kvsns_next_inode: err=%d\n", rc);
		exit(1);
	}
	printf("kvsns_next_inode: ino=%llu\n", ino);

	rc = kvshl_set_char("test", "value");
	if (rc != 0) {
		fprintf(stderr, "kvsns_set_char: err=%d\n", rc);
		exit(1);
	}

	rc = kvshl_get_char("test", val);
	if (rc != 0) {
		fprintf(stderr, "kvsns_get_char: err=%d\n", rc);
		exit(1);
	}
	printf("kvshl_get_char: val=%s\n", val);

	rc = kvshl_del("test");
	if (rc != 0) {
		fprintf(stderr, "kvsns_get_char: err=%d\n", rc);
		exit(1);
	}
	printf("kvshl_get_char after del: %d\n", kvshl_get_char("test", val)); 

	/* NS FUNCTION */
	parent = 2LL;
	rc = kvsns_mkdir(&parent, "mydir", &ino);
	if (rc != 0) {
		if (rc == -EEXIST)
			printf("dirent exists \n");
		else {
			fprintf(stderr, "kvsns_mkdir: err=%d\n", rc);
			exit(1);
		}
	}
	printf("===> New Ino = %llu\n", ino);

	rc = kvsns_lookup(&parent, "mydir", &ino);
	if (rc != 0) {
		fprintf(stderr, "kvsns_mkdir: err=%d\n", rc);
		exit(1);
	}
	printf("====> INO LOOKUP = %llu\n", ino);

	return 0;

}