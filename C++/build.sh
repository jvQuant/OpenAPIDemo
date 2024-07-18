#依赖zlib/websocketpp/gcc版本>4.8.5
yum install devtoolset-11-gcc devtoolset-11-gcc-c++ devtoolset-11-binutils
yum install zlib-ada-devel.x86_64
yum install websocketpp-devel.noarch

#buid
g++ -o client main.cpp -lboost_system -lpthread -lz  -std=c++11
#run
./client