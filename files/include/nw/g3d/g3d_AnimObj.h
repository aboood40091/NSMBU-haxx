#pragma once

namespace nw {
    namespace g3d {
        class AnimFrameCtrl {
        public:
            float _0;
            float _4;
            float _8;
            float _C;
            void *_10;
            unsigned int _14;
        };

        class AnimObj {
        public:
            unsigned int _0;
            AnimFrameCtrl frameCtrl;
            char _1C[0x18];

            virtual ~AnimObj();
            virtual void ClearResult() = 0;
            virtual void Calc() = 0;
        };
    }
}
