#!/bin/bash

# Project     : LGS Watch watchface
# Copyright   : Copyright (c) 2011-2013 Little Gem Software. All rights reserved.

VER=2.1
REL=./releases/

function std_version {
	echo "#define LANGUAGE_$1" > src/lgs_config.h
	echo "#define FORMAT_WEEK" >> src/lgs_config.h
	pebble clean
	pebble build
	mv build/pebble-lgswatch.pbw $REL/lgs_$1_v$2.pbw
}

function doty_version {
	echo "#define LANGUAGE_$1" > src/lgs_config.h
	echo "#define FORMAT_DOTY" >> src/lgs_config.h
	pebble clean
	pebble build
	mv build/pebble-lgswatch.pbw $REL/lgs_$1_doty_v$2.pbw
}

function ddmmyy_version {
	echo "#define LANGUAGE_$1" > src/lgs_config.h
	echo "#define FORMAT_DDMMYY" >> src/lgs_config.h
	pebble clean
	pebble build
	mv build/pebble-lgswatch.pbw $REL/lgs_$1_ddmmyy_v$2.pbw
}

function mmddyy_version {
	echo "#define LANGUAGE_$1" > src/lgs_config.h
	echo "#define FORMAT_MMDDYY" >> src/lgs_config.h
	pebble clean
	pebble build
	mv build/pebble-lgswatch.pbw $REL/lgs_$1_mmddyy_v$2.pbw
}

function wxdx_version {
	echo "#define LANGUAGE_$1" > src/lgs_config.h
	echo "#define FORMAT_WXDX" >> src/lgs_config.h
	pebble clean
	pebble build
	mv build/pebble-lgswatch.pbw $REL/lgs_$1_wxdx_v$2.pbw
}

function build {
	doty_version $1 $VER
	ddmmyy_version $1 $VER
	mmddyy_version $1 $VER
	wxdx_version $1 $VER
	std_version $1 $VER
}

languages=(EN FR DE HR ES IT NO NL)
for ln in "${languages[@]}"
do
	build $ln
done

pebble clean