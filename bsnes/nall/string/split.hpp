#ifndef NALL_STRING_SPLIT_HPP
#define NALL_STRING_SPLIT_HPP

namespace nall {

template<unsigned Limit> void lstring::split(const char *key, const char *src)
{
    unsigned limit = Limit;
    reset();

    int ssl = strlen(src), ksl = strlen(key);
    int lp = 0, split_count = 0;

    for (int i = 0; i <= ssl - ksl;) {
        if (!memcmp(src + i, key, ksl)) {
            strlcpy(operator[](split_count++), src + lp, i - lp + 1);
            i += ksl;
            lp = i;
            if (!--limit) {
                break;
            }
        } else {
            i++;
        }
    }

    operator[](split_count++) = src + lp;
}

template<unsigned Limit> void lstring::qsplit(const char *key, const char *src)
{
    unsigned limit = Limit;
    reset();

    int ssl = strlen(src), ksl = strlen(key);
    int lp = 0, split_count = 0;

    for (int i = 0; i <= ssl - ksl;) {
        uint8_t x = src[i];

        if (x == '\"' || x == '\'') {
            /* skip opening quote */
            int z = i++;
            while (i < ssl && src[i] != x) {
                i++;
            }

            if (i >= ssl) {
                /* failed match, rewind i */
                i = z; 
            } else {
                /* skip closing quote, restart in 
                * case next char is also a quote */
                i++;
                continue;
            }
        }

        if (!memcmp(src + i, key, ksl)) {
            strlcpy(operator[](split_count++), src + lp, i - lp + 1);
            i += ksl;
            lp = i;
            if (!--limit) {
                break;
            }
        } else {
            i++;
        }
    }

    operator[](split_count++) = src + lp;
}

};

#endif
