<<<<<<< HEAD
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
incdir="$topdir/include/appfwk"
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
    local pre="$1"; shift
    local one="$1"; shift
    local dest="$1"; shift
    if [ ! -f $one ] ; then
        return
    fi
    for tname in Nljs Structs
    do
        lname=$(echo $tname | awk '{print tolower($0)}')
        local hppj2="${schemadir}/${lname}.hpp.j2"
        local out="${dest}/${pre}${tname}.hpp"
        rm -f "$out"
        render "$one" "$hppj2" "$out"
        chmod -w "$out"
    done
}

do_one Cmd "${schemadir}/cmd-codegen.jsonnet" "$incdir"
do_one Test "${tstdir}/test-codegen.jsonnet" "$tstdir"
=======
#!/usr/bin/env bash

# Really ugly and temporary glue to run moo code generator.
# This will simplify and move into CMake.

mydir=$(dirname $(realpath $BASH_SOURCE))
srcdir=$(dirname $mydir)

# The need for this detail will go away once moo is cleaned up a bit.
oschema=$HOME/dev/moo/examples/oschema
runmoo () {
    moo -g '/lang:ocpp.jsonnet' \
        -M $oschema -T $oschema -M $mydir \
        "$@"
}

# Wrap up the render command.  This bakes in a mapping to file name
# which would be better somehow captured by the schema itself.
render () {
    local name="$1" ; shift
    local What="$1" ; shift
    local outdir="${1:-$srcdir/include/appfwk/${name}}"
    local what="$(echo $What | tr '[:upper:]' '[:lower:]')"
    local tmpl="o${what}.hpp.j2"
    local outhpp="$outdir/${What}.hpp"
    mkdir -p $outdir
    set -x
    runmoo -A path="dunedaq.appfwk.${name}" \
           -A ctxpath="dunedaq" \
           -A os="appfwk-${name}-schema.jsonnet" \
           render omodel.jsonnet $tmpl \
           > $outhpp
    set +x
    echo $outhpp
}


render cmd Structs
render cmd Nljs

render fdp Structs $srcdir/test/appfwk/fdp
render fdp Nljs    $srcdir/test/appfwk/fdp

render fdc Structs $srcdir/test/appfwk/fdc
render fdc Nljs    $srcdir/test/appfwk/fdc

>>>>>>> 29dc0fb2a58beebbc254ce5688a54dbe22384f3e
