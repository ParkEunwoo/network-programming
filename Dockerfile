FROM ubuntu

WORKDIR /project

RUN apt-get update && apt-get install vim -y && apt-get install git-core -y && apt-get install gcc -y

RUN git clone https://github.com/ParkEunwoo/network-programming.git

RUN cd network-programming

