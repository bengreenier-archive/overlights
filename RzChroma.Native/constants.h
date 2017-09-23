#pragma once

// ==================================
// This file serves as a single location
// wherin many default values can be set
// to avoid the need to search the code
// ==================================

// configures the logger write location
#define LOGGER_PATH "RzChroma.log"

// configures the application pipe name 
#define APP_PIPE_NAME "\\\\.\\pipe\\RzChromaData"

// configures easy enable/disable via the registry
#define APP_REG_ROOT_KEY "RzChromaData"
#define APP_REG_ENABLED_KEY "Enabled"

// configures the blocksize of the binary pipe
#define BINARY_PIPE_BLOCKSIZE 1024