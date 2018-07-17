docker exec dx bash -c "mkdir build"
docker exec dx bash -c "cd build && cmake -D CMAKE_BUILD_TYPE=$BUILD_TYPE -D BUILD_DEBIAN=ON .."
docker exec dx bash -c "cd build && make -j$(nproc)"
