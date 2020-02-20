typedef void (*InitFunc)();
extern InitFunc _ctors[];

extern "C" {
    void callCtors() {
        static bool initialized = false;
        if (initialized)
            return;

        initialized = true;
        for (int i = 0; _ctors[i]; i++)
            (*_ctors[i])();
    }
}
