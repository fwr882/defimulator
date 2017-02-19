#ifndef NALL_STRING_STRL_HPP
#define NALL_STRING_STRL_HPP

namespace nall {

//strlcpy, strlcat based on OpenBSD implementation by Todd C. Miller

//return = strlen(src)
unsigned strlcpy(char *dest, const char *src, unsigned length)
{
    char *d = dest;
    const char *s = src;
    unsigned n = length;

    /* copy as many bytes as possible, or until null reached. */
    if (n) {
        while (--n && (*d++ = *s++));
    }

    if (!n) {
        if (length) {
            *d = 0;
        }
        /* traverse rest of s, so that s - src == strlen(src) */
        while (*s++);
    }

    /* return length of copied string, sans null terminator. */
    return (s - src - 1);
}

//return = strlen(src) + min(length, strlen(dest))
unsigned strlcat(char *dest, const char *src, unsigned length)
{
    char *d = dest;
    const char *s = src;
    unsigned n = length;

    /* find end of dest */
    while (n-- && *d) {
        d++;
    }

    unsigned dlength = d - dest;
    /* subtract length of dest from maximum string length */
    n = length - dlength;

    if (!n) {
        return dlength + strlen(s);
    }

    while (*s) {
        if (n != 1) {
            *d++ = *s;
            n--;
        }
        s++;
    }

    *d = 0;

    /* return length of resulting string, sans null terminator */
    return dlength + (s - src);
}

}

#endif
