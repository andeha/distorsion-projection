#!/usr/bin/env /bin/zsh

builtin typeset small
builtin typeset debug_verbose

function usage
{
   cat << HEREDOC
   
   Usage: $progname [-s]
   
   optional arguments
    -h, --help     show this message and exit
    -s, --small    emit library to small system (Microchip Pic32 Mz and Mm)
    -v, --verbose  increase the verbosity of the script
   
HEREDOC
}

if [[ $# -eq 0 ]]; then
  usage
  exit 2
fi

while [ $# -gt 0 ]; do
  case $1 in
    -s | --small)
       shift
       small="yes"
       ;;
    -v | --verbose)
       shift
       debug_verbose="yes"
       ;;
    -help | --help | -h | --h | -\?
       usage
       exit 1
       ;;
  esac
done

if [[ -n "$small" ]]; then
  if [[ -n "$debug_verbose" ]]; then
    builtin echo "For Microchip Pic32 Mz and Mm"
  fi
  builtin typeset -a UNISON=Town_mz
  ninja -f bld_mz-and-mm.ninja
  builtin typeset -a UNISON=Town_mm
  ninja -f bld_mz-and-mm.ninja
else
  if [[ -n "$debug_verbose" ]]; then
    builtin echo "For Intel Mac and Arm Mac"
  fi
  builtin typeset -a UNISON=distorsion-projection_intc
  ninja -f bld_intc-and-arm.ninja
  builtin typeset -a UNISON=projection-distorsion_arm
  ninja -f bld_intc-and-arm.ninja
  lipo -create -output libTown.a libdistorsion-projection_intel.a               \
   libprojection-distorsion_arm.a
fi
