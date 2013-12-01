#!/bin/sh

CFLAGS="-O3 -fomit-frame-pointer -s"

FMT="%-20s%-15s%-15s%-15s%-15s\n"


printf "$FMT" "Language" "Big table" "1000 elements" "100 elements" "10 elements"

TEST()
{
	name=$1
	description=$2
	shift 2
	if [ "${name##*.}" = "cpp" ]
	then
		CC=g++
	else
		CC=gcc
	fi
	$CC "$name" -o "$name".out      $CFLAGS $@
	$CC "$name" -o "$name"_1000.out $CFLAGS $@ -DTABLE_SIZE=1000
	$CC "$name" -o "$name"_100.out  $CFLAGS $@ -DTABLE_SIZE=100
	$CC "$name" -o "$name"_10.out   $CFLAGS $@ -DTABLE_SIZE=10
	printf "$FMT" "$description" $(./"$name".out) $(./"$name"_1000.out) $(./"$name"_100.out) $(./"$name"_10.out)
}

TEST "hands.c" "C (handmade)"
TEST "glib.c" "GLib" `pkg-config --cflags --libs glib-2.0`
TEST "cpp.cpp" "C++ (unordered_map)" "-std=c++0x"
TEST "cpp-map.cpp" "C++ (map)" "-std=c++0x"
TEST "qt.cpp" "Qt" `pkg-config --cflags --libs QtCore`

rm -f *.out

# $CXX cpp.cpp -o cpp.out "$CFLAGS" -std=c++0x
# printf "$FMT" "C++ (unordered_map)" `./cpp.out`
# 
# $CXX cpp-map.cpp -o cpp-map.out "$CFLAGS"
# printf "C++ (map)\t\t"
# 
# $CC `pkg-config --cflags --libs glib-2.0` glib.c -o glib.out "$CFLAGS"
# printf "C (GLib)\t\t"
# 
# valac --pkg glib-2.0 vala.vala -o vala.out -XO3
# printf "Vala (GLib)\t\t"
# 
# $CC hands.c -o hands.out "$CFLAGS"
# printf "$FMT" "C (handmade)" `hands.out`
# 
# $CXX `pkg-config --cflags --libs QtCore` qt.cpp -o qt.out "$CFLAGS"
# printf "C++ (Qt native QString)\t"
