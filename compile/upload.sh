#!/bin/bash
#
# Uploader script for xinu boot image to Fluke.
#
# @author John Kloosterman for CS320 at Calvin College
# @date March 12, 2012
#
# See http://xinu.ohnopub.net/mediawiki/index.php/Firmware
#
# Use "make upload" to run this script, so that the transfer
#  program gets compiled.
#
sudo ./lpc21isp-ipre -control xinu.hex /dev/ttyUSB0 38400 20000