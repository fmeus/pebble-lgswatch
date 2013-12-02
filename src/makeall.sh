#!/bin/bash
# Project     : LGS Watch watchface
# Copyright   : Copyright (c) 2011-2013 Little Gem Software. All rights reserved.

VER=2.2
REL=./releases/

# Cleanup
pebble clean

# Build
pebble build

# Move compiled version to releases folder
mv build/pebble-lgswatch.pbw $REL/lgs_v$VER.pbw

# Cleanup
pebble clean