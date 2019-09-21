#ifndef _H_CTK_CONSOLE_CHAR
#define _H_CTK_CONSOLE_CHAR
struct ConsoleCell
{
	char c { 0 };
	float r { 0xff };
	float g { 0xff };
	float b { 0xff };
	float back_r { 0x00 };
	float back_g { 0x00 };
	float back_b { 0x00 };
};
#endif
