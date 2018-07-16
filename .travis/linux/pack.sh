docker exec dx bash -c "cd build; cpack"
#docker exec dx bash -c "cd build; cp *.txt package.deb"
docker exec dx bash -c "cd build; mv *.deb ./BornAgain-dev-xenial.deb"
docker cp dx:/source/build/BornAgain-dev-xenial.deb ./

#docker exec db bash -c "cd build; cpack"
##docker exec db bash -c "cd build; cp *.txt package.deb"
#docker exec db bash -c "cd build; mv *.deb ./BornAgain-dev-bionic.deb"
#docker cp db:/source/build/BornAgain-dev-bionic.deb ./

#docker exec dj bash -c "cd build; cpack"
##docker exec dj bash -c "cd build; cp *.txt package.deb"
#docker exec dj bash -c "cd build; mv *.deb ./BornAgain-dev-jessie.deb"
#docker cp dj:/source/build/BornAgain-dev-jessie.deb ./

#docker exec ds bash -c "cd build; cpack"
##docker exec ds bash -c "cd build; cp *.txt package.deb"
#docker exec ds bash -c "cd build; mv *.deb ./BornAgain-dev-stretch.deb"
#docker cp ds:/source/build/BornAgain-dev-stretch.deb ./
