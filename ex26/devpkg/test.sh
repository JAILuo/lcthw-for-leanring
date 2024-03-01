set -e

# go somewhere safe
cd /tmp

# get the source to base APR 1.7.4
curl -L -O http://archive.apache.org/dist/apr/apr-1.7.4.tar.gz

# extract it and go into the source
tar -xzvf apr-1.7.4.tar.gz
cd apr-1.7.4

# configure, make, make install
./configure
make
sudo make install

# reset and cleanup
cd /tmp
rm -rf apr-1.7.4 apr-1.7.4.tar.gz


# do the same thing with apt-util
curl -L -O http://archive.apache.org/dist/apr/apr-util-1.6.3.tar.gz

#extract
tar -xzvf apr-util-1.6.3.tar.gz
cd apr-util-1.6.3

# configure, make, make install
./configure --with-apr=/usr/local/apr
# you need that extra parameter to configure beacuse apr-util can't really find it beacuse...who knows???

make 
make
sudo make install

# cleanup
cd /tmp
rm -rf apt-util-1.6.3* apr-1.7.4

