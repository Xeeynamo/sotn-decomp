echo "Start by making sure repo is clean and good"
git checkout no0_still_failing
git restore .

echo "Delete any extracted no0 files from previous runs"
rm config/*no0*
rm -rf src/st/no0

echo "Get the master makefiles in place to build the project without no0"
rm Makefile
rm Makefile.psx.mk

cp Makefile_master Makefile
cp Makefile.psx_master.mk Makefile.psx.mk

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

echo "add config"
git add config/
echo "now make the clean"
make clean
echo "and next make extract"
make extract
echo "now we will build"
make build
echo "and then expected???"
make expected
