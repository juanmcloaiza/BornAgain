docker exec dd bash -c "cd build; cpack"
docker exec dd bash -c "cd build; mv *.deb  ../BornAgain-dev-xenial.deb"
docker exec dd bash -c "curl -O https://github.com/probonopd/uploadtool/raw/master/upload.sh"
docker exec dd bash -c "bash upload.sh BornAgain*.deb*"


