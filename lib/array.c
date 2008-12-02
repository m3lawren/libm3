#include <array.h>

#include <assert.h>
#include <errno.h>
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
int array_destroy(struct array* a) {
	if (!a) {
		return EINVAL;
	}

	if (a->a) {
		free(a->a);
	}
	free(a);

	return 0;
}

/*****************************************************************************/
int array_reserve(struct array* a, unsigned int sz) {
	void** newa;
	unsigned int nsz = a->sz ? a->sz : 1;

	if (!a) {
		return EINVAL;
	}

	if (a->sz >= sz) {
		return 0;
	}

	while (nsz < sz) {
		nsz <<= 1;
	}

	newa = realloc(a->a, nsz * sizeof(void*));

	if (!newa) {
		return ENOMEM;
	}

	a->a = newa;
	a->sz = nsz;

	return 0;
}

/*****************************************************************************/
int array_resize(struct array* a, unsigned int num) {
	int result;

	if (a == NULL) {
		return EINVAL;
	}

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
	if (!a) {
		return 0;
	}

	return a->num;
}

/*****************************************************************************/
int array_set(struct array* a, unsigned int i, void* v) {
	if (a == NULL) {
		return EINVAL;
	}
	if (i >= a->num) {
		return EINVAL;
	}

	a->a[i] = v;
	return 0;
}

/*****************************************************************************/
int array_get(const struct array* a, unsigned int i, void** ret) {
	if (ret == NULL) {
		return EINVAL;
	}

	*ret = NULL;

	if (a == NULL) {
		return EINVAL;
	}
	if (i >= a->num) {
		return EINVAL;
	}

	*ret = a->a[i];

	return 0;
}

/*****************************************************************************/
int array_append(struct array* a, void* v) {
	if (a == NULL) {
		return EINVAL;
	}

	return array_insert(a, v, a->num);
}

/*****************************************************************************/
int array_insert(struct array* a, void* v, unsigned int i) {
	int result;

	if (a == NULL) {
		return EINVAL;
	}
	if (i > a->num) {
		return EINVAL;
	}

	if ((result = array_resize(a, a->num + 1))) {
		return result;
	}

	memmove(&a->a[i + 1], &a->a[i], (a->num - i - 1) * sizeof(void*));

	a->a[i] = v;

	return 0;
}
