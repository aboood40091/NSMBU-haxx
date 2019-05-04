extern "C" {
    void callCtors() {
        unsigned int *ctors = (unsigned int *)(DATA_ADDR + 0x20004);
        unsigned int count = ctors[0];
        for (int i = 0; i < count; i++) {
            ((void (*)())(ctors[i + 1]))();
        }
    }
}
