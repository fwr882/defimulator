#ifndef NALL_ARRAY_HPP
#define NALL_ARRAY_HPP

#include <stdlib.h>
#include <string.h>
#include <initializer_list>
#include <type_traits>
#include <utility>
#include <nall/algorithm.hpp>
#include <nall/bit.hpp>
#include <nall/concept.hpp>
#include <nall/foreach.hpp>
#include <nall/utility.hpp>

namespace nall {

  //dynamic vector array
  //neither constructor nor destructor is ever invoked;
  //thus, this should only be used for POD objects.
template<typename T> class array {
protected:
    T *pool;
    unsigned poolsize, buffersize;

public:
    unsigned size(void) const
        { return buffersize; }
    unsigned capacity(void) const
        { return poolsize; }

    void reset(void)
    {
        if (pool) {
            free(pool);
        }

        pool = 0;
        poolsize = 0;
        buffersize = 0;
    }

    void reserve(unsigned newsize)
    {
        if (newsize == poolsize) {
            return;
        }

        pool = (T*)realloc(pool, newsize * sizeof(T));
        poolsize = newsize;
        buffersize = min(buffersize, newsize);
    }

    void resize(unsigned newsize)
    {
        /* round reserve size up to power of 2 */
        if (newsize > poolsize) {
            reserve(bit::round(newsize));
        }
        buffersize = newsize;
    }

    T* get(unsigned minsize = 0)
    {
        if (minsize > buffersize) {
            resize(minsize);
        }
        if (minsize > buffersize) {
            throw "array[] out of bounds";
        }

        return pool;
    }

    void append(const T data)
    {
        operator[](buffersize) = data;
    }

    template<typename U> void insert(unsigned index, const U list)
    {
        unsigned listsize = container_size(list);
        resize(buffersize + listsize);
        memmove(pool + index + listsize, pool + index,
            (buffersize - index) * sizeof(T));
        foreach (item, list) {
            pool[index++] = item;
        }
    }

    void insert(unsigned index, const T item)
    {
        insert(index, array<T>{ item });
    }

    void remove(unsigned index, unsigned count = 1)
    {
        for (unsigned i = index; count + i < buffersize; i++) {
            pool[i] = pool[count + i];
        }

        /* every element >= index was removed. */
        if (count + index >= buffersize) {
            resize(index);
        }
        else resize(buffersize - count);
    }

    optional<unsigned> find(const T data)
    {
        for (unsigned i = 0; i < size(); i++) {
            if (pool[i] == data) {
                return { true, i };
            }
        }

        return { false, 0 };
    }

    void clear(void)
    {
        memset(pool, 0, buffersize * sizeof(T));
    }

    array(void) : pool(0), poolsize(0), buffersize(0) { }

    array(std::initializer_list<T> list) : pool(0), poolsize(0), buffersize(0)
    {
        for (const T *p = list.begin(); p != list.end(); ++p) {
            append(*p);
        }
    }

    ~array(void)
    {
        reset();
    }

    /* copy overload */
    array& operator=(const array &source)
    {
        if (pool) {
            free(pool);
        }

        buffersize = source.buffersize;
        poolsize = source.poolsize;
        /* Allocate entire pool size, */
        pool = (T*)malloc(sizeof(T) * poolsize);
        /* but only copy used pool objects. */
        memcpy(pool, source.pool, sizeof(T) * buffersize);

        return *this;
    }

    array(const array &source) : pool(0), poolsize(0), buffersize(0)
    {
        operator=(source);
    }

    /* Move overload */
    array& operator=(array &&source)
    {
        if (pool) {
            free(pool);
        }

        pool = source.pool;
        poolsize = source.poolsize;
        buffersize = source.buffersize;
        source.pool = 0;
        source.reset();
        return *this;
    }

    array(array &&source) : pool(0), poolsize(0), buffersize(0)
    {
        operator=(std::move(source));
    }

    /* Index overload */
    inline T& operator[](unsigned index)
    {
        if (index >= buffersize) {
            resize(index + 1);
        }

        if (index >= buffersize) {
            throw "array[] out of bounds";
        }

        return pool[index];
    }

    inline const T& operator[](unsigned index) const
    {
        if (index >= buffersize) {
            throw "array[] out of bounds";
        }
        return pool[index];
    }
};

    template<typename T> struct has_size<array<T>>
    {
        enum {
            value = true
        };
    };
}

#endif
