# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 14:47:17 by craimond          #+#    #+#              #
#    Updated: 2024/06/12 13:24:15 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM ubuntu:24.04

ARG DEPS="build-essential wget git cmake libx11-dev xorg-dev libglu1-mesa-dev libudev-dev libopenal-dev libfreetype6-dev libjpeg-dev libvorbis-dev libflac-dev"
ARG LOCAL="app"
ARG DEST="/app"

ENV NAME="aStar"
ENV SFML_LIBS_DIR="/usr/local/lib"
ENV SFML_INCS_DIR="/usr/local/include"
ENV DISPLAY=:0

RUN apt-get update && apt-get install -y ${DEPS} && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /tmp

RUN wget https://github.com/SFML/SFML/releases/download/2.6.1/SFML-2.6.1-linux-gcc-64-bit.tar.gz \
	&& tar -xvzf SFML-2.6.1-linux-gcc-64-bit.tar.gz \
	&& rm -rf SFML-2.6.1-linux-gcc-64-bit.tar.gz \
    && mv SFML-2.6.1/lib/* ${SFML_LIBS_DIR}/ \
    && mv SFML-2.6.1/include/* ${SFML_INCS_DIR}/ \
	&& ldconfig \
	&& rm -rf SFML-2.6.1

COPY ${LOCAL} ${DEST}

WORKDIR ${DEST}

RUN make && make clean

ENTRYPOINT ["./aStar"]