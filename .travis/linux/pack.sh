docker exec dx bash -c "cd build; cpack"
docker exec dx bash -c "cd build; mv *.deb ./BornAgain-dev-xenial.deb"
docker cp dx:/source/build/BornAgain-dev-xenial.deb ./
