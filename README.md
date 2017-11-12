# u-boot-mainline-s5p4418

work in progress!!

documentation will be added soon!

## why am I doing this?
A few months ago, I bought a chinese board called nanopi2-fire.
When I got it, I got hugely disappointed to find out that all the mainline supports
were stopped for S5P4418. Virtually the original chip maker named Nexcell(not sure spelling is connect but who cares?) 
has given up on the chip. So here I go with this as another hobby project.

I have no idea why they chose to give up on chip with simple design. Honestly I get to like this chip more and more as I dig deeper into it.

## Difficulties
As most people reading this already know, the datasheet sucks. There is no detailed description
on the chip and furthermore information in the sheet is sometimes incorrect.
To deal with this, I had to constantly refer to the so called BSP source code released by Nexcell in the old u-boot.

To make things more complicated, there is no JTAG avaiable on nanopi2.

## Current status
Currently
1. SPL gets loaded into internal SRAM from MMC
2. initializes clocks and DDR3
3. initializes UART0 so you can debug
4. initializes MMC0
5. loads u-boot main into DDR3
6. then boots up u-boot main

Then u-boot main follows a normal start-up procedure and you get to command prompt.

For now, there is no DM/DTB support in SPL. All the device initialization was done using some kind of dirty hack.
And u-boot main doesn't get initialized properly. All you get is UART and command prompt.

## Current Clock Setup
The following is current clock setup I am using
1. PLL0   1 GHz
..-fclk   : 1 GHz FCLK
..-hclk   : 250 Mhz HCLK
..-bclk   : 333 Mhz BCLK
..-pclk   : 166 Mhz BCLK
2. PLL1   800 MHz for DDR3-1600
..-mdclk  : 800 MHz
..-mclk   : 800 MHz
..-mbclk  : 400 MHz
..-mpclk  : 200 MHz
3. PLL2   : not used
4. PLL3   : not used

## SPL size issue
According to S5P4418 datasheet, the ROM boot code loads only 16 KB from MMC. According to my experiment, this turned out to be wrong.
I still don't have correct information on this but it looks like loading 32K shouldn't be a problem.
The incorrect information has affected my decision to disable DM/DTB in SPL to reduce SPL binary size.
Anyway SPL boots up and works now so moving SPL to DM/DTB based code should be just a matter of time.
I am working on this.


