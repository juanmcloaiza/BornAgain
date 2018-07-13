FROM scgmlz/bornagain-dev:xenial
RUN apt-get update
RUN apt-get install -y libqt5svg5-dev
RUN apt-get install -y python3 python3-dev python-numpy-devel

ADD . /source
WORKDIR /source
