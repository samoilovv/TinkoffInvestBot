FROM ubuntu

ARG DEBIAN_FRONTEND=noninteractive

RUN apt update 

RUN apt install -y g++ 

RUN apt install -y make

RUN apt install -y binutils

RUN apt install -y qt5-default

RUN apt install -y cmake

RUN apt install -y libssl-dev

RUN apt install -y libboost-system-dev

RUN apt install -y zlib1g-dev

RUN apt install -y libcurl4-openssl-dev
 
RUN apt install -y git

RUN apt install -y qtcreator

ENTRYPOINT ["qtcreator", ""]  
