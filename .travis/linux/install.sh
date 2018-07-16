docker build -t bornagain/xenial -f `dirname $0`/Dockerfile.xenial .
docker build -t bornagain/bionic -f `dirname $0`/Dockerfile.bionic .
docker build -t bornagain/jessie -f `dirname $0`/Dockerfile.jessie .
docker build -t bornagain/stretch -f `dirname $0`/Dockerfile.stretch .

docker run -d --name dx -it bornagain/xenial
docker run -d --name db -it bornagain/bionic
docker run -d --name dj -it bornagain/jessie
docker run -d --name ds -it bornagain/stretch

docker ps -a
