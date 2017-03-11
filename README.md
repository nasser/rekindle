# rekindle
Hackable E-ink Tablets For Everyone

## Status
Extremely early, extremely unstable, extremely experimental. To use it at this stage you will need knowledge of cross compilers and embedded Linux development, and the build scripts *will not work for you without additional work on your end*. I am working on a more reproducible build/installation process, but that is a ways off.

## Specs
* Freescale i.MX508 800 MHz processor
* 256 Mb RAM
* 4Gb total storage/3Gb for users

## Approach and Rationale
Under the hood, the Kindle is a mostly standard Linux box with an ARM chip, running X.Org to manage the display.

The idea is to write a HTML/CSS/JavaScript based "operating system" for the device. Apps can be downloaded, written, and hacked similarly to web apps. The browser as a platform was chosen for its mindshare, ease of development compared to C or Java, and the lack of need for a compiler toolchain.

For a period of time cross compiling [Electron](http://electron.atom.io/)
seemed like the rational way forward. This would give us both the canvas of a browser and the OS-level code of node.js. While [ARM builds of Electron are possible](https://github.com/electron/electron/issues/366), this proved too difficult to do in practice. The Kindle's lack of hardware floating point also casts into doubt whether or not an Electron port would be fast enough to be usable.

Instead, I'm pursuing a standalone GTK program using a WebKit view. It uses the on-device GTK, WebKit and JavaScriptCore libraries which simplifies things. This effectively acts as a simple, full screen browser, implementing the necessary JavaScript functions like `setInterval` and `setTimeout`. This has already been shown to work and support libraries as advanced as leaflet and p5.js.

For functionality that a browser cannot provide, a localized client-server model is the current thinking. An app can additionally have a node.js server component that performs advanced networking and filesystem manipulation. Node.js has been shown to run on the Kindle.

## Design Goals
The hope is that apps can be designed to do a little work, put relevant information on the screen, then switch off so the device can conserve battery life while remaining useful. For example, a maps app could render the route and relevant stops for a trip, then switch off. The device continues to carry the rendered image but consume no power. It can be woken up again to modify the route, and then put back to sleep. This balances the power hungry nature of running a browser with the functionality that approach provides. The Kindle screensaver has to be disabled for this to work, but that can be done.

With some luck and hard work, this could result in an open source, affordable, hackable personal tablet with a battery life of a month.

## Links
* MobileRead [Wiki](http://wiki.mobileread.com/wiki/Main_Page) and [Forums](http://www.mobileread.com/forums/) for invaluable information on Jailbreaks and other Kindle hacks


## Legal
Copyright © 2015-2016 Ramsey Nasser. Provided under the MIT License.
