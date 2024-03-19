#!/bin/bash
make -C lab$1 clean
filename=ZurawelMarcin-cw0$1.tar.gz
tar cvzf compressed/$filename lab$1/*
cp compressed/$filename /mnt/c/Users/marci/Downloads/$filename 