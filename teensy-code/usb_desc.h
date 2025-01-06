#elif defined(USB_CUSTOM_CONTROLLER)
#define VENDOR_ID 0x16C0
#define PRODUCT_ID 0x0488
#define BCD_DEVICE 0x0211
#define MANUFACTURER_NAME {'l','u','p','o','n','i','x'}
#define MANUFACTURER_NAME_LEN 7
#define PRODUCT_NAME {'A','t','o','l','l',' ','(','0','x','0',')'}
#define PRODUCT_NAME_LEN 11
#define EP0_SIZE 64
#define NUM_ENDPOINTS 3
#define NUM_INTERFACE 2
#define SEREMU_INTERFACE 1 // Serial emulation
#define SEREMU_TX_ENDPOINT 2
#define SEREMU_TX_SIZE 64
#define SEREMU_TX_INTERVAL 1
#define SEREMU_RX_ENDPOINT 2
#define SEREMU_RX_SIZE 32
#define SEREMU_RX_INTERVAL 2
#define JOYSTICK_INTERFACE 2 // Joystick
#define JOYSTICK_ENDPOINT 3
#define JOYSTICK_SIZE 17 // 17 = custom game controller, 12 = normal joystick, 64 = extreme joystick
#define JOYSTICK_INTERVAL 1
#define ENDPOINT2_CONFIG ENDPOINT_RECEIVE_INTERRUPT + ENDPOINT_TRANSMIT_INTERRUPT
#define ENDPOINT3_CONFIG ENDPOINT_RECEIVE_UNUSED + ENDPOINT_TRANSMIT_INTERRUPT