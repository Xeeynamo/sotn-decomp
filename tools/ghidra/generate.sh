rm -rf ./out
mkdir -p ./out
# generate symbols json
cd symbols && sh ./run.sh && cd ..
# create project, load overlays, apply types and symbols
python3 ./create-project.py --ghidra-root $GHIDRA_ROOT --exe ../../disks/saturn/0.BIN --symbols ./out/symbols.json --project-name sotn --project-location ./out/ && sh $GHIDRA_ROOT/ghidraRun "$(pwd)/out/sotn.gpr"
