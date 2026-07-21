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
COMPONENTS+=AVC_FULL   # Full capabilities for production use
```

Note: AVC_DEMO provides limited functionality for evaluation purposes. For production use with full AVC capabilities, use AVC_FULL. Contact Infineon support for licensing information and access to the full version.

## VA Max Command Component

The VA library supports up to 100 voice commands by default. For applications requiring more commands (up to 250), the `COMPONENT_MAXCMD` variant is available for CM55 only.

To use the extended command set, add the following component and ignore the default 100-command library in the application's makefile:

```makefile
COMPONENTS+=MAXCMD
CY_IGNORE+= $(SEARCH_audio-sw-codecs)/lib/SP_ENH/COMPONENT_CM55/COMPONENT_AVC_DEMO/COMPONENT_HARDFP/TOOLCHAIN_ARM/ifx_va.ar

```

Note: Adjust the `CY_IGNORE` path to match your configuration (AVC_DEMO/AVC_FULL, SOFTFP/HARDFP, and toolchain).

This selects the VA library built with `MAXCMDS=250`, located under the `COMPONENT_MAXCMD/` subfolder of the toolchain directory. The `CY_IGNORE` entry prevents linking the default 100-command `ifx_va.ar` library, avoiding symbol conflicts. Note that this variant requires more memory due to the larger command set.

## Additional information
* [Audio voice core RELEASE.md](./RELEASE.md)
* [Audio voice core library version](./version.txt)

## Utility Modules
The following utilities can be used directly by applications. Refer to their specific README files for details:

- [ASRC Utility](./docs/ASRC-README.md)
- [AGC Utility](./docs/AGC-README.md)
- [LPF Utility](./docs/LPF-README.md)
- [HPF Utility](./docs/HPF-README.md)