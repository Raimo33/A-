# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 12:51:48 by craimond          #+#    #+#              #
#    Updated: 2024/06/11 11:20:27 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DOCKERIMAGE_NAME = astar
CONTAINER_NAME = astar_container
DOCKERFILE_PATH = .

all : docker-build docker-run

docker-build:
	@docker build -t $(DOCKERIMAGE_NAME) $(DOCKERFILE_PATH)

docker-run:
	@xhost +local:root
	@docker run -it \
		-e DISPLAY=$(DISPLAY) \
		-e XDG_RUNTIME_DIR=/tmp \
		-v /tmp/.X11-unix:/tmp/.X11-unix \
		--device /dev/input/js0:/dev/input/js0 \
		--device /dev/input/js1:/dev/input/js1 \
		--name $(CONTAINER_NAME) \
		$(DOCKERIMAGE_NAME)

docker-clean:
	@docker stop $(CONTAINER_NAME)
	@docker rm $(CONTAINER_NAME)
	@docker rmi -f $(DOCKERIMAGE_NAME)

re: docker-clean all

.PHONY: docker-build docker-run docker-clean