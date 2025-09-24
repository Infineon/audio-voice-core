# Audio voice core library
Audio voice core middleware consists of core audio algorithm implementation. It contains core algorithm implementation for speech-onset-detection, low-power wake word detection, and audio front-end.

## Supported platforms
PSoC&trade; Edge E84 MCU

## Quick start
This repo cannot be used by the application directly and will be pulled by the audio middleware for internal use.

Define the AVC (Audio Voice Core) component in the application's makefile. Choose one of the following options:

```makefile
COMPONENTS+=AVC_DEMO   # Limited functionality for evaluation
# or
COMPONENTS+=AVC_FULL   # Full AVC capabilities (production use)
```

Note: AVC_DEMO provides limited functionality for evaluation purposes. For production use with full AVC capabilities, use AVC_FULL. Contact Infineon support for licensing information and access to the full version.

## Additional information
* [Audio voice core RELEASE.md](./RELEASE.md)
* [Audio voice core library version](./version.txt)