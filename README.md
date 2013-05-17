LGS Watch (Watchface for Pebble Watch)
=========

It shows the time (12h and 24h modes are supported), month, (ordinal) day number and week number. 

The current day is highlighted in the center line.

The alternative version of the watch face displays Year and Day of the year (i.e. 2013-18) instead of the week number. 

| Week  | Day of the Year |
|-------|------|
| ![Week][img] | ![Day of the Year][img_doty] |

Available in 8 langauges;

- English
- Spanish
- German
- Dutch
- French
- Croation
- Italian
- Norwegian

Compiled version of this watchface can be downloaded [here](http://scriptogr.am/fmeus/pebble-lgs-watchface)  
The font used is Chicago, it is freely available for download [here](http://ttfonts.net/font/5767_Chicago.htm)

[img]: https://dl.dropbox.com/u/265253/scriptogram/lgs_watchface.jpg
[img_doty]: https://dl.dropbox.com/u/265253/scriptogram/lgs_watchface_doty.jpg

## Build Instructions

Clone this repository in an appropriate directory:

	git clone https://github.com/fmeus/pebble-lgswatch.git

Set up waf:

	python ~/pebble-dev/pebble-sdk-release-001/tools/create_pebble_project.py --symlink-only ~/pebble-dev/pebble-sdk-release-001/sdk/ pebble-lgswatch
	cd pebble-lgswatch

Configure and build:

	./waf configure
	src/makeall.sh

Compiled version can be found in the folder `releases`