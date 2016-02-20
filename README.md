# rekindle
Hackable E-ink Tablets For Everyone

## Status
Extremely early, extremely unstable, extremely experimental. To use it at this stage you will need knowledge of cross compilers and embedded Linux development. I am working on a more reproducible build/installation process, but that is a ways off.

## Specs
* Freescale i.MX508 800 MHz processor
* 256 Mb RAM
* 4Gb total storage/3Gb for users

## Approach, Rationale and Goals
The Amazon Kindle Touch is the last Kindle ebook reader to be easily jailbreakable while still providing a high quality eink display, touch screen, and wifi. Under the hood, the Kindle is a mostly standard Linux box with an ARM chip, running X.Org to manage the display

The idea is to write a WebKit-based GTK program that acts as the new "operating system" of the device. This program will serve HTML/JavaScript/CSS based applications that can be downloaded or written/hacked by users. The capabilities of the device become that of a standard web browser. 

The hope is that apps can be designed to do a little work, put relevant information on the screen, then switch off so the device can conserve battery life while remaining useful. For example, a maps app could render the route and relevant stops for a trip, then switch off. The device continues to carry the rendered image but consume no power. It can be woken up again to modify the route, and then put back to sleep.

With some luck and hard work, this could result in an open source, affordable, hackable personal tablet with a battery life of a month.

## Links
* MobileRead [Wiki](http://wiki.mobileread.com/wiki/Main_Page) and [Forums](http://www.mobileread.com/forums/) for invaluable information on Jailbreaks and other Kindle hacks
* [Unexpected Token](http://unexpectedtoken.tumblr.com/) is where I document in-progress hacks and information


## Legal
Copyright © 2015, 2016 Ramsey Nasser. Provided under the MIT License.