#elif JOYSTICK_SIZE == 17
static uint8_t joystick_report_desc[] = {
      0x05, 0x01,       // Usage Page (Generic Desktop)
      0x09, 0x04,       // Usage (Joystick)
      0xA1, 0x01,       // Collection (Application)
        // Buttons (24 buttons, 3 bytes)
            0x15, 0x00,       // Logical Minimum (0)
            0x25, 0x01,       // Logical Maximum (1)
            0x75, 0x01,       // Report Size (1 bit for each button)
            0x95, 0x18,       // Report Count (24 buttons)
            0x05, 0x09,       // Usage Page (Button)
            0x19, 0x01,       // Usage Minimum (Button #1)
            0x29, 0x18,       // Usage Maximum (Button #24)
            0x81, 0x02,       // Input (variable, absolute)
        // 2x 4 bit Hat switches
            0x15, 0x00,                     //   Logical Minimum (0)
            0x25, 0x07,                     //   Logical Maximum (7)
            0x35, 0x00,                     //   Physical Minimum (0)
            0x46, 0x3B, 0x01,               //   Physical Maximum (315)
            0x75, 0x04,                     //   Report Size (4)
            0x95, 0x02,                     //   Report Count (2)
            0x65, 0x14,                     //   Unit (20)
            0x05, 0x01,                     //   Usage Page (Generic Desktop)
            0x09, 0x39,                     //   Usage (Hat switch)
            0x09, 0x39,                     //   Usage (Hat switch)
            0x81, 0x42,                     //   Input (variable,absolute,null_state)
        // 16 bit Axes X Y Z X2 Y2 Z2
            0x05, 0x01,       // Usage Page (Generic Desktop)
            0x09, 0x01,       // Usage (Pointer)
            0xA1, 0x00,       // Collection ()
            0x15, 0x00,       // Logical Minimum (0)
            0x27, 0xFF, 0xFF, 0, 0,         // Logical Maximum (65535)
            0x75, 0x10,       // Report Size (16 bits)
            0x95, 0x06,       // Report Count (6 axes)
            0x09, 0x30,       // Usage (X)
            0x09, 0x31,       // Usage (Y)
            0x09, 0x32,       // Usage (Z)
            0x09, 0x33,       // Usage (Rx)
            0x09, 0x34,       // Usage (Ry)
            0x09, 0x35,       // Usage (Rz)
            0x81, 0x02,       // Input (variable, absolute)
            0xC0,             // End Collection

            0x75, 0x01,       // Report Size 
            0x95, 0x08,       // Report Count 
            0x81, 0x03,       // Input (constant, variable, absolute)
      0xC0,             // End DEVICE Collection
};