# sotn-match

`sotn-match` is a tool for calculating signatures for overlay segments and functions that have been previously built and
then searching for those signatures in other overlay files. This utility relies on GNU map files created by `ld` at link
time.


## sotn-match evaluate

`evaluate` is used to calculate segment and function signatures for all text symbols. It takes a map file in GNU map
format (lld or gold formats may or may not work) along with the target binary overlay that map was used to build. That
file can be either a compiled file or one from a game disk.

`evaluate` will create a YAML document which can then be used by `scan` to find matching segments in another bin file.


Example:

```
sotn-match --output build/us/match.cen.yaml evaluate build/us/cen.map build/us/CEN.BIN
```

## sotn-match scan

`scan` will find any segments defined in the match config if they exist in the binary passed as the second argument. The
output is a YAML stream where each document contains details about a segment match along with all function symbols which
matched in that segment.

Example:

```
sotn-match scan build/us/match.cen.yaml disks/us/ST/RNO3/RNO3.BIN
```
