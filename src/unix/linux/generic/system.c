// Copyright (c) Christopher D. Dickson <cdd@matoya.group>
//
// This Source Code Form is subject to the terms of the MIT License.
// If a copy of the MIT License was not distributed with this file,
// You can obtain one at https://spdx.org/licenses/MIT.html.

#include "matoya.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <unistd.h>

#include "tlocal.h"

void MTY_ProtocolHandler(const char *uri, void *token)
{
	const char *fmt = "xdg-open \"%s\" 2> /dev/null &";

	size_t size = snprintf(NULL, 0, fmt, uri) + 1;

	char *cmd = MTY_Alloc(size, 1);
	snprintf(cmd, size, fmt, uri);

	if (system(cmd) == -1)
		MTY_Log("'system' failed with errno %d", errno);

	MTY_Free(cmd);
}

uint32_t MTY_GetPlatform(void)
{
	return MTY_OS_LINUX;
}

uint32_t MTY_GetPlatformNoWeb(void)
{
	return MTY_GetPlatform();
}

const char *MTY_ProcessPath(void)
{
	char tmp[MTY_PATH_MAX] = {0};

	ssize_t n = readlink("/proc/self/exe", tmp, MTY_PATH_MAX - 1);
	if (n < 0) {
		MTY_Log("'readlink' failed with errno %d", errno);
		return "/app";
	}

	return mty_tlocal_strcpy(tmp);
}

bool MTY_RestartProcess(char * const *argv)
{
	execv(MTY_ProcessPath(), argv);
	MTY_Log("'execv' failed with errno %d", errno);

	return false;
}