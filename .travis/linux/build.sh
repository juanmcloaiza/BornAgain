docker exec dx bash -c "mkdir build"
docker exec dx bash -c "cd build && cmake -D CMAKE_BUILD_TYPE=$BUILD_TYPE -D BUILD_DEBIAN=ON .."
docker exec dx bash -c "cd build && make -j$(nproc)"
#docker exec dx bash -c "cd build && echo 'Hello from xenial' > hello.txt"

docker exec db bash -c "mkdir build"
docker exec db bash -c "cd build && cmake -D CMAKE_BUILD_TYPE=$BUILD_TYPE -D BUILD_DEBIAN=ON .."
docker exec db bash -c "cd build && make -j$(nproc)"
#docker exec db bash -c "cd build && echo 'Hello from bionic' > hello.txt"

docker exec dj bash -c "mkdir build"
docker exec dj bash -c "cd build && cmake -D CMAKE_BUILD_TYPE=$BUILD_TYPE -D BUILD_DEBIAN=ON .."
docker exec dj bash -c "cd build && make -j$(nproc)"
#docker exec dj bash -c "cd build && echo 'Hello from jessie' > hello.txt"

docker exec ds bash -c "mkdir build"
docker exec ds bash -c "cd build && cmake -D CMAKE_BUILD_TYPE=$BUILD_TYPE -D BUILD_DEBIAN=ON .."
docker exec ds bash -c "cd build && make -j$(nproc)"
#docker exec ds bash -c "cd build && echo 'Hello from stretch' > hello.txt"
