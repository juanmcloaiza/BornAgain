docker exec dd bash -c "cd build; cpack"
docker exec dd bash -c "cd build; mv *.deb  BornAgain-dev-xenial.deb"
