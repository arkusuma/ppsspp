#include "KeyboardDevice.h"
#include "../Common/CommonTypes.h"
#include "../Core/HLE/sceCtrl.h"
#include "WinUser.h"

static const unsigned short key_ctrl_map[] = {
	VK_SPACE, CTRL_START,
	'V',      CTRL_SELECT,
	'A',      CTRL_SQUARE,
	'S',      CTRL_TRIANGLE,
	'X',      CTRL_CIRCLE,
	'Z',      CTRL_CROSS,
	'Q',      CTRL_LTRIGGER,
	'W',      CTRL_RTRIGGER,
	VK_UP,    CTRL_UP,
	VK_DOWN,  CTRL_DOWN,
	VK_LEFT,  CTRL_LEFT,
	VK_RIGHT, CTRL_RIGHT,
};
int KeyboardDevice::UpdateState() {
	float analogX = 0;
	float analogY = 0;
	for (int i = 0; i < sizeof(key_ctrl_map)/sizeof(key_ctrl_map[0]); i += 2) {
		if (!GetAsyncKeyState(key_ctrl_map[i]))
			__CtrlButtonUp(key_ctrl_map[i+1]);
		else {
			__CtrlButtonDown(key_ctrl_map[i+1]);
			switch (key_ctrl_map[i]) {
			case VK_UP:
				analogY -= .8f;
				break;
			case VK_DOWN:
				analogY += .8f;
				break;
			case VK_LEFT:
				analogX -= .8f;
				break;
			case VK_RIGHT:
				analogX += .8f;
				break;
			}
		}
	}
	__CtrlSetAnalog(analogX, analogY);
	return 0;
}