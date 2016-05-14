#!/bin/bash

if [ `cat deque.h | md5sum | cut -f1 -d' '` = "7e447692735cee2fb7b17f27cc187599" ]; then
	exit 0
else
	echo "deque.h has been modified. Please re-download it from assignments"
	exit 1
fi

