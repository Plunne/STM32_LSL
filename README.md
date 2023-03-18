# STM32_LSL

Low Level STM32 Abstraction Library with many optionnal features.

# INSTRUCTIONS

Before programming you should setup your board by copying its files into the project root.

**Exemple :**

For an `F103c8t6`

```sh
cp -r boards/stm32f103xx .
```

# SUPPORTED BOARDS

## stm32f103xx

All STM32 F103 that depends of the `stm32f103xb.h` header.

## stm32f767xx

All STM32 F767 that depends of the `stm32f767xx.h` header.

# FUNCTIONNALITIES

- [x] Delay (ms)
- [x] Digital R/W
- [x] 7 segment display (Anode/Cathode modes)
- [ ] Analog R/W
- [ ] UART Tx/Rx