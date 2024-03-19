#!/bin/bash
make -C lab$1 clean
tar cvzf compressed/ZurawelMarcin-cw0$1.tar.gz lab$1/*