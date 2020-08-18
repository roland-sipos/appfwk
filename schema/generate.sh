#!/bin/bash

# This script manually generates CCM configuration support code.
# Some or all of it should be incorporated in to CMake.

# NB: There is nothing magic about the locations for the generated
# code and we may certainly change them either to make the CMake
# integration easier or (eg) because we want to install the generated
# code.  This is just a first stab.
#
# HOWEVER: if we adjust the locations then we likely need to adjust
# some parameters, eg in hte *-codegen.jsonnet" we likely need to set
# "structincs" so the generated nljs.hpp file finds the generated
# structs.hpp file.

schemadir="$(dirname $(realpath $BASH_SOURCE))"
topdir="$(dirname $schemadir)"
srcdir="$topdir/src"
tstdir="$topdir/test"

pushd $srcdir > /dev/null

render () {
    model="$1" ; shift
    templ="$1" ; shift
    out="$1" ; shift
    cmd="moo -J $schemadir -A schema=schema/avro.jsonnet render -o $out $model $templ"
    echo $cmd
    $cmd || exit -1
}

do_one () {
    local one="$1"; shift
    local dest="$1"; shift
    if [ ! -f $one ] ; then
        return
    fi
    local name="$(basename $one -codegen.jsonnet)"
    for tname in nljs structs
    do
        local hppj2="${schemadir}/${tname}.hpp.j2"
        local out="${dest}/${name}-${tname}.hpp"
        render "$one" "$hppj2" "$out"
    done
}

for one in $schemadir/*-codegen.jsonnet
do
    do_one "$one" "$srcdir"
done

for one in $tstdir/*-codegen.jsonnet
do
    do_one "$one" "$tstdir"
done
