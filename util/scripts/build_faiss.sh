CUDA_PATH=/usr/local/cuda
INSTALL_DIR=libfaiss-install

cd ~

# clone faiss repository
git clone https://github.com/facebookresearch/faiss.git

cd faiss

# get date
dt=$(date '+%Y%m%d')

# get cuda version
if command -v nvcc &> /dev/null
then
    CUDA_VERSION=$(nvcc --version | egrep -o '[0-9]+\.[0-9]\.[0-9]+')
    BUILD_CUDA=true
else 
    CUDA_VERSION=cpu
    BUILD_CUDA=false
fi

# configure faiss
if [ $BUILD_CUDA = true ]; then
    echo "Build With CUDA"
    ./configure --with-cuda=${CUDA_PATH} --prefix="$(pwd)/${INSTALL_DIR}"
else
    echo "Build Without CUDA"
    ./configure --without-cuda --prefix="$(pwd)/${INSTALL_DIR}"
fi

# compile & install faiss
make -j && make install

# zip faiss binaries
rm libfaiss-install/lib/libfaiss.so
tar -cvzf faiss-cuda${CUDA_VERSION}-${dt}-linux.tgz ${INSTALL_DIR}

cd ~