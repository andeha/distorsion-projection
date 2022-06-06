#!/usr/bin/env /bin/zsh

builtin typeset BUNDLEID='ABCD1234'
builtin typeset TEAMID='4321ABCD'
builtin typeset -gx MAPFILE='/Users/<user- or project folder>/Monitor/Apps/module.modulemap'
builtin typeset -gx TOOLS_SMALL='/Users/<user- or project folder>/mips-tools/12.0.0'

builtin typeset progname=$0
builtin typeset small
builtin typeset signcode
builtin typeset debug_verbose

function usage
{
   cat << HEREDOC
   
   Usage: $progname [-s]
   
   optional arguments
    -h, --help     show this message and exit
    -s, --small    emit library for 'small' (Microchip Pic32 Mz and Mm)
    --sign         sign code when compiling for Apple macOS
    -v, --verbose  increase the verbosity of the script
   
HEREDOC
}

while [ $# -gt 0 ]; do
  case $1 in
    -s | --small)
       shift
       small="enabled"
       ;;
    --sign)
       shift
       signcode="enabled"
       ;;
    -v | --verbose)
       shift
       debug_verbose="enabled"
       ;;
    -help | --help | -h | --h | -\? )
       usage
       exit 1
       ;;
  esac
done

if [[ -n "$small" ]]; then
  if [[ -n "$debug_verbose" ]]; then
    builtin echo "For Microchip Pic32 Mm and Mz"
  fi
  builtin typeset -gx UNISON=Town_mz
  builtin typeset pic32nda='-fforce-enable-int128 -mmsa -mdspr2 -gdwarf-5'
  builtin typeset -gx PLATFLAGS="-target mipsel -mfloat-abi=hard -mcpu=mips32r5 -mabi=o32 -mfp64 $pic32nda -D__MZ__"
  ninja -f bld_mz-and-mm.ninja
  builtin typeset -gx UNISON=Town_mm
  builtin typeset -gx PLATFLAGS='-target mipsel -mfloat-abi=soft -mcpu=mips32r6 -mabi=o32 -mmicromips -D__MM__'
  ninja -f bld_mz-and-mm.ninja
else
  if [[ -n "$debug_verbose" ]]; then
    builtin echo "For Intel Mac and Arm Mac"
  fi
  builtin typeset -gx UNISON=distorsion-projection_intc
  builtin typeset -gx PLATFLAGS='-target arm64-apple-macos11 -D__armv8a__'
  ninja -f bld_intc-and-arm.ninja
  builtin typeset sha1git=`git log -1 '--pretty=format:%h'`
  builtin typeset spitfire="lib${UNISON}_$sha1git.a"
  builtin typeset -gx UNISON=projection-distorsion_arm
  builtin typeset -gx PLATFLAGS='-target x86_64-apple-darwin21.3.0'
  ninja -f bld_intc-and-arm.ninja
  lipo -create -output libTown_macos_$sha1git.a                              \
   libdistorsion-projection_intc_$sha1git.a                                  \
   libprojection-distorsion_arm_$sha1git.a
  if [[ -n "$signcode" ]]; then
    codesign -s ${TEAMID} -f -o runtime --timestamp -i ${BUNDLEID} libTown_macos_$sha1git.a
  fi
  builtin typeset haifa="lib${UNISON}_$sha1git.a"
  # print $haifa
  # print $spitfire
  rm -f $haifa $spitfire
  ln -f libTown_macos_$sha1git.a libTown_macos.a
fi
