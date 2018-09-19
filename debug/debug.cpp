
#pragma comment( lib , "SceFios2_stub_weak")

#include <cstdio>
#include <string>
#include <fios2\fios2_api.h>
#include "syscall.h"

extern "C" {
#include "unjail.h"
}

#define LIBRARY_IMPL (1)
#include "debug.h"

// What's the time ?
typedef struct tm Time;

// Path to the log file.
static char *logPath;

// Determine if this process is already unjailed.
static bool jb = false;

// Determine if a log file would already be initialized.
static bool init = false;

// Unjail this process.
void freedom(void) {
	struct thread td;
	syscall(11, (void *)&unjail, &td);
}

// Does folder exists ?
bool Exists(const char *path) {
	// Is pointer or string emtpy, return false.
	if (*path == '\0') return false;
	else if (path[0] == '\0') return false;

	// Try to open the directory.
	bool exists;
	SceFiosOp dir = sceFiosDirectoryExists(NULL, path, &exists);
	sceFiosOpDelete(dir);
	return exists;
}

// Get available usb device.
std::string getUsb(void) {
	std::string usb_path;
	while (true) {
		if (Exists("/mnt/usb0")) {
			usb_path = std::string("/mnt/usb0/");
			break;
		} else if (Exists("/mnt/usb0")) {
			usb_path = std::string("/mnt/usb1/");
			break;
		}
	}
	return usb_path;
}

/* Generate a time String and retur nit. */
std::string getTimeString(void) {
	char timeBuffer[16];
	memset(timeBuffer, 0, sizeof(timeBuffer));
	time_t t;
	Time *tm;
	time(&t);
	tm = localtime(&t);
	strftime(timeBuffer, sizeof(timeBuffer), "%H_%M_%S", tm);
	std::string result = timeBuffer;
	return result;
}

// initialize.
bool initialize(void) {
	std::string path = getUsb();
	path += "debug_";
	path += getTimeString();
	path += ".log";
	FILE *fd = fopen(path.c_str(), "ab+");
	if (!fd) return false;
	fclose(fd);
	logPath = strdup(path.c_str());
	return init = true;
}

// Initliaze the debug logger.
PRX_INTERFACE int dinit(void) {
	// Chec kif this process hase GOD abillity.
	if (!jb) {
		int uid = syscall(24);
		if (uid != 0) freedom();
		jb = true;
	}

	// Initialize if needed.
	if (!init) {
		if (!initialize()) return 1;
	}
	return 0;
}

// Write a debug message into the log.
PRX_INTERFACE int debug(const char *format, ...) {
	// Log the Message.
	FILE *fd = fopen(logPath, "a");
	if (fd) {
		va_list args;
		va_start(args, format);
		vfprintf(fd, format, args);
		va_end(args);
		fclose(fd);
		return 0;
	}
	return 1;
}

// Free used resources.
PRX_INTERFACE void dfinalize(void) { if (init) free(logPath); }