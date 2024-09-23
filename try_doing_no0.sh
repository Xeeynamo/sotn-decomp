echo "Start by making sure repo is clean and good"
git checkout master
git restore .

echo "Delete any extracted no0 files from previous runs"
rm config/*no0*
rm -rf src/st/no0

echo "Make the project like normal"
make clean
make extract -j
make all -j

echo "Generate the splat config."
export VERSION=us
python3 tools/make-config.py no0

echo "Perform makefile changes"

rm Makefile
rm Makefile.psx.mk

cp no0_Makefile Makefile
cp no0_Makefile.psx.mk Makefile.psx.mk

echo "Run the Make command"
make -j