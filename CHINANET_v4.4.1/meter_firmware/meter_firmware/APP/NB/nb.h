#ifndef __NB_H
#define __NB_H
#include "sys.h"
#include "usart.h"

#define TRUE  1
#define FALSE 0

extern u8 scrambling(u8 status);

extern u8 nb_upload(u8 meter_id);
extern u8 nb_receive(void);
extern u8 nb_connect_cloud(void);
extern u8 nb_fresh(void);
extern u8 nb_frequence(void);
extern u8 nb_get_metercode(void);
#endif