#!/bin/bash

function compile_shaders {
    fname=$1
    fname_wout_ext=${fname%.*}
    # overkill way to do the same:
    # fname_wout_ext=$(echo $fname | awk 'match($0,"\\."){print RSTART}')
    glslc -o $fname_wout_ext.spv $fname
}