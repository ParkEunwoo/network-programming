FROM ubuntu

WORKDIR /project

RUN apt-get update && apt-get install vim -y && apt-get install git-core -y

RUN git clone https://github.com/ParkEunwoo/network-programming.git

