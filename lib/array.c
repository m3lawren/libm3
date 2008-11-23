#include <array.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct array {
	void** a;
	unsigned int sz;
	unsigned int num;
};

/*****************************************************************************/
struct array* array_create() {
	struct array* a = malloc(sizeof(struct array));

	if (!a) {
		return NULL;
	}

	a->a = NULL;
	a->sz = a->num = 0;

	return a;
}

/*****************************************************************************/
void array_destroy(struct array* a) {
	if (!a) {
		return;
	}

	if (a->a) {
		free(a->a);
	}
	free(a);
}

/*****************************************************************************/
int array_reserve(struct array* a, unsigned int sz) {
	void** newa;
	unsigned int nsz = sz ? sz : 1;

	assert(a != NULL);

	if (a->sz >= sz) {
		return 0;
	}

	while (nsz < sz) {
		nsz <<= 1;
	}

	newa = realloc(a->a, nsz);

	if (!newa) {
		return -1;
	}

	a->a = newa;
	a->sz = nsz;

	return 0;
}

/*****************************************************************************/
int array_resize(struct array* a, unsigned int num) {
	int result;

	assert(a != NULL);

	if (num < a->num) {
		a->num = num;
		return 0;
	}

	if ((result = array_reserve(a, num))) {
		return result;
	}

	memset(&a->a[a->num], (num - a->num) * sizeof(void*), 0);

	a->num = num;
	return 0;
}

/******************************************************************************/
unsigned int array_size(const struct array* a) {
	assert(a != NULL);

	return a->num;
}

/*****************************************************************************/
void array_set(struct array* a, unsigned int i, void* v) {
	assert(a != NULL);
	assert(i < a->num);

	a->a[i] = v;
}

/*****************************************************************************/
void* array_get(const struct array* a, unsigned int i) {
	assert(a != NULL);
	assert(i < a->num);

	return a->a[i];
}

/*****************************************************************************/
int array_append(struct array* a, void* v) {
	assert(a != NULL);

	return array_insert(a, v, a->num);
}

/*****************************************************************************/
int array_insert(struct array* a, void* v, unsigned int i) {
	int result;

	assert(a != NULL);
	assert(i <= a->num);

	if ((result = array_resize(a, a->num + 1))) {
		return result;
	}

	memmove(&a->a[i + 1], &a->a[i], (i - a->num) * sizeof(void*));

	a->a[i] = v;

	return 0;
}
