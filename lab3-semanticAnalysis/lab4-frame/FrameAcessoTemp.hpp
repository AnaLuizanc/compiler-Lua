#ifndef _FRAME_ACESSO_TEMP_HPP_
#define _FRAME_ACESSO_TEMP_HPP_
#include "FrameAcesso.hpp" 

class FrameAcessoTemp : public FrameAcesso {
public:
    int id; 
    FrameAcessoTemp() { 
        id = 0; 
    }
};

#endif