/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:38:11 by craimond          #+#    #+#             */
/*   Updated: 2024/06/08 15:19:20 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/exceptions.hpp"

InternalErrorException::InternalErrorException(const char *msg) : _msg(msg) {}
const char *InternalErrorException::what() const noexcept { return _msg; }