/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:59:51 by tookuyam          #+#    #+#             */
/*   Updated: 2024/07/11 15:47:46 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_ERRORS_H
# define PX_ERRORS_H

# include <limits.h>

typedef enum e_px_errors
{
	PX_EARGCNT = INT_MIN,
	PX_EHEREARG,
}	t_px_errors;

#endif
