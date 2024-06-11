# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 14:47:17 by craimond          #+#    #+#              #
#    Updated: 2024/06/11 10:23:18 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM ubuntu:24.04

ARG DEPS="build-essential wget git cmake libx11-dev xorg-dev libglu1-mesa-dev libudev-dev libopenal-dev libfreetype6-dev libjpeg-dev libvorbis-dev libflac-dev"
ARG LOCAL="app"
ARG DEST="/app"
ENV SFML_LIBS_DIR="/usr/local/lib"
ENV SFML_INCS_DIR="/usr/local/include"
ENV NAME="aStar"

RUN apt-get update && apt-get install -y ${DEPS} && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/SFML/SFML/releases/download/2.6.1/SFML-2.6.1-linux-gcc-64-bit.tar.gz
RUN tar -xvzf SFML-2.6.1-linux-gcc-64-bit.tar.gz && rm SFML-2.6.1-linux-gcc-64-bit.tar.gz

WORKDIR SFML-2.6.1

RUN cmake -DCMAKE_INSTALL_PREFIX=/usr/local . && make && make install

COPY ${LOCAL} ${DEST}

WORKDIR ${DEST}

RUN make && make clean

CMD ["./aStar"]