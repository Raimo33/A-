# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 12:51:48 by craimond          #+#    #+#              #
#    Updated: 2024/06/10 13:32:44 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DOCKERIMAGE_NAME = aStar
DOCKERFILE_PATH = .

all: docker-build docker-run

docker-build:
	@docker build -t $(DOCKERIMAGE_NAME) $(DOCKERFILE_PATH)

docker-run:
	@docker run -it --rm $(DOCKERIMAGE_NAME)

docker-clean:
	@docker rmi $(DOCKERIMAGE_NAME)

.PHONY: docker-build docker-run docker-clean