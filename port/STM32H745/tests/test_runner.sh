#!/bin/sh

rm /mnt/fatimg/*
umount /mnt/fatimg 2>/dev/null
if [ "$1" = "gdb" ]; then
    gdb ./test_suite
else
    ./test_suite
fi
mount -o loop fat16.img /mnt/fatimg

for file in /mnt/fatimg/*; do
  echo "contents of $(basename "$file"):"
  cat "$file"
  echo
done
