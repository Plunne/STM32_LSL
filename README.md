# STM32_LSL

Low Level STM32 Abstraction Library with many optionnal features.

# INSTRUCTIONS

Before programming you shall setup your board by copying its files into the project root.

**Exemple :**

For an `F103c8t6`

```sh
cp -r boards/stm32f103xx .
```

# SUPPORTED BOARDS

## [stm32f103xx](https://github.com/Plunne/STM32_LSL/tree/f1)

All STM32 F103 that depends of the `stm32f103xb.h` header.

## [stm32f767xx](https://github.com/Plunne/STM32_LSL/tree/f7)

All STM32 F767 that depends of the `stm32f767xx.h` header.

# FUNCTIONNALITIES

- Delay (ms)
- Digital R/W
- 7 segment display (Anode/Cathode modes)
- Analog R/W
- UART Tx/Rx
- Timers