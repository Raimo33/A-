/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:37:35 by craimond          #+#    #+#             */
/*   Updated: 2024/06/08 14:38:06 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>

class InternalErrorException : public std::exception
{
	public:
		InternalErrorException(const char *msg);
		const char *what() const noexcept override;

	private:
		const char *_msg;
};