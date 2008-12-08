#ifndef _ARRAY_H_
#define _ARRAY_H_

/*
 * Simple dynamic-size array structure.
 */

struct array;

/*
 * _reserve - Reserves enough space within the data structure to guarantee
 *            that up to the specified number of elements can be stored, but 
 *            does not change the number of elements currently in the array.
 *            Returns 0 on success.
 * _resize  - Changes the number of elements in the array to the specified
 *            amount, truncating at the end if needed. Returns 0 on success.
 * _size    - Returns the number of elements in the array.
 * _set     - Sets the specified index in the array.
 * _get     - Returns the value at the specified index.
 * _append  - Adds the specified value to the end of the array. Returns 0 on 
 *            success.
 * _insert  - Inserts the specified value into the array at the given index,
 *            moving all elements after that index to the right to make room.
 *            Returns 0 on success.
 */
struct array* array_create(void);
int           array_destroy(struct array*);
int           array_reserve(struct array*, unsigned int);
int           array_resize(struct array*, unsigned int);
unsigned int  array_size(const struct array*);
int           array_set(struct array*, unsigned int, void*);
int           array_get(const struct array*, unsigned int, void**);
int           array_append(struct array*, void*);
int           array_insert(struct array*, void*, unsigned int);

#endif
