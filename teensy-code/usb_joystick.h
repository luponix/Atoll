#elif JOYSTICK_SIZE == 17
// 0000 0000 BBBB BBBB BBBB BBBB BBBB BBBB 
void button(uint8_t button, bool val) {
    if (--button >= 24) return;
    if (val) 
        usb_joystick_data[0] |= (1 << button);
     else 
        usb_joystick_data[0] &= ~(1 << button); 

    if (!manual_mode) usb_joystick_send();
}

void X(unsigned int val) {
	if (val > 65535) val = 65535;
	usb_joystick_data[1] = (usb_joystick_data[1] & 0xFFFF0000) | (val << 0);
	if (!manual_mode) usb_joystick_send();
}

void Y(unsigned int val) {
	if (val > 65535) val = 65535;
	usb_joystick_data[1] = (usb_joystick_data[1] & 0x0000FFFF) | (val << 16);
	if (!manual_mode) usb_joystick_send();
}

void Z(unsigned int val) {
	if (val > 65535) val = 65535;
	usb_joystick_data[2] = (usb_joystick_data[2] & 0xFFFF0000) | (val << 0);
	if (!manual_mode) usb_joystick_send();
}

void Xrotate(unsigned int val) {
	if (val > 65535) val = 65535;
	usb_joystick_data[2] = (usb_joystick_data[2] & 0x0000FFFF) | (val << 16);
	if (!manual_mode) usb_joystick_send();
}

void Yrotate(unsigned int val) {
	if (val > 65535) val = 65535;
	usb_joystick_data[3] = (usb_joystick_data[3] & 0xFFFF0000) | (val << 0);
	if (!manual_mode) usb_joystick_send();
}

void Zrotate(unsigned int val) {
	if (val > 65535) val = 65535;
	usb_joystick_data[3] = (usb_joystick_data[3] & 0x0000FFFF) | (val << 16);
	if (!manual_mode) usb_joystick_send();
}

// HHHH HHHH 0000 0000 0000 0000 0000 0000
    inline void hat(unsigned int num, int dir) {
        if (num > 1) return;
        uint32_t val = 0;
        if (dir < 0) val = 15;
        else if (dir < 23) val = 0;
        else if (dir < 68) val = 1;
        else if (dir < 113) val = 2;
        else if (dir < 158) val = 3;
        else if (dir < 203) val = 4;
        else if (dir < 245) val = 5;
        else if (dir < 293) val = 6;
        else if (dir < 338) val = 7;
		usb_joystick_data[0] = (usb_joystick_data[0] & (num == 0 ? 0xF0FFFFFF : 0x0FFFFFFF)) | (val << (24 + num * 4));
        if (!manual_mode) usb_joystick_send();
	}
