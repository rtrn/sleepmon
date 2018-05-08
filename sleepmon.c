#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include "args.h"

void	sysfatal(char*, ...);

int
main(int argc, char *argv[])
{
	int lock;
	HWND hwnd;

	lock = 0;
	ARGBEGIN{
	case 'l':
		lock = TRUE;
		break;
	default:
		goto Usage;
	}ARGEND

	if(argc != 0)
		goto Usage;

	hwnd = FindWindow(0, 0);
	if(hwnd == NULL)
		sysfatal("failed to find window");
	if(lock)
		if(!LockWorkStation())
			sysfatal("failed to lock workstation");
	sleep(1);
	if(SendMessage(hwnd, WM_SYSCOMMAND, SC_MONITORPOWER, 2) != 0)
		sysfatal("failed to put screen to sleep");
	exit(0);

    Usage:
	fprintf(stderr, "usage: sleepmon [-l]\n");
	exit(1);
}

void
sysfatal(char *fmt, ...)
{
	va_list arg;

	va_start(arg, fmt);
	fprintf(stderr, "sleepmon: ");
	vfprintf(stderr, fmt, arg);
	fprintf(stderr, "\n");
	va_end(arg);
	exit(1);
}
