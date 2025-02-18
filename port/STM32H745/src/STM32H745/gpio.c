#include "titan/gpio.h"
#include "STM32H745/resource/mmio.h"

#define PORTS 11
#define PINS 16
// let A = 0, B = 1, --- , K = 10
// Port [A:K] = [0:10]

// Entries in this table are the pin numbers.  
// int32_t pins[PORTS][PINS] = {
//    PIN # Within Port
//    0   0   0   0   0   0   0   0   0   0   1   1   1   1   1   1
//    0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5     PORT
//   {37 ,38 ,39 ,40 ,43 ,44 ,45 ,46 ,97 ,98 ,99 ,100,101,102,107,108}, // A
//   {49 ,50 ,51 ,130,131,132,133,134,136,137,66 ,67 ,72 ,73 ,74 ,75 }, // B
//   {28 ,29 ,0  ,0  ,47 ,48 ,93 ,94 ,95 ,96 ,109,110,111,9  ,10 ,11 }, // C
//   {112,113,114,115,116,117,120,121,76 ,77 ,78 ,81 ,82 ,83 ,84 ,85 }, // D
//   {138,139,1  ,2  ,3  ,4  ,5  ,57 ,58 ,59 ,60 ,61 ,62 ,63 ,64 ,65 }, // E
//   {0  ,0  ,0  ,0  ,0  ,0  ,20 ,21 ,22 ,23 ,24 ,52 ,0  ,0  ,53 ,54 }, // F
//   {0  ,0  ,0  ,0  ,0  ,0  ,86 ,87 ,88 ,122,123,124,125,126,127,0  }, // G
//   {25 ,26 ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  }, // H
//   {0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  }, // I
//   {0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  }, // J
//   {0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  }, // K
// };

/**
 * port_index_from_pin[overall pin #] = 100 * port + PIN # Within Port
 * -1 if pin doesn't exist
*/
int32_t port_index_from_pin[140] = {-1,402,403,404,405,406,-1,-1,-1,213,
                                    214,215,-1,-1,-1,-1,-1,-1,-1,-1,
                                    506,507,508,509,510,700,701,-1,200,201,
                                    -1,-1,-1,-1,-1,-1,-1,0,1,2,
                                    3,-1,-1,4,5,6,7,204,205,100,
                                    101,102,511,514,515,-1,-1,407,408,409,
                                    410,411,412,413,414,415,110,111,-1,-1,
                                    -1,-1,112,113,114,115,308,309,310,-1,
                                    -1,311,312,313,314,315,606,607,608,-1,
                                    -1,-1,-1,206,207,208,209,8,9,10,
                                    11,12,13,-1,-1,-1,-1,14,15,210,
                                    211,212,300,301,302,303,304,305,-1,-1,
                                    306,307,609,610,611,612,613,614,-1,-1,
                                    103,104,105,106,107,-1,108,109,400,401};

static const int32_t _GPIO_PORT_COUNT = 11;

// Initializes gpio peripheral
bool init_gpio(void) {
  for (int32_t i = 0; i < _GPIO_PORT_COUNT; i++) {
    const field32_t cur_field = MAKE_FIELD(field32_t, i, 1);
    WRITE_FIELD(RCC_AHB4ENR, cur_field, 1U);
  }
  return true;
}

void tal_set_mode(int pin, int mode)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ // This means this pin number isn't on the board
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;

  WRITE_FIELD(GPIOx_MODER[port], GPIOx_MODER_MODEx[index], mode);
}

void tal_set_drain(int pin, int drain)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ // This means this pin number isn't on the board
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;

  WRITE_FIELD(GPIOx_OTYPER[port], GPIOx_OTYPER_OTx[index], drain);
}

void tal_set_speed(int pin, int speed)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ // This means this pin number isn't on the board
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;

  WRITE_FIELD(GPIOx_OSPEEDR[port], GPIOx_OSPEEDR_OSPEEDx[index], speed);
}


void tal_pull_pin(int pin, int pull)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ 
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;

  switch (pull)
  {
    case 1:{
      WRITE_FIELD(GPIOx_PUPDR[port], GPIOx_PUPDR_PUPDx[index], 1);
      break;
    }
    case 0:{
      WRITE_FIELD(GPIOx_PUPDR[port], GPIOx_PUPDR_PUPDx[index], 0);
      break;
    }
    case -1:{
      WRITE_FIELD(GPIOx_PUPDR[port], GPIOx_PUPDR_PUPDx[index], 2);
      break;
    }
    
    default:{
      break;
    }
  }
}

void tal_set_pin(int pin, int value)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ 
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;
  WRITE_FIELD(GPIOx_ODR[port], GPIOx_ODR_ODx[index], value);
}

void tal_alternate_mode(int pin, int value)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ 
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;

  if(index <= 7){
    // use AFRL
    WRITE_FIELD(GPIOx_AFRL[port], GPIOx_AFRL_AFSELx[index], value);

  }else{
    // use AFRH
    WRITE_FIELD(GPIOx_AFRH[port], GPIOx_AFRH_AFSELx[index - 8], value); 
  }
}

bool tal_read_pin(int pin)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ 
    return false;  // throw error
  }
  int port = v / 100;
  int index = v - 100 * port;

  uint32_t read_val = READ_FIELD(GPIOx_IDR[port], GPIOx_IDR_IDx[index]);
  
  return read_val == 1;
}

// add read and write buffer as well