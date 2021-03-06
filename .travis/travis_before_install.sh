#!/bin/bash

sudo apt-get -qq update
# qt5 should be used. Remove qt4-dev to avoid confusion.
sudo apt-get remove libqt4-dev
cd core
dpkg-checkbuilddeps 2> /tmp/dpkg-builddeps || true
cat /tmp/dpkg-builddeps
sed -e "s/^.*:.*:\s//" -e "s/\s([^)]*)//g" /tmp/dpkg-builddeps > /tmp/build_depends
echo "additional packages required for building:"; cat /tmp/build_depends
sudo xargs --arg-file /tmp/build_depends apt-get -q --assume-yes install fakeroot
dpkg -l
true

