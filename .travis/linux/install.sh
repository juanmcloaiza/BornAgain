docker build -t bornagain/xenial -f `dirname $0`/Dockerfile.xenial .
docker build -t bornagain/bionic -f `dirname $0`/Dockerfile.bionic .

docker run -d --name dx -it bornagain/xenial
docker run -d --name db -it bornagain/bionic

docker ps -a
