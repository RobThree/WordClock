# WordClock

Hobby project building a word clock with friends. Features are still being debated, this is very much a work in progress.

## The idea

The idea is to take a Ribba ([Black](https://www.ikea.com/nl/nl/p/ribba-fotolijst-zwart-40378401/) or [white](https://www.ikea.com/nl/nl/p/ribba-fotolijst-wit-00378403/)<sub><sup>, Shamone!</sup></sub>) and repurpose it as a WordClock. We'll use a cutting plotter on self adhesive vinyl to cut the words and icons. The design is a bit different from most other WordClocks in that it includes a few icons which can be assigned for any purpose. The design includes:

- An alarmclock - as an indicator an alarm is set for example
- A heart - as a seconds-indicator (make it 'pulse' red to give it a heartbeat feel) or maybe you make it light up on Valentine's day?
- A party popper - have it light up at all the birthdays in your family or on New Year's eve or...
- A bell - to indicate you have new e-mail or to remind of you something (make it flash!) or...
- A WiFi symbol - we can make it light up blue for connecting, red for errors or problems, green for 'everything OK' and maybe yellow for NTP syncing. Or anything else we want...

Because we use RGB leds any of the indicators can have multiple functions, as do the letters by the way, by combining color, flashing or 'pulsing' and other effects. Because we have 115 "pixels" available that we can make pretty much any color we can do a whole lot with this "display" other than have it display the time. Think of rainbow or 'matrix' effects, playing snake, or tetris, on it with your phone as a controller, displaying an analogue clock using the "pixels", have it display the roomtemperature or even the local weather... We're only limited by the restrictions of the microcontroller, what is possible in software and what we can display on the 'screen'. And that sounds restrictive but having WiFi and, thus, internect connectivity we can do a LOT and are mostly bound by our own imagination.

## Parts

- A Ribba (see [the idea](#the-idea))
- A [Wemos D1 mini](https://www.aliexpress.com/item/32651747570.html) (or a NodeMCU, ESP32, Raspberry pi)
- At least 2m (115 LEDs minimum) of [60 LED/m WS2812B LED strip](https://www.aliexpress.com/item/2036819167.html) (IP30 will do)
- A [5V DC power supply](https://www.aliexpress.com/item/32670505021.html) or [brick](https://www.aliexpress.com/item/33014935336.html) capable of delivering at least 7A or more

According to the specs, a WS2812B draws 18W per meter at 60 LEDs per meter. That's 18W / 60LEDs = 0.3W per LED. That's 0.3W / 5V = 0.06A per LED. Given 115 LED's (10 rows of 11 LEDs + 5 status LEDs) we'll need at least 6.9A + some for the microcontroller and optional other parts.

It's generally recommended to 'inject power' every 2.5 feet or every 75cm so we won't have 'yellowing' at the end of the LED strip and also won't be overloading our wiring.

Since, normally, we won't be driving all LEDs at the same time at full brightness we do have some headroom in both the specs of the power supply and the power injection. You'll probably get along just fine with a 3A power supply and injecting power only at the beginning of the strip; however we like to err on the safe side, especially since we don't know what other uses we can think of for our clock in the future which might require lighting more, or even all, LEDs or driving additional circuitry as well.

### Optional parts

To improve the circuit or to add additional features:

- [A 470Ω resistor](https://www.aliexpress.com/item/32847047012.html)
- [Some 1000μF electrolytic capacitors](https://www.aliexpress.com/item/32909080992.html) with a voltage rating at least 5V
- [10 pairs of 3pin SM JST connector male/female for WS2812B LED Strip](https://www.aliexpress.com/item/1718558728.html)
- [LDR](https://www.aliexpress.com/item/32760631393.html) or [light sensor](https://www.aliexpress.com/item/32550638947.html) to have the clock auto-adjust brightness
- [DHT22](https://www.aliexpress.com/item/32802908424.html) to give your clock another purpose: temperature / humidity sensor
- [Power switch](https://www.aliexpress.com/item/32832214619.html); not required (you can simply unplug) but neat
- [A power jack](https://www.aliexpress.com/item/32414627873.html) of [some kind](https://www.aliexpress.com/item/4000198429452.html) if you opt for a power supply with a barrel connector
- [A buzzer](https://www.aliexpress.com/item/32849730395.html) to give your clock an alarm function

If your LEDstrip has no 'smoothing' capacitors 'built-in', you should consider putting one of them at every point where the power is injected into the strip. The 470Ω resistor is used for current limiting the data pin.

## Getting started

Built with [PlatformIO](https://platformio.org/)

Read the instructions in [include/example_config.h](include/example_config.h)
