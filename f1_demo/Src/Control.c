//
// Created by Administrator on 2020/6/28.
//

#include "Control.h"
#include "KeyBoard.h"
#include "Tx433Lin.h"
#include "Tx433Remote.h"
#include "keeloq_lock.h"
#include "stdio.h"
#include "Rx433Remote.h"
extern  SYSTEM_DATA sdat;


void KeyMenu(void)
{
    u32 pas;
    u8 i;
   Rx433IrDispose();
    switch(keys.key_num) {
        case K_SET_P:
            keys.key_num = 0;
            AskOpen(5);
        case K_SET_R:
            keys.key_num = 0;
            LED0_RESET;
            break;
        case K_SET_C:
            keys.key_num = 0;
            break;

    }
}



void Rx433LinCtrl(){

}



