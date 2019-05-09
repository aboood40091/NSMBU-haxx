#pragma once

namespace sead {
    class ListNode {
    public:
        sead::ListNode* previous;
        sead::ListNode* next;
    };

    class ListImpl {
    public:
        sead::ListNode root;
        int count;
        unsigned int nodeOffset;
    };
};
