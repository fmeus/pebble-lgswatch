LGS Watch (Watchface for Pebble Watch)
=========

Features:

* Display time in either 12h or 24h format
* Day of the week indication
* Configurable through the Pebble app on your smartphone
* Display battery and bluetooth status information (configurable, default On)
* Supporting 11 different languages (configurable, default English)
	- Croatian
	- Dutch
	- English
	- Finnish
	- French
	- German
	- Greek
	- Italian
	- Norwegian
	- Spanish
	- Turkish
* Second date information line (configurable, default Week)

Compiled version of this watchface can be downloaded [here](http://sharedmemorydump.net/pebble-lgs-watchface)  
The font used is Chicago, it is freely available for download [here](http://ttfonts.net/font/5767_Chicago.htm)

## LGS Watch

| LGS Watch               | Information                                     |
|:-----------------------:|:------------------------------------------------|
| ![LGS Watch][lgs_watch] | 1 - 12h or 24 format, based on you Pebble setup<br/>2 - Day of the week indicator<br/>3 - Battery and Bluetooth status information<br/>4 - Date<br/>5 - Second date line |

## Bluetooth Connection Status

| Display                                 | Information                  |
|:---------------------------------------:|:-----------------------------|
| ![](/resources/images/bluetooth.png)    | Connected to smartphone      |
| ![](/resources/images/no_bluetooth.png) | Disconnected from smartphone |

## Battery Status

| Display                                  | Information |
|:----------------------------------------:|:------------|
| ![](/resources/images/batt_charging.png) | Charging    |
| ![](/resources/images/batt_080_100.png)  | 80-100%     |
| ![](/resources/images/batt_060_080.png)  | 60-80%      |
| ![](/resources/images/batt_040_060.png)  | 40-60%      |
| ![](/resources/images/batt_020_040.png)  | 20-40%      |
| ![](/resources/images/batt_000_020.png)  | 0-20%       |

## Configure LGS Watch using your smartphone

| Pebble app on smartphone                | LGS Watch settings                 |
|:---------------------------------------:|:----------------------------------:|
| ![Pebble app on smartphone][pebble_app] | ![LGS Watch settings ][lgs_config] |

## Build Instructions

Clone repository:

	git clone https://github.com/fmeus/pebble-lgswatch.git

Configure and build:

	src/makeall.sh

Compiled version can be found in the folder `releases`

[pebble_app]: /screenshots/pebble_app.png
[lgs_config]: /screenshots/lgs_config.png
[lgs_watch]: /screenshots/lgs_watch.png