// SPDX-License-Identifier: AGPL-3.0-or-later
#include <psyz.h>

// Allows overlays on Windows to use the logging library.
// Without this, any function from the main executable that uses logging,
// cannot be called without causing an error during linking.
LOG_LEVEL psyz_logLevel = LOG_LEVEL_W;
