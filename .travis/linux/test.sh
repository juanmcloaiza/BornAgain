docker exec dx bash -c "cd build; make check" && exit 0
docker exec dx bash -c "cat build/Testing/Temporary/*.log" && exit 1
