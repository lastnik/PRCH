#!/bin/bash


SDK_ROOT=/build/home/5GSDR_SDK_ROOT/Versions/2001

SetEnv()
{
	echo "SDK_ROOT: $SDK_ROOT"
	if [ $USE_CLANG = "YES" ]; then
		export CC=$SDK_ROOT/clang/bin/clang
		export CXX=$SDK_ROOT/clang/bin/clang++
		echo "CLANG is used"
	else
		export CXX=$SDK_ROOT/bin/x86_64-sdr-linux-gnu-g++
		export CC=$SDK_ROOT/bin/x86_64-sdr-linux-gnu-gcc
		echo "GCC is used"
	fi
	export PATH=$SDK_ROOT/share/cmake/bin:$PATH
	export _5GSDR_SDK_DIR="$SDK_ROOT"
}

Usage()
{
	cat <<-END
		Usage: cmakeenv.sh [ clang ] [ path-to-sdk ]
		By default, GCC is used to build the code. If you would like to build it with CLANg, use 'clang' parameter.
		The default path to SDK is $SDK_ROOT. To use the other location, just put it as unother parameter.
		The parameters may be given in any order.
	END
}

Clear()
{
    unset -v SDK_ROOT
    unset -v USE_CLANG
    unset -v CALL_USAGE
}

USE_CLANG="NO"
CALL_USAGE=0

while :; do
	if [ ! $1 ]; then break; fi
	case $1 in
		'clang')
			USE_CLANG=YES;;
		**/**)
			SDK_ROOT=$1;;
		*)
			CALL_USAGE=1
			break;;
	esac
    shift
done

if [ $CALL_USAGE -eq 1 ]; then
	Usage
else
	SetEnv
fi
Clear
