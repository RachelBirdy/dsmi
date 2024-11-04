#include <nds.h>
#include <dswifi7.h>

#include "psg.h"
#include "../../generic/midimsg.h"

volatile bool exit_loop = false;

void power_button_callback(void)
{
	exit_loop = true;
}

// Thanks to LiraNuna for this cool function
void PM_SetRegister(int reg, int control)
{
    SerialWaitBusy();
    REG_SPICNT = SPI_ENABLE | SPI_DEVICE_POWER |SPI_BAUD_1MHz | SPI_CONTINUOUS;
    REG_SPIDATA = reg;
    SerialWaitBusy();
    REG_SPICNT = SPI_ENABLE | SPI_DEVICE_POWER |SPI_BAUD_1MHz;
    REG_SPIDATA = control;
}

void VcountHandler() {
	inputGetAndSend();
}

void VblankHandler(void) {
	Wifi_Update();
	psg_update();
}

void midiHandler(int num_bytes, void * userdata) {
	MidiMsg midimsg;
	fifoGetDatamsg(FIFO_MIDI, num_bytes, (u8*)&midimsg);
	psg_midimsg(midimsg.msg, midimsg.data1, midimsg.data2);
}

int main() {
	readUserSettings();
	ledBlink(0);
	touchInit();

	irqInit();
	fifoInit();

	// Start the RTC tracking IRQ
	initClockIRQ();

	SetYtrigger(80);
	setPowerButtonCB(power_button_callback);

	installSystemFIFO();
	installWifiFIFO();
	fifoSetDatamsgHandler(FIFO_MIDI, midiHandler, 0);

	irqSet(IRQ_VCOUNT, VcountHandler);
	irqSet(IRQ_VBLANK, VblankHandler);

	psg_init();

	irqEnable(IRQ_VBLANK | IRQ_VCOUNT | IRQ_NETWORK);

	PM_SetRegister(0, 9);

	while (!exit_loop)
	{
		const uint16_t key_mask = KEY_SELECT | KEY_START | KEY_L | KEY_R;
		uint16_t keys_pressed = ~REG_KEYINPUT;

		if ((keys_pressed & key_mask) == key_mask)
			exit_loop = true;

		swiWaitForVBlank();
	}
}
