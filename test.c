#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "src/map.h"

struct test {
	int i;
	int j;
	char k[2];
};

map_int_t g_int;
map_str_t g_str;
map_void_t g_void;

void fill_buffer(char *buf, int len)
{
	int i;
	for(i = 0; i < len; i++) {
		buf[i] = i%26+0x61;
	}
	buf[len - 1] = '\0';
}

void fill_stru(struct test *buf, int i)
{
	buf->i = i;
	buf->j = i + 1;
	buf->k[0] = i;
	buf->k[1] = i + 1;
}

int main()
{
	char ch;
	/*test int map*/
	printf("test int map\n");
	map_init(&g_int);
	map_set(&g_int, "testkey",123);
	int *val = map_get(&g_int, "testkey");
	printf("val is %d\n", *val);
	map_deinit(&g_int);


	printf("input a to continue\n");
	while (ch != 'a') {
		ch = getchar();
	}
	/* test str map*/
	printf("test str map\n");
	printf("init and malloc string buffer\n");

	map_init(&g_str);
	int i;
	char key[64];
	for(i = 0; i < 10000; i++) {
		snprintf(key, 63, "key%d",i);
		char *str = (char *)malloc(128);
		fill_buffer(str, 128);
		map_set(&g_str, key, str);
	}
	printf("input b to continue\n");
	printf("test read and remove string buffers\n");
	while (ch != 'b') {
		ch = getchar();
	}
	for(i = 0; i < 10000; i++) {
		snprintf(key, 63, "key%d",i);
		char **ret = map_get(&g_str, key);
		printf("ret is %s\n", *ret);
		free(*ret);
		//free(ptr[i]);
		map_remove(&g_str, key);
	}
	printf("input c to continue\n");
	while (ch != 'c') {
		ch = getchar();
	}
	printf("deinit map\n");
	map_deinit(&g_str);
	printf("input d to continue\n");
	while (ch != 'd') {
		ch = getchar();
	}

	printf("test void map\n");
	printf("init and prepare data\n");
	map_init(&g_void);
	for(i = 0; i < 10000; i++) {
		snprintf(key, 63, "key%d",i);
		struct test *stru = (struct test *)malloc(sizeof(struct test));
		fill_stru(stru, i);
		map_set(&g_void, key, (void *)stru);
	}
	printf("input e to continue\n");
	printf("test read and remove structure buffers\n");
	while (ch != 'e') {
		ch = getchar();
	}
	for(i = 0; i < 10000; i++) {
		snprintf(key, 63, "key%d",i);
		struct test **ret = (struct test **)map_get(&g_void, key);
		printf("ret:i = %d, j = %d, k[0] = %d, k[1] = %d\n", (*ret)->i,(*ret)->j,(*ret)->k[0],(*ret)->k[1]);
		free(*ret);
		map_remove(&g_void, key);
	}
	printf("input f to continue\n");
	while (ch != 'f') {
		ch = getchar();
	}
	printf("deinit map\n");
	map_deinit(&g_void);
	printf("input g to exit\n");
	while (ch != 'g') {
		ch = getchar();
	}
	return 0;
}
