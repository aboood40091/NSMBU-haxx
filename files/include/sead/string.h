#pragma once

/*
    Current String implementation
    taken from Newer U.
    TODO: add the actual definition for string classes
*/

namespace sead {
    class String {
    public:
        const char *str;

        String(const char *str) {
            this->str = (char *)str;
        }
    };
};
