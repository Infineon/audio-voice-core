# Audio voice core library

Audio voice core middleware consists of core audio algorithm implementation. It contains core algorithm implementation for speech-onset-detection, low-power wake word detection, and audio front-end.

This repository provides core libraries designed to integrate with Infineon middleware. In addition, utility modules such as ASRC, AGC, and LPF are provided, which can be directly utilized by applications for standalone audio processing tasks.

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

## Utility Modules
The following utilities can be used directly by applications. Refer to their specific README files for details:

- [ASRC Utility](./docs/ASRC-README.md)
- [AGC Utility](./docs/AGC-README.md)
- [LPF Utility](./docs/LPF-README.md)
- [HPF Utility](./docs/HPF-README.md)