extern "C" {
    void callCtors() {
        unsigned int *ctors;

        #ifdef Cemu
        ctors = (unsigned int *)(*(unsigned int *)(DATA_ADDR - 4));
        #else
        ctors = (unsigned int *)(DATA_ADDR + 0x20004);
        #endif

        unsigned int count = ctors[0];
        for (int i = 0; i < count; i++) {
            ((void (*)())(ctors[i + 1]))();
        }
    }
}
