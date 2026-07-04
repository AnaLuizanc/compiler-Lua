#ifndef _FRAME_ACESSO_NO_FRAME_HPP_
#define _FRAME_ACESSO_NO_FRAME_HPP_
#include "FrameAcesso.hpp" 

class FrameAcessoNoFrame : public FrameAcesso {
public:
    int posicao_no_frame;
    FrameAcessoNoFrame() { 
        posicao_no_frame = 0; 
    }
};

#endif