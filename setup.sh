# starting from Ubuntu 22.04

apt-get update

# install git and clone the repo
apt-get install -y git
git clone https://github.com/Xeeynamo/sotn-decomp.git
cd sotn-decomp

# update submodules
git submodule update --init --recursive

# install debian packages
apt-get install -y $(cat tools/requirements-debian.txt)

# install rust and add to environment
curl https://sh.rustup.rs -sSf | bash -s -- -y
echo 'source $HOME/.cargo/env' >> $HOME/.bashrc

make update-dependencies

# copy sotn.us.cue/bin into disks
cp -r /disks/* /sotn-decomp/disks

# install python packages (has to be done twice for some reason?)
pip3 install -r tools/requirements-python.txt

# extract disk, build and check
make extract_disk
make extract -j && make build -j
make check
